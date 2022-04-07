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

#include "rendering/data/model.h"
#include "rendering/world/block/block.h"
#include "rendering/world/block/blockdatabase.h"
#include "rendering/world/chunk/chunkmesh.h"
#include "rendering/world/worldconstants.h"

namespace Nocturn::rendering
{
	using ChunkBlockMap = std::unordered_map< ivec3, Block >;

	struct ChunkLayer
	{
		void Update( ) noexcept
		{
			m_numberOfBlocks++;
		}

		NODISCARD bool IsAllSolid( ) const
		{
			return m_numberOfBlocks == CHUNK_SIDE;
		}

	private:
		uint8_t m_numberOfBlocks = 0;
	};

	class ChunkSection
	{
	public:
		ChunkSection( ) noexcept = default;
		explicit ChunkSection( const glm::vec3 &location );
		ChunkSection( const ChunkSection &chunk ) = default;
		ChunkSection( ChunkSection &&chunk )	  = delete;

		ChunkSection &operator=( const ChunkSection &chunk ) = delete;
		ChunkSection &operator=( ChunkSection &&chunk ) = delete;

		void setBlock( const BlockId id, const glm::ivec3 &position );
		void setBlock( const BlockId id, const int32 x, const int32 y, const int32 z );

		NODISCARD vec3				   getLocation( ) const;
		NODISCARD const RenderInfo	   &getRenderInfo( ) const;
		NODISCARD const ChunkBlockMap &getChunk( ) const;
		NODISCARD ChunkLayer		   getLayer( const int y ) const noexcept;
		NODISCARD Block				   getBlock( const int32_t x, const int32_t y, const int32_t z );
		NODISCARD Block				   getBlock( const glm::ivec3 &coords );
		NODISCARD size_t			   getSizeOfBlockArray( ) const noexcept;
		NODISCARD size_t			   getSizeOfBlock( ) const noexcept;
		NODISCARD bool				   hasMesh( ) const noexcept;

		void createChunk( );
		void loadBufferData( );
		void render( ) const;

		~ChunkSection( ) noexcept = default;

	private:
		std::vector< Block >			  m_blocks;
		std::array< ChunkLayer, CHUNK_Y > m_layers;
		ChunkBlockMap					  m_chunk;
		ChunkMesh						  m_mesh;
		glm::vec3						  m_location; /* chunk position */

		static bool outOfBound( const int32_t x, const int32_t y, const int32_t z ) noexcept;
	};
} // namespace Nocturn::rendering

#endif