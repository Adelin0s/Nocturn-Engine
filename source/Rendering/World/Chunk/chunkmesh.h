/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 13-11-2021 21:53:35                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 17-02-2022 21:54:59                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include <cstdint>
#include <glm/glm.hpp>

#include "core/platform/platform.h"
#include "core/types/typedef.hpp"
#include "Rendering/Renderer/Data/model.hpp"

namespace Nocturn
{
	class NChunkSection;
	class ChunkMesh;
	struct Block;
	struct BlockDataHolder;

	struct AdjacentBlock
	{
		void update( uint32_t x, uint32_t y, uint32_t z );

		ivec3 top;
		ivec3 bottom;
		ivec3 left;
		ivec3 right;
		ivec3 front;
		ivec3 back;
	};

	enum class FaceType
	{
		Up = 0
		,	Down
		,	Left
		,	Right
		,	Back
		,	Front
	};

	class ChunkMesh
	{
	public:
		ChunkMesh() noexcept = default;

		ChunkMesh(const ChunkMesh& chunk) = default;
		ChunkMesh(ChunkMesh&& mesh) = delete;

		ChunkMesh &operator=( const ChunkMesh &mesh ) = delete;
		ChunkMesh &operator=( ChunkMesh &&mesh ) = delete;

		void Initialize(const NChunkSection* ChunkIn);
		NODISCARD const Model< VertexDataType::ChunkDataType >& GetModel() const
		{
			return m_model;
		}
		NODISCARD uint32 GetIndicesSize() const noexcept;
		void			 MakeMesh(const NChunkSection* ChunkIn);
		void			 ReloadMesh(const NChunkSection* ChunkIn);
		void			 LoadBufferData();
		NODISCARD bool	 HasMesh() const noexcept
		{
			return bHasMesh;
		}
		NODISCARD bool   HasLoaded() const noexcept
		{
			return bHasLoaded;
		}

		void						DeleteMesh( ) noexcept;

		~ChunkMesh( ) noexcept = default;

	private:
		uint32_t m_index		= 0; /* lolita lolita , cichi cichi bambita */

		bool bHasMesh : 1 = false;
		bool bHasLoaded : 1 = false;
		bool bShouldToReloadMesh : 1 = false;

		Model< VertexDataType::ChunkDataType > m_model;

		/** Pointer to the current chunk. */
		const NChunkSection *Chunk = nullptr;

		VertexType::ChunkVertex	  Mesh;

		void GenerateMeshLayer(uint32 LayerY);
		void MakeFace( const Vertices_t &TlockFace, const glm::vec2 &TextureCoords, const Block_t &BlockPosition, const ivec3 &AdjBlock );
		void AddBlockDataLight(const vec3& BlockCoords);
		NODISCARD bool ShouldMakeFace( const Block_t &BlockCoords, const ivec3 &AdjCoords ) const noexcept;

		/**
		 * @brief Checks if the neighbors have all the blocks set on the current layer y.
		 * @param LayerY Current layer.
		 * @return True if all blocks are set or False
		 */
		NODISCARD bool ShouldPassLayer( uint32 LayerY ) const noexcept;
		void AddFace( const Vertices_t &Face, const Textures_t &TexturesCoords, const ivec2 &ChunkPosition, const Block_t &BlockPosition );
	};
} // namespace Nocturn
#endif