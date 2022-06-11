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
#include "rendering/data/model.h"

namespace Nocturn::rendering
{
	class ChunkSection;
	class ChunkMesh;
	struct Block;
	struct BlockDataHolder;

	struct AdjacentBlock
	{
		void update( const uint32_t x, const uint32_t y, const uint32_t z );

		ivec3 top;
		ivec3 bottom;
		ivec3 left;
		ivec3 right;
		ivec3 front;
		ivec3 back;
	};

	enum class FaceType
	{
		Up = 0,
		Down,
		Left,
		Right,
		Back,
		Front
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
		void				   DeleteMesh( ) noexcept;

		~ChunkMesh( ) noexcept = default;

	private:
		uint32_t	  m_faces	  = 0;
		uint32_t	  m_index	  = 0; /* lolita lolita , cichi cichi bambita */
		bool		  m_hasMesh	  = false;
		bool		  m_hasLoaded = false;
		Mesh		  m_mesh;
		Model		  m_model;
		ChunkSection *m_pChunk = nullptr; /* pointer to the current chunk */

		void		   makeFace( const Vertices_t &blockFace, const glm::vec2 &textureCoords, const Block_t &blockPosition, const ivec3 &adjBlock );
		NODISCARD bool shouldMakeFace( const Block_t &blockCoords, const ivec3 &adjCoords ) const noexcept;
		NODISCARD bool shouldPassLayer( const int32 y ) const noexcept;
		void		   addFace( const Vertices_t &face, const Textures_t &texturesCoords, const ivec2 &chunkPosition, const Block_t &blockPosition );
	};
} // namespace Nocturn::rendering
#endif