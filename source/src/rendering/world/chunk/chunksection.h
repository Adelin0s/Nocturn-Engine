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
	// use std::vector instead of std::unordered_map because we need to init 16*16*256 block directly
	// all of those blocks will be initialized with BlockId::Air
	struct ChunkLayer
	{
		ChunkLayer( ) :
			m_numberOfBlocks( 0 )
		{}

		void Increase( ) noexcept
		{
			++m_numberOfBlocks;
		}

		void Decrease( ) noexcept
		{
			--m_numberOfBlocks;
		}

		NODISCARD bool IsAllSolid( ) const
		{
			return static_cast< uint32 >( m_numberOfBlocks ) == CHUNK_BASE;
		}

		NODISCARD auto getNumberOfBlocks( ) const noexcept
		{
			return m_numberOfBlocks;
		}

	private:
		uint16 m_numberOfBlocks;
	};

	enum class NeighborType : uint8
	{
		Left = 0,
		Right,
		Front,
		Back
	};

	struct Neighbor
	{
		ChunkSection *left	 = nullptr;
		ChunkSection *right	 = nullptr;
		ChunkSection *top	 = nullptr;
		ChunkSection *bottom = nullptr;
	};

	struct AdjacentChunk
	{
		AdjacentChunk( const int32 x, const int32 z ) noexcept;
		AdjacentChunk( const ivec2 &vec ) noexcept;

		ivec2 front;
		ivec2 back;
		ivec2 left;
		ivec2 right;
	};

	class ChunkSection
	{
	public:
		ChunkSection( ) noexcept = default;
		explicit ChunkSection( const ivec2 &location );
		// TODO: Investigate the behavior of the default constructor
		ChunkSection( const ChunkSection &chunk ) = default;
		ChunkSection( ChunkSection &&chunk )	  = delete;

		ChunkSection &operator=( const ChunkSection &chunk ) = delete;
		ChunkSection &operator=( ChunkSection &&chunk ) = delete;

		Block operator[]( const ivec3 &position ) const noexcept;

		void setBlock( const BlockId id, const ivec3 &position );
		void setBlock( const BlockId id, const int32 x, const int32 y, const int32 z );
		void setNeighbor( const NeighborType type, ChunkSection &chunk ) noexcept;
		void setRenderableChunk( ) noexcept;

		NODISCARD ivec2				getLocation( ) const;
		NODISCARD const RenderInfo &getRenderInfo( ) const;
		NODISCARD const std::vector< Block > &getChunk( ) const;
		NODISCARD ChunkLayer				  getLayer( const int y ) const;
		NODISCARD Block						  getBlock( const int32_t x, const int32_t y, const int32_t z ) const noexcept;
		NODISCARD Block						  getBlock( const ivec3 &coords ) const noexcept;
		NODISCARD Block						  getAdjacentBlock( const ivec3 &coords ) const noexcept;
		NODISCARD ChunkSection			   *tryGetNeighbor( const NeighborType type ) const noexcept;
		NODISCARD bool						  hasMesh( ) const noexcept;
		NODISCARD bool						  hasLoaded( ) const noexcept;
		NODISCARD bool						  shouldToRender( ) const noexcept;
		NODISCARD bool						  isRenderable( ) const noexcept;

		void createChunk( );
		void loadBufferData( );
		void DeleteMesh( ) noexcept;
		void render( ) const;

		static NODISCARD constexpr size_t getSizeOfBlock( ) noexcept;
		static NODISCARD uint32			  getSizeFromIndex( const uint32 x, const uint32 y, const uint32 z ) noexcept;
		static NODISCARD uint32			  getSizeFromIndex( const ivec3 &vec ) noexcept;
		static NODISCARD ivec3			  getIndexFromSize( const uint32 size ) noexcept;

		~ChunkSection( ) noexcept = default;

	private:
		std::vector< Block >			  m_chunk;
		ChunkMesh						  m_mesh;
		Neighbor						  m_neighbor;
		std::array< ChunkLayer, CHUNK_Y > m_layers;
		ivec2							  m_location; /* chunk position */
		bool							  m_renderableChunk = false;

		static bool outOfBound( const int32_t x, const int32_t y, const int32_t z ) noexcept;
	};
} // namespace Nocturn::rendering

#endif