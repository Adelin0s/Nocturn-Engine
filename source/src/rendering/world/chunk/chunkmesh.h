/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 13-11-2021 21:53:35                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 17-02-2022 21:54:59                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include <array>
#include <cstdint>
#include <glm/glm.hpp>

#include "core/platform/platform.h"
#include "rendering/data/model.h"
#include "rendering/world/block/blockid.hpp"

namespace Nocturn::rendering
{
	class ChunkSection;
	class ChunkMesh;
	struct Block;
	struct BlockDataHolder;

	struct AdjacentBlock
	{
		void update( const uint32_t x, const uint32_t y, const uint32_t z );

		glm::ivec3 top;
		glm::ivec3 bottom;
		glm::ivec3 left;
		glm::ivec3 right;
		glm::ivec3 front;
		glm::ivec3 back;
	};

	class ChunkMesh
	{
	public:
		ChunkMesh( ) noexcept = default;
		ChunkMesh( ChunkSection &chunk );
		ChunkMesh( const ChunkMesh &chunk ) = default;
		ChunkMesh( ChunkMesh &&mesh )		= delete;

		ChunkMesh &operator=( const ChunkMesh &mesh ) = delete;
		ChunkMesh &operator=( ChunkMesh &&mesh ) = delete;

		NODISCARD const Model &getModel( ) const;
		NODISCARD uint32	   getIndicesSize( ) const noexcept;
		void				   makeMesh( ChunkSection &pchunk );
		void				   loadBufferData( );
		NODISCARD bool		   hasMesh( ) const noexcept;
		NODISCARD bool		   hasLoaded( ) const noexcept;

		~ChunkMesh( ) noexcept = default;

	private:
		uint32_t	  faces		  = 0;
		uint32_t	  m_index	  = 0; /* lolita lolita , cichi cichi bambita */
		bool		  m_hasMesh	  = false;
		bool		  m_hasLoaded = false;
		Mesh		  m_mesh;
		Model		  m_model;
		ChunkSection *m_pChunk = nullptr; /* pointer to the current chunk */

		void		   makeFace( const Vertices_t &blockFace, const glm::vec2 &textureCoords, const Block_t &blockPosition, const AdjacentBlock &adjBlock );
		NODISCARD bool shouldMakeFace( const Block_t &blockCoords, const AdjacentBlock &adjCoords ) const noexcept;
		NODISCARD bool shouldMakeLayer( const int y ) const noexcept;
		void		   addFace( const Vertices_t &face, const Textures_t &texturesCoords, const Chunk_t &chunkPosition, const Block_t &blockPosition );
	};
} // namespace Nocturn::rendering
#endif