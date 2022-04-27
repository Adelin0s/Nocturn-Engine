/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 30-01-2022 10:49:32                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 18-02-2022 15:17:02                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

//#include "core/async/queuesafe.h"
#include "core/types/typedef.hpp"

#include "rendering/data/camera.h"

namespace Nocturn
{
	using TaskFunction = std::function< void( ) >;

	// TODO @ Make chunks according to the priority level
	enum class Priority : uint8
	{
		None = 0,
		Low,
		Medium,
		High
	};

	class ThreadPool
	{
	public:
		// ThreadPool( ) noexcept;
		// ThreadPool( const ThreadPool &smth ) = delete;
		// ThreadPool( ThreadPool &&smth )		 = delete;

		// ThreadPool &operator=( const ThreadPool &smth ) = delete;
		// ThreadPool &operator=( ThreadPool &&smth ) = delete;

		// void BeginWork( const bool notifyAll = false ) noexcept;

		// NODISCARD size_t GetSize( ) const noexcept
		//{
		//	// return m_tasks.GetSize( );
		// }

		// NODISCARD size_t GetCountExecutedTasks( ) const noexcept
		//{
		//	return m_executedTasks;
		// }

		// template< typename T >
		// void PushTask( T &&t ) noexcept
		//{
		//	// m_tasks.Push( std::forward< T >( t ) );
		//	// m_cv.notify_one( );
		// }

		//~ThreadPool( ) noexcept;

	private:
		// QueueSafe				   m_tasks;
		std::vector< std::thread > m_threads;
		std::mutex				   m_queueMutex;
		mutable std::mutex		   m_mutex;
		std::condition_variable	   m_cv;

		/**
		 * @brief atomic variable that control when workers must be stop their working
		 */
		std::atomic_bool m_done;
		/**
		 * @brief atomic variable that control when workers should be start their working
		 */
		std::atomic_bool m_doWork;

		std::atomic_size_t m_executedTasks;

		uint32_t m_threadCount;

		void ThreadWork( );
	};
} // namespace Nocturn

#endif