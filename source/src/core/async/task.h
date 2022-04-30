#ifndef TASK_H
#define TASK_H

#include <cassert>
#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <thread>

#include "core/platform/platform.h"
#include "core/types/typedef.hpp"

namespace Nocturn
{
	using Task = std::function< void( ) >;

	static constexpr int8 CNumberOfPriorities = 3;
	static constexpr int8 CPriorityMaxIndex	  = CNumberOfPriorities - 1;

	enum class ETaskPriorityLevel : int8
	{
		Low = 0,
		Medium,
		High
	};

	class BaseTask
	{
	public:
		BaseTask( ) noexcept			 = default;
		BaseTask( const BaseTask &task ) = delete;
		BaseTask( BaseTask &&task ) noexcept;
		explicit BaseTask( Task &&task ) noexcept;

		BaseTask &operator=( const BaseTask &task ) = delete;

		BaseTask &operator=( BaseTask &&task ) noexcept;

		NODISCARD virtual Task Release( ) NOCTURN_PURE;
		virtual void		   Execute( ) NOCTURN_PURE;

		virtual ~BaseTask( ) noexcept = default;

	protected:
		Task m_task{ };
	};

	class PriorityTask final: public BaseTask
	{
	public:
		PriorityTask( ) noexcept				 = default;
		PriorityTask( const PriorityTask &task ) = delete;
		PriorityTask( PriorityTask &&task ) noexcept;
		explicit PriorityTask( Task &&task, const ETaskPriorityLevel priority = ETaskPriorityLevel::Low ) noexcept;

		PriorityTask &operator=( const PriorityTask &task ) = delete;
		PriorityTask &operator								=( PriorityTask &&task ) noexcept;
		explicit	  operator bool( ) const noexcept;

		NODISCARD ETaskPriorityLevel EGetPriority( ) const noexcept;
		NODISCARD uint8				 IGetPriority( ) const noexcept;

		Task Release( ) noexcept override;
		void Execute( ) override;

		~PriorityTask( ) noexcept override = default;

	private:
		ETaskPriorityLevel m_priority{ };
	};

	class PriorityQueue
	{
	public:
		PriorityQueue( ) noexcept						= default;
		PriorityQueue( const PriorityQueue & ) noexcept = delete;
		PriorityQueue( PriorityQueue && )				= delete;

		PriorityQueue &operator=( const PriorityQueue & ) = delete;
		PriorityQueue &operator=( PriorityQueue && ) = delete;

		PriorityTask			 TryPop( const ETaskPriorityLevel priority );
		PriorityTask			 TryPop( const uint8 priority );
		PriorityTask			 ForcePop( );
		bool					 TryPush( PriorityTask &task );	  // && -> &
		void					 ForcePush( PriorityTask &task ); // && -> &
		void					 ForceQuit( );
		NODISCARD constexpr bool IsEmpty( ) const noexcept;

		NODISCARD size_t GetNumOfTasks( ) const noexcept;

		~PriorityQueue( ) noexcept = default;

	private:
		std::array< std::deque< Task >, CNumberOfPriorities > m_queueTasks;
		std::mutex											  m_mutex;
		std::condition_variable								  m_cv;
		bool												  m_end = false;
	};

	class TaskSystem
	{
	public:
		explicit TaskSystem( const uint32 nthreads = 1 );
		TaskSystem( const TaskSystem &task ) = delete;
		TaskSystem( TaskSystem && )			 = delete;

		TaskSystem operator=( const TaskSystem &task ) = delete;
		TaskSystem operator=( TaskSystem &&task ) = delete;

		void Async( PriorityTask task );
		// void Async( Task task, const ETaskPriorityLevel priority );
		void RunTaskLoop( const uint8 queueIndex );
		void TryRunTask( );
		void ForceQuit( ) const noexcept;

		uint32 GetNumOfThreads( ) const noexcept;
		uint32 GetNumOfTasks( ) const noexcept;
		void   PrintTaskEachQueue( ) const noexcept;

		~TaskSystem( ) noexcept;

	private:
		uint32					  m_numberOfWorkers;
		static thread_local int32 m_currentTaskQueue;

		std::vector< std::thread >	 m_threads;
		std::vector< PriorityQueue > m_queue;

		// Total number of tasks pushed in each priority level.
		std::array< std::atomic< uint32 >, CNumberOfPriorities > m_numberOfTasks;
	};

	class TaskGroup
	{
	public:
		explicit TaskGroup( TaskSystem *taskSystem ) :
			m_pTaskSystem( taskSystem )
		{}

		TaskGroup( const TaskGroup & ) = delete;
		TaskGroup( TaskGroup && )	   = delete;

		TaskGroup &operator=( const TaskGroup & ) = delete;
		TaskGroup &operator=( TaskGroup && ) = delete;

		template< typename TCallable >
		using callable = std::decay_t< TCallable >;

		template< typename TWrapFunction >
		class Wrap
		{
		public:
			template< typename TInitFunction >
			explicit Wrap( TInitFunction &&other, std::atomic< uint64 > &counter ) :
				m_f( std::forward< TInitFunction >( other ) ),
				m_counter( counter )
			{}

			Wrap( const Wrap &other ) :
				m_f( other.m_f ),
				m_counter( other.m_counter )
			{}

			Wrap( Wrap &&other ) noexcept :
				m_f( std::move( other.m_f ) ),
				m_counter( other.m_counter )
			{}

			Wrap &operator=( const Wrap & ) = delete;
			Wrap &operator=( Wrap && ) = delete;

			void operator( )( )
			{
				m_f( );
				--m_counter;
			}

			~Wrap( ) noexcept = default;

		private:
			TWrapFunction		   m_f;
			std::atomic< uint64 > &m_counter;
		};

		template< typename F >
		Wrap< callable< F > > MakeWrapFunction( F &&f, std::atomic< uint64 > &counter )
		{
			return Wrap< callable< F > >( std::forward< F >( f ), counter );
		}

		template< typename F >
		void Run( F &&f )
		{
			// TODO : get current priority(static variable in TaskSystem)
			constexpr auto priority = 0; /*=TaskSystem::GetCurrentTaskPriority();*/
			Run( std::forward< F >( f ), priority );
			return priority;
		}

		template< typename F >
		void Run( F &&f, const uint32 priority )
		{
			m_running = true;
			++m_inFlight;
			m_pTaskSystem->Async( PriorityTask{ MakeWrapFunction( std::forward< F >( f ), m_inFlight ), ETaskPriorityLevel::Low } );
		}

		void Wait( ) const
		{
			while( m_inFlight )
			{
				m_pTaskSystem->TryRunTask( );
			}
		}

		~TaskGroup( ) noexcept = default;

		std::atomic< std::size_t > m_inFlight{ 0 };

	private:
		bool		m_running = false;
		TaskSystem *m_pTaskSystem;
	};

} // namespace Nocturn
#endif