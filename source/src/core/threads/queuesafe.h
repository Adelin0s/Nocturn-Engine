#ifndef QUEUE_SAFE_H
#define QUEUE_SAFE_H

#include <mutex>
#include <queue>

#include "core/platform/platform.h"

namespace Nocturn
{
	/**
	 * @brief Thread-safe data race queue
	 */

	using TaskFunction = std::function< void( ) >;

	class QueueSafe
	{
	public:
		QueueSafe( ) noexcept :
			m_mutex{ }
		{}

		QueueSafe( const QueueSafe & ) = delete;
		QueueSafe( QueueSafe && )	   = delete;

		QueueSafe &operator=( const QueueSafe & ) = delete;
		QueueSafe &operator=( QueueSafe && ) = delete;

		void Push( TaskFunction &&f ) noexcept
		{
			std::lock_guard lock( m_mutex );
			m_queue.push( std::forward< TaskFunction >( f ) );
		}

		bool Pop( TaskFunction &function ) noexcept
		{
			if( !IsEmpty( ) )
			{
				std::lock_guard lock( m_mutex );
				function = std::move( m_queue.front( ) );
				m_queue.pop( );
				return true;
			}
			return false;
		}

		NODISCARD bool IsEmpty( ) const noexcept
		{
			std::lock_guard lock( m_mutex );
			return m_queue.empty( );
		}

		NODISCARD size_t GetSize( ) const noexcept
		{
			return m_queue.size( );
		}

		~QueueSafe( ) noexcept = default;

	private:
		mutable std::mutex		   m_mutex;
		std::queue< TaskFunction > m_queue;
	};

} // namespace Nocturn

#endif