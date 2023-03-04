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

#include "rendering/Renderer/Data/model.hpp"
#include "rendering/world/block/block.h"
#include "rendering/world/block/blockdatabase.h"
#include "rendering/world/chunk/chunkmesh.h"
#include "core/components/constants.hpp"

namespace Nocturn::rendering
{
	// Use std::vector instead of std::unordered_map because we need to init 16*16*256 block directly
	// All of those blocks will be initialized with BlockId::Air
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
			return static_cast< uint32 >( m_numberOfBlocks ) == Constants::CChunkBase;
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

		void SetBlock( BlockId blockId, const ivec3 &worldPosition ) noexcept;
		void SetBlock( BlockId blockId, int32 worldX, int32 worldY, int32 worldZ ) noexcept;
		void SetNeighbor( NeighborType type, ChunkSection &chunk ) noexcept;
		void SetRenderableChunk( ) noexcept;
		void SetChunkMaxY( const uint8 maxy ) noexcept
		{
			m_maxy = maxy;
		}

		NODISCARD ivec2                       getLocation( ) const;
		NODISCARD const Render::RenderInfo&   GetRenderInfo( ) const;
		NODISCARD const std::vector< Block >& getChunk( ) const;
		NODISCARD ChunkLayer                  getLayer( int y ) const;
		NODISCARD uint8                       GetChunkMaxY( ) const noexcept
		{
			return m_maxy;
		}
		NODISCARD Block						  getBlock( int32_t x, int32_t y, int32_t z ) const noexcept;
		NODISCARD Block						  getBlock( const ivec3 &coords ) const noexcept;
		NODISCARD Block						  getAdjacentBlock( const ivec3 &coords ) const noexcept;
		NODISCARD ChunkSection*				  tryGetNeighbor( NeighborType type ) const noexcept;
		NODISCARD bool						  hasMesh( ) const noexcept;
		NODISCARD bool						  hasLoaded( ) const noexcept;
		NODISCARD bool						  shouldToRender( ) const noexcept;
		NODISCARD bool						  isRenderable( ) const noexcept;

		void createChunk( );
		void loadBufferData( );
		void DeleteMesh( ) noexcept;

		static NODISCARD constexpr size_t getSizeOfBlock( ) noexcept;
		static NODISCARD uint32			  getSizeFromIndex( uint32 x, uint32 y, uint32 z ) noexcept;
		static NODISCARD uint32			  getSizeFromIndex( const ivec3 &vec ) noexcept;
		static NODISCARD ivec3			  getIndexFromSize( uint32 size ) noexcept;

		~ChunkSection( ) noexcept = default;

	private:
		std::array< ChunkLayer, Constants::CChunkY > m_layers;
		std::vector< Block >						 m_chunk;

		ChunkMesh m_mesh;
		Neighbor  m_neighbor;
		ivec2	  m_location; /* chunk position */
		bool	  m_renderableChunk = false;
		uint8	  m_maxy;

		static bool outOfBound( int32_t x, int32_t y, int32_t z ) noexcept;
	};
} // namespace Nocturn::rendering

#endif