#ifndef BLOCK_H
#define BLOCK_H

#include "core/platform/platform.h"
#include "core/types/typedef.hpp"

namespace Nocturn::rendering
{
	struct BlockDataHolder; /* forward decalartion */

	enum class BlockId : uint8
	{
		Air		  = 0,
		Grass	  = 1,
		Dirt	  = 2,
		Stone	  = 3,
		OakBark	  = 4,
		OakLeaf	  = 5,
		Sand	  = 6,
		Water	  = 7,
		Cactus	  = 8,
		Rose	  = 9,
		TallGrass = 10,
		DeadShrub = 11,
		END
	};

	struct Block
	{
		Block( ) noexcept = default;
		Block( const BlockId id );
		Block( const uint8 id );
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

		uint8 m_id = static_cast< uint8 >( BlockId::Air ); /* default BlockId::Air */
	};
} // namespace Nocturn::rendering

#endif