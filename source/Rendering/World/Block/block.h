#ifndef BLOCK_H
#define BLOCK_H

#include "core/platform/platform.h"
#include "core/types/typedef.hpp"

namespace Nocturn
{
	// Forward declares
	struct BlockDataHolder;

	static constexpr std::array< float, 12 > frontFace
	{
		0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1
	};

	static constexpr std::array< float, 12 > backFace
	{
		1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0
	};

	static constexpr std::array< float, 12 > leftFace
	{
		0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0
	};

	static constexpr std::array< float, 12 > rightFace
	{
		1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1
	};

	static constexpr std::array< float, 12 > topFace
	{
		0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0
	};

	static constexpr std::array< float, 12 > bottomFace
	{
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
	
	struct NBlock
	{
		static constexpr uint8 CMaxLightLevel = 31;

		/** Default constructor. */
		NBlock() noexcept = default;

		/** Constructor with EBlockId parameter. */
		NBlock(EBlockId BlockId);

		/** Constructor with block ID parameter. */
		NBlock(uint8 BlockId);

		/** Default copy constructor. */
		NBlock(const NBlock& Block) = default;

		/** Default move constructor. */
		NBlock(NBlock&& Block) = default;

		/** Copy assignment operator. */
		NBlock& operator=(const NBlock& Block) = default;

		/** Move assignment operator. */
		NBlock& operator=(NBlock&& Block) = default;

		/** Assignment operator with EBlockId parameter. */
		void operator=(EBlockId BlockId);

		/** Equality comparison operator with EBlockId parameter. */
		bool operator==(EBlockId BlockId) const;

		/** Equality comparison operator with NBlock parameter. */
		bool operator==(const NBlock& Block) const;

		/** Inequality comparison operator with NBlock parameter. */
		bool operator!=(const NBlock& Block) const;

		/** Set the light level of the block. */
		void SetLight(uint8 LightLevel) noexcept;

		void SetSkyLight(uint8 LightLevel) noexcept;

		bool IsTransparent() const noexcept
		{
			return BlockType == EBlockId::Air;
		}

		/** Get the data of the block. */
		NODISCARD const BlockDataHolder& GetData() const;

		/** Get the light level of the block. */
		NODISCARD uint8 GetSkyLight() const noexcept
		{
			return SkyLight;
		}

		/** Get the light level of the block. */
		NODISCARD uint8 GetLight() const noexcept
		{
			return BlockLight;
		}

		/** Default destructor. */
		~NBlock() noexcept = default;

	private:
		EBlockId BlockType = EBlockId::Air;

		uint8 SkyLight : 5;

		uint8 BlockLight : 5;
	};
} // namespace Nocturn

#endif