/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 13-11-2021 20:45:03                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 17-02-2022 22:42:19                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef CHUNK_SECTION_H
#define CHUNK_SECTION_H

#include <array>
#include <cstdint>

#include "core/GL/GLFunctions.h"
#include "core/math/glm.hpp"
#include "core/types/typedef.hpp"

#include "core/components/constants.hpp"
#include "rendering/Renderer/Data/model.hpp"
#include "rendering/world/block/block.h"
#include "rendering/world/block/blockdatabase.h"
#include "rendering/world/chunk/chunkmesh.h"

namespace Nocturn
{
	/**
     * @brief Represents a section of a chunk that contains blocks.
     */
	struct ChunkLayer
	{
		ChunkLayer() :
			m_numberOfBlocks(0)
		{}

		void Increase() noexcept
		{
			++m_numberOfBlocks;
		}

		void Decrease() noexcept
		{
			--m_numberOfBlocks;
		}

		/**
         * @brief Checks if all blocks in the layer are solid.
         * @return True if all blocks are solid, false otherwise.
         */
		NODISCARD bool IsAllSolid() const
		{
			return static_cast< uint32 >(m_numberOfBlocks) == CChunkBase;
		}

		/**
         * @brief Retrieves the number of blocks in the layer.
         * @return The number of blocks.
         */
		NODISCARD auto getNumberOfBlocks() const noexcept
		{
			return m_numberOfBlocks;
		}

	private:
		uint16 m_numberOfBlocks;
	};

	/**
     * @brief Represents the type of neighbor chunk.
     */
	enum class NeighborType : uint8
	{
		Left = 0,
		Right,
		Front,
		Back
	};

	/**
     * @brief Represents a neighbor chunk.
     */
	struct Neighbor
	{
		NChunkSection* left	 = nullptr;
		NChunkSection* right	 = nullptr;
		NChunkSection* top	 = nullptr;
		NChunkSection* bottom = nullptr;
	};

    /**
     * @brief Represents adjacent chunks.
     */
	struct AdjacentChunk
	{
		AdjacentChunk(int32 x, int32 z) noexcept;
		AdjacentChunk(const ivec2& vec) noexcept;

		ivec2 front;
		ivec2 back;
		ivec2 left;
		ivec2 right;
	};

	class NChunkSection
	{
	public:
		NChunkSection() noexcept = default;

		explicit NChunkSection(const ivec2& Location);

		// TODO: Investigate the behavior of the default constructor
		NChunkSection(const NChunkSection& chunk) = default;
		NChunkSection(NChunkSection&& chunk) = delete;

		NChunkSection& operator=(const NChunkSection& chunk) = delete;
		NChunkSection& operator=(NChunkSection&& chunk) = delete;

		/**
         * @brief Retrieves the block at the specified position.
         * @param Position The block position.
         * @return The block at the position.
         */
		NBlock operator[](const ivec3& Position) const noexcept;

	    /**
	     * @brief Sets the block at the specified world position to the given block ID.
	     * @param blockId The block ID.
	     * @param worldPosition The world position.
	     */
	    void SetBlock(EBlockId blockId, const ivec3& worldPosition) noexcept;

	    /**
	     * @brief Sets the block at the specified world coordinates to the given block ID.
	     * @param blockId The block ID.
	     * @param worldX The world X coordinate.
	     * @param worldY The world Y coordinate.
	     * @param worldZ The world Z coordinate.
	     */
	    void SetBlock(EBlockId blockId, int32 worldX, int32 worldY, int32 worldZ) noexcept;

		void SetLight(const vec3& BlockPosition, uint8 LightLevel) noexcept;

		void SetSkyLight(const vec3& BlockPosition, uint8 LightLevel) noexcept;

		/**
	     * @brief Sets the neighbor chunk of the specified type.
	     * @param type The neighbor type.
	     * @param chunk The neighbor chunk.
	     */
		void SetNeighbor(NeighborType type, NChunkSection& chunk) noexcept;

		/**
	     * @brief Marks the chunk section as a renderable chunk.
	     */
		void SetRenderableChunk() noexcept;

		/**
		 * @brief Gets the location (chunk position) of the chunk section.
		 * @return The location.
		 */
		NODISCARD ivec2 GetLocation() const noexcept;

		/**
		 * @brief Sets the maximum Y coordinate of the chunk section.
		 * @param maxy The maximum Y coordinate.
		 */
		void SetChunkMaxY(const uint8 maxy) noexcept
		{
			m_maxy = maxy;
		}

	    /**
	     * @brief Gets the render info of the chunk section.
	     * @return The render info.
	     */
	    const RenderInfo& GetRenderInfo() const;

	    /**
	     * @brief Gets the vector of blocks in the chunk section.
	     * @return The vector of blocks.
	     */
		const std::vector< NBlock >& GetBlocks() const;

	    /**
	     * @brief Gets the layer of the chunk section at the specified Y coordinate.
	     * @param LayerY The Y coordinate of the layer.
	     * @return The chunk layer.
	     */
	    NODISCARD ChunkLayer GetLayer(const uint32 LayerY) const
	    {
			return m_layers[ LayerY ];
	    }

	    /**
	     * @brief Gets the maximum Y coordinate of the chunk section.
	     * @return The maximum Y coordinate.
	     */
	    NODISCARD uint8 GetChunkMaxY() const noexcept
	    {
		    return m_maxy;
	    }

	    /**
	     * @brief Gets the block at the specified coordinates.
	     * @param x The X coordinate.
	     * @param y The Y coordinate.
	     * @param z The Z coordinate.
	     * @return The block at the coordinates.
	     */
	    NBlock GetBlock(int32_t x, int32_t y, int32_t z) const noexcept;

	    /**
	     * @brief Gets the block at the specified coordinates.
	     * @param coords The block coordinates.
	     * @return The block at the coordinates.
	     */
	    NBlock GetBlock(const ivec3& coords) const noexcept;

		uint8 GetLight(const vec3& BlockPosition) const noexcept;

		uint8 GetSkyLight(const vec3& BlockPosition) const noexcept;

	    /**
	     * @brief Gets the block adjacent to the specified coordinates.
	     * @param coords The block coordinates.
	     * @return The adjacent block.
	     */
	    NBlock GetAdjacentBlock(const ivec3& coords) const noexcept;

	    /**
	     * @brief Tries to get the neighbor chunk of the specified type.
	     * @param type The neighbor type.
	     * @return A pointer to the neighbor chunk, or nullptr if not found.
	     */
	    NChunkSection* TryGetNeighbor(NeighborType type) const noexcept;

	    /**
	     * @brief Checks if the chunk section has a mesh.
	     * @return True if the chunk section has a mesh, false otherwise.
	     */
	    bool HasMesh() const noexcept;

		/**
		 * @brief Checks if the chunk section has been loaded.
		 * @return True if the chunk section has been loaded, false otherwise.
		*/
		NODISCARD bool HasLoaded() const noexcept;

	    /**
	     * @brief Checks if the chunk section should be rendered.
	     * @return True if the chunk section should be rendered, false otherwise.
	     */
	    bool ShouldToRender() const noexcept;
		
		bool ShouldCalculateLighting() const noexcept
		{
			return bShouldCalculateLighting;
		}

	    /**
	     * @brief Checks if the chunk section is renderable.
	     * @return True if the chunk section is renderable, false otherwise.
	     */
	    bool IsRenderable() const noexcept;

	    /**
	     * @brief Creates the chunk section.
	     */
	    void CreateChunk();

		void ReloadChunk();

	    /**
	     * @brief Loads the buffer data for rendering the chunk section.
	     */
	    void LoadBufferData();

	    /**
	     * @brief Deletes the mesh of the chunk section.
	     */
	    void DeleteMesh() noexcept;

	    /**
	     * @brief Retrieves the size of a block in bytes.
	     * @return The size of a block in bytes.
	     */
	    static constexpr size_t GetSizeOfBlock() noexcept;

	    /**
	     * @brief Retrieves the size from the given index coordinates.
	     * @param x The X index coordinate.
	     * @param y The Y index coordinate.
	     * @param z The Z index coordinate.
	     * @return The size calculated from the index coordinates.
	     */
	    static uint32 GetSizeFromIndex(uint32 x, uint32 y, uint32 z) noexcept;

	    /**
	     * @brief Retrieves the size from the given index coordinates.
	     * @param vec The index coordinates.
	     * @return The size calculated from the index coordinates.
	     */
	    static uint32 GetSizeFromIndex(const ivec3& vec) noexcept;

	    /**
	     * @brief Retrieves the index coordinates from the given size.
	     * @param size The size.
	     * @return The index coordinates calculated from the size.
	     */
	    static ivec3 GetIndexFromSize(uint32 size) noexcept;

		~NChunkSection() noexcept = default;

	private:
		/** Layers of the chunk section. */
		std::array< ChunkLayer, CChunkY > m_layers;

		// Use std::vector instead of std::unordered_map because we need to init 16*16*256 block directly
		// All of those blocks will be initialized with BlockId::Air
		/** Vector of blocks in the chunk section. */
		std::vector< NBlock > m_chunk;

		/** Mesh of the chunk section. */
	    ChunkMesh m_mesh;

		/** Neighbor chunks of the chunk section. */
	    Neighbor m_neighbor;

		/** Location (chunk position) of the chunk section. */
	    ivec2 m_location;

		/** Flag indicating if the chunk section is a renderable chunk. */
		bool bIsRenderableChunk : 1 { false };

		bool bShouldCalculateLighting : 1 { false };

		/** Maximum Y coordinate of the chunk section. */
	    uint8 m_maxy;

		/**
	     * @brief Checks if the specified coordinates are out of bounds.
	     * @param x The X coordinate.
	     * @param y The Y coordinate.
	     * @param z The Z coordinate.
	     * @return True if the coordinates are out of bounds, false otherwise.
	     */
		static bool OutOfBound(int32_t x, int32_t y, int32_t z) noexcept;
	};
} // namespace Nocturn

#endif