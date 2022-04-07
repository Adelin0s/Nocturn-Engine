#ifndef BLOCK_H
#define BLOCK_H

#include "core/platform/platform.h"
#include "core/types/typedef.hpp"
#include "rendering/world/block/blockid.hpp"

namespace Nocturn::rendering
{
	struct BlockDataHolder; /* forward decalartion */

	struct Block
	{
		Block( ) noexcept = default;
		Block( const BlockId id );
		Block( const BlockId_t id );
		Block( const Block &block ) = default;
		Block( Block &&block )		= default;

		Block &operator=( const Block &block ) = default;
		Block &operator=( Block &&block ) = default;
		void   operator					  =( const BlockId id );
		bool   operator==( const BlockId id ) const;
		bool   operator==( const Block &block ) const;
		bool   operator!=( const Block &block ) const;

		NODISCARD const BlockDataHolder &getData( ) const;

		~Block( ) noexcept = default;

		uint8_t m_id = static_cast< uint8_t >( BlockId::Air ); /* default BlockId::Air */
	};
} // namespace Nocturn::rendering

#endif