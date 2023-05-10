#ifndef BLOCK_H
#define BLOCK_H

#include "core/platform/platform.h"
#include "core/types/typedef.hpp"

namespace Nocturn
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

	enum class EBlockId : uint8
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
		, End
	};

	struct NBlockLight
	{
	    uint8_t Level;  // Nivelul luminii (de la 0 la 15)
	    uint8_t Light;  // Luminozitatea (de la 0 la 15)

	    NBlockLight()
		:
			Level(0), Light(0)
		{}

	    NBlockLight(const uint8 LevelIn, const uint8_t LightIn)
		:
			Level(LevelIn), Light(LightIn)
		{}
	};

	struct NBlock
	{
		NBlock() noexcept = default;
		NBlock(EBlockId BlockId);
		NBlock(uint8 BlockId);

		NBlock(const NBlock& Block) = default;
		NBlock(NBlock&& Block) = default;

		NBlock& operator=(const NBlock& Block) = default;
		NBlock& operator=(NBlock&& Block) = default;

		void operator=(EBlockId BlockId);
		bool operator==(EBlockId BlockId) const;
		bool operator==(const NBlock& Block) const;
		bool operator!=(const NBlock& Block) const;

		NODISCARD const BlockDataHolder& GetData() const;

		~NBlock() noexcept = default;

		EBlockId BlockType = EBlockId::Air;
		NBlockLight BlockLight;
	};
} // namespace Nocturn

#endif