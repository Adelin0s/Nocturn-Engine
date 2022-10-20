#ifndef BLOCK_H
#define BLOCK_H

#include "core/platform/platform.h"
#include "core/types/typedef.hpp"

namespace Nocturn::rendering
{
	struct BlockDataHolder; /* forward decalartion */

	static constexpr std::array< float, 12 > frontFace{
		0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1
	};

	static constexpr std::array< float, 12 > backFace{
		1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0
	};

	static constexpr std::array< float, 12 > leftFace{
		0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0
	};

	static constexpr std::array< float, 12 > rightFace{
		1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1
	};

	static constexpr std::array< float, 12 > topFace{
		0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0
	};

	static constexpr std::array< float, 12 > bottomFace{
		0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1
	};

	enum class BlockId : uint8
	{
		Air = 0
		,	Grass
		,	Dirt
		,	Stone
		,	OakBark
		,	OakLeaf
		,	Sand
		,	Water
		,	Cactus
		,	Rose
		,	TallGrass
		,	DeadShrub

		,	End
	};

	struct Block
	{
		Block( ) noexcept = default;
		Block( BlockId id );
		Block( uint8 id );
		Block( const Block &block ) = default;
		Block( Block &&block ) = default;

		Block &operator=( const Block &block ) = default;
		Block &operator=( Block &&block ) = default;
		void   operator=( BlockId id );
		bool   operator==( BlockId id ) const;
		bool   operator==( const Block &block ) const;
		bool   operator!=( const Block &block ) const;

		NODISCARD const BlockDataHolder &getData( ) const;

		~Block( ) noexcept = default;

		uint8 m_id = static_cast< uint8 >( BlockId::Air ); /* default BlockId::Air */
	};
} // namespace Nocturn::rendering

#endif