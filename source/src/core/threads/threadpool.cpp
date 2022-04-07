#include "core/threads/threadpool.h"

namespace Nocturn
{
	ThreadPool::ThreadPool( ) noexcept :
		m_done( false ),
		m_doWork( false ),
		m_executedTasks( 0 ),
		m_threadCount( std::max( 2u, std::thread::hardware_concurrency( ) ) )
	{
		for( uint32_t i = 0; i < m_threadCount; i++ )
			m_threads.emplace_back( std::thread( &ThreadPool::ThreadWork, this ) );
	}

	void ThreadPool::BeginWork( const bool notifyAll ) noexcept
	{
		m_doWork = true;
		if( notifyAll )
			m_cv.notify_all( );
		else
			m_cv.notify_one( );
	}

	void ThreadPool::ThreadWork( )
	{
		bool bContinue = true;
		while( bContinue )
		{
			if( !m_doWork )
			{
				std::unique_lock lock( m_mutex );
				m_cv.wait( lock, [ & ]
						   { return ( m_doWork || !m_tasks.IsEmpty( ) ); } );
				bContinue = !m_done && !m_tasks.IsEmpty( );
			}

			bool		 canExecute = false;
			TaskFunction task;
			{
				std::lock_guard lock( m_mutex );
				if( !m_tasks.IsEmpty( ) )
				{
					canExecute = m_tasks.Pop( task );
				}
			}
			if( canExecute )
			{
				++m_executedTasks;
				task( );
			}
		}
	}

	ThreadPool::~ThreadPool( ) noexcept
	{
		{
			std::lock_guard lock( m_mutex );
			m_done = true;
		}
		m_cv.notify_all( );

		for( auto &t : m_threads )
		{
			t.join( );
		}
	}

} // namespace Nocturn