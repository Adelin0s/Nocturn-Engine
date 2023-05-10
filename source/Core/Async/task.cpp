#include "task.h"

#include <iostream>

namespace Nocturn
{
#pragma region "BaseTask"
	BaseTask::BaseTask( BaseTask &&task ) noexcept
	{
		std::swap( m_task, task.m_task );
	}

	BaseTask::BaseTask( Task &&task ) noexcept :
		m_task( std::move( task ) )
	{}

	BaseTask &BaseTask::operator=( BaseTask &&task ) noexcept
	{
		std::swap( m_task, task.m_task );
		return *this;
	}
#pragma endregion

#pragma region "PriorityTask"
	PriorityTask::PriorityTask( PriorityTask &&task ) noexcept :
		BaseTask( std::move( task.m_task ) ),
		m_priority( task.m_priority )
	{}

	PriorityTask::PriorityTask( Task &&task, const ETaskPriorityLevel priority ) noexcept :
		BaseTask( std::move( task ) ),
		m_priority( priority )
	{}

	PriorityTask &PriorityTask::operator=( PriorityTask &&task ) noexcept
	{
		std::swap( m_task, task.m_task );
		m_priority = task.m_priority;
		return *this;
	}

	FORCE_INLINE PriorityTask::operator bool( ) const noexcept
	{
		return static_cast< bool >( m_task );
	}

	ETaskPriorityLevel PriorityTask::EGetPriority( ) const noexcept
	{
		return m_priority;
	}

	uint8 PriorityTask::IGetPriority( ) const noexcept
	{
		return static_cast< uint8 >( m_priority );
	}

	Task PriorityTask::Release( ) noexcept
	{
		Task t;
		std::swap( t, m_task );
		return t;
	}

	void PriorityTask::Execute( )
	{
		Release( )( );
	}
#pragma endregion

#pragma region "PriorityQueue"
	PriorityTask PriorityQueue::TryPop( const ETaskPriorityLevel priority )
	{
		const std::unique_lock lock{ m_mutex, std::try_to_lock };

		if( lock )
		{
			if( auto &queue = m_queueTasks.at( static_cast< int8 >( priority ) ); !queue.empty( ) )
			{
				PriorityTask p_task( std::move( queue.front( ) ), priority );
				queue.pop_front( );
				return p_task;
			}
		}
		return { };
	}

	PriorityTask PriorityQueue::TryPop( const uint8 priority )
	{
		return TryPop( static_cast< ETaskPriorityLevel >( priority ) );
	}

	PriorityTask PriorityQueue::ForcePop( )
	{
		std::unique_lock lock( m_mutex );
		while( !m_end && IsEmpty( ) )
		{
			m_cv.wait( lock, [ & ]
					   { return !IsEmpty( ) && !m_end; } );
		}
		for( auto priority = CPriorityMaxIndex; priority > -1; --priority )
		{
			if( auto &queue = m_queueTasks.at( priority ); !queue.empty( ) )
			{
				PriorityTask p_task( std::move( queue.front( ) ), static_cast< ETaskPriorityLevel >( priority ) );
				queue.pop_front( );
				return p_task;
			}
		}
		return { };
	}

	bool PriorityQueue::TryPush( PriorityTask &task )
	{
		{
			const std::unique_lock lock( m_mutex, std::try_to_lock );
			if( !lock )
				return false;

			m_queueTasks.at( task.IGetPriority( ) ).push_front( task.Release( ) );
		}
		m_cv.notify_all( );
		return true;
	}

	void PriorityQueue::ForcePush( PriorityTask &task )
	{
		{
			std::unique_lock lock( m_mutex );
			m_queueTasks.at( task.IGetPriority( ) ).push_front( task.Release( ) );
		}
		m_cv.notify_all( );
	}

	void PriorityQueue::ForceQuit( )
	{
		{
			std::unique_lock lock( m_mutex );
			m_end = true;
		}
		m_cv.notify_all( );
	}

	size_t PriorityQueue::GetNumOfTasks( ) const noexcept
	{
		size_t count = 0;
		for( int32 i = 0; i < CNumberOfPriorities; ++i )
			count += m_queueTasks[ i ].size( );
		return count;
	}

	NODISCARD constexpr bool PriorityQueue::IsEmpty( ) const noexcept
	{
		for( const auto &q : m_queueTasks )
			if( !q.empty( ) )
				return false;
		return true;
	}
#pragma endregion

#pragma region "TaskSystem"
	NTaskSystem::NTaskSystem( const uint32 nthreads ) :
		m_numberOfWorkers( std::min( std::thread::hardware_concurrency( ), nthreads ) ),
		m_queue( nthreads )
	{
		assert( nthreads > 0 );

		for( uint32 i = 0; i < nthreads; i++ )
		{
			m_threads.emplace_back( std::thread( &NTaskSystem::RunTaskLoop, this, i ) );
		}
	}

	void NTaskSystem::Async( PriorityTask task )
	{
		assert( task );

		const auto index = m_numberOfTasks[ task.IGetPriority( ) ]++;

		for( uint32_t i = 0; i < m_numberOfWorkers; i++ )
		{
			if( m_queue[ ( i + index ) % m_numberOfWorkers ].TryPush( task ) )
				return;
		}

		m_queue[ index % m_numberOfWorkers ].ForcePush( task );
	}

	void NTaskSystem::Async( Task task, const ETaskPriorityLevel priority )
	{
		Async( PriorityTask{ std::move( task ), priority } );
	}

	/**
	 * \brief The main function that all worker execute
	 * \param queueIndex is the thread index used to select thread's PriorityQueue
	 */
	void NTaskSystem::RunTaskLoop( const uint8 queueIndex )
	{
		while( true )
		{
			PriorityTask task;
			for( int8 priority = CPriorityMaxIndex; priority >= 0; --priority )
			{
				// TODO : Iterate over all threads if current thread has not any task to execute
				task = m_queue[ ( queueIndex % m_numberOfWorkers ) ].TryPop( ETaskPriorityLevel::Low );
				if( task )
					break;
			}
			if( !task )
				task = m_queue[ queueIndex ].ForcePop( );
			if( !task )
				break;
			task.Execute( );
		}
	}

	void NTaskSystem::TryRunTask( )
	{
		for( auto priority = CPriorityMaxIndex; priority >= 0; --priority )
		{
			for( uint32 i = 0; i < m_numberOfWorkers; ++i )
			{
				if( auto task = m_queue[ i ].TryPop( priority ); task )
				{
					std::cout << "here\n";
					task.Execute( );
					return;
				}
			}
		}
	}

	void NTaskSystem::ForceQuit( ) const noexcept
	{
		this->~NTaskSystem( );
	}

	uint32 NTaskSystem ::GetNumOfThreads( ) const noexcept
	{
		return m_numberOfWorkers;
	}

	uint32 NTaskSystem::GetNumOfTasks( ) const noexcept
	{
		uint32 s = 0;
		for( int i = 0; i < 3; i++ )
			s += m_numberOfTasks[ i ];
		return s;
	}

	void NTaskSystem::PrintTaskEachQueue( ) const noexcept
	{
		for( uint32 i = 0; i < m_numberOfWorkers; ++i )
			std::cout << "Worker_" << i << ' ' << m_queue[ i ].GetNumOfTasks( ) << '\n';
	}

	NTaskSystem::~NTaskSystem( ) noexcept
	{
		for( auto &q : m_queue )
			q.ForceQuit( );

		for( auto &t : m_threads )
			t.join( );
	}
#pragma endregion
} // namespace Nocturn
