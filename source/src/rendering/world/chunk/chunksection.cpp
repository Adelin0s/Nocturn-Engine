#include "rendering/world/chunk/chunksection.h"
#include "rendering/world/block/block.h"

#include "core/math/noise.h"
#include "core/math/math.hpp"

namespace Nocturn::rendering
{
	ChunkSection::ChunkSection( const ivec2 &location ) :
		m_chunk( Constants::CChunkSize ),
		m_location( location )
	{
	}

	Block ChunkSection::operator[]( const ivec3 &position ) const noexcept
	{
		return m_chunk[ getSizeFromIndex( position ) ];
	}

	/**
	 * \brief Normalize from WorldPosition to BlockPosition and set the Block to BlockId
	 * \param blockId: block id
	 * \param worldX: world position X
	 * \param worldY: world position Y
	 * \param worldZ: world position Z
	 */
	void ChunkSection::SetBlock( const BlockId blockId, const int32 worldX, const int32 worldY, const int32 worldZ ) noexcept
	{
		// Normalize to chunk coords
		const auto &chunkPosition = Math::ToBlockCoords( worldX, worldY, worldZ );
		SetBlock( blockId, chunkPosition );
	}

	/**
	 * \brief Normalize from WorldPosition to BlockPosition and set the Block to BlockId
	 * \param blockId: block id 
	 * \param worldPosition: world position vec3(x,y,z)
	 */
	void ChunkSection::SetBlock( const BlockId blockId, const ivec3 &worldPosition ) noexcept
	{
		// Normalize to chunk coords
		const auto &position = Math::ToBlockCoords( worldPosition );
		const auto block = m_chunk[ getSizeFromIndex( position ) ];

		if( BlockId::Air == block && BlockId::Air != blockId )
			m_layers[ position.y ].Increase( );

		if( BlockId::Air != block && BlockId::Air == blockId )
			m_layers[ position.y ].Decrease( );

		m_chunk[ getSizeFromIndex( position ) ] = blockId;
	}

	void ChunkSection::SetNeighbor( const NeighborType type, ChunkSection &chunk ) noexcept
	{
		if( NeighborType::Left == type )
		{
			m_neighbor.left = &chunk;
		}
		else if( NeighborType::Right == type )
		{
			m_neighbor.right = &chunk;
		}
		else if( NeighborType::Front == type )
		{
			m_neighbor.top = &chunk;
		}
		else if( NeighborType::Back == type )
		{
			m_neighbor.bottom = &chunk;
		}
	}

	void ChunkSection::SetRenderableChunk( ) noexcept
	{
		m_renderableChunk = true;
	}

	ChunkSection *ChunkSection::tryGetNeighbor( const NeighborType type ) const noexcept
	{
		if( type == NeighborType::Left && m_neighbor.left )
			return m_neighbor.left;

		if( type == NeighborType::Right && m_neighbor.right )
			return m_neighbor.right;

		if( type == NeighborType::Front && m_neighbor.top )
			return m_neighbor.top;

		if( type == NeighborType::Back && m_neighbor.bottom )
			return m_neighbor.bottom;

		return nullptr;
	}

	ivec2 ChunkSection::getLocation( ) const
	{
		return m_location;
	}

	const std::vector< Block > &ChunkSection::getChunk( ) const
	{
		return m_chunk;
	}

	NODISCARD ChunkLayer ChunkSection::getLayer( const int y ) const
	{
		return m_layers[ y ];
	}

	NODISCARD Block ChunkSection::getBlock( const int32_t x, const int32_t y, const int32_t z ) const noexcept
	{
		if( outOfBound( x, y, z ) )
			return BlockId::Air;
		return m_chunk[ getSizeFromIndex( x, y, z ) ];
	}

	NODISCARD Block ChunkSection::getBlock( const ivec3 &coords ) const noexcept
	{
		if( outOfBound( coords.x, coords.y, coords.z ) )
			return BlockId::Air;
		return m_chunk[ getSizeFromIndex( coords ) ];
	}

	NODISCARD Block ChunkSection::getAdjacentBlock( const ivec3 &coords ) const noexcept
	{
		const auto px = coords.x;
		const auto py = coords.y;
		const auto pz = coords.z;

		if( px == -1 )
		{
			const auto &neighbor = tryGetNeighbor( NeighborType::Back );

			assert( neighbor != nullptr );

			return neighbor->getBlock( Constants::CChunkX- 1, py, pz );
		}
		if( px == Constants::CChunkX )
		{
			const auto &neighbor = tryGetNeighbor( NeighborType::Front );

			assert( neighbor != nullptr );

			return neighbor->getBlock( 0, py, pz );
		}
		if( pz == -1 )
		{
			const auto &neighbor = tryGetNeighbor( NeighborType::Left );

			assert( neighbor != nullptr );

			return neighbor->getBlock( px, py, Constants::CChunkZ - 1 );
		}
		if( pz == Constants::CChunkZ )
		{
			const auto &neighbor = tryGetNeighbor( NeighborType::Right );

			assert( neighbor != nullptr );

			return neighbor->getBlock( px, py, 0 );
		}

		return getBlock( px, py, pz );
	}

	NODISCARD constexpr size_t ChunkSection::getSizeOfBlock( ) noexcept
	{
		return sizeof( Block );
	}

	/// <summary>
	/// Return size from (x, y, z) to chunk position (uint32)
	/// </summary>
	/// <param name="x">column</param>
	/// <param name="y">height</param>
	/// <param name="z">row</param>
	/// <returns>uint32 size</returns>
	NODISCARD uint32 ChunkSection::getSizeFromIndex( const uint32 x, const uint32 y, const uint32 z ) noexcept
	{
		return z * 16 + y * 256 + x;
	}

	/// <summary>
	/// Return a size from (ivec3) to chunk position
	/// </summary>
	/// <param name="vec">vec3 stands for chunk position</param>
	/// <returns>uint32 stands for size of current chunk</returns>
	NODISCARD uint32 ChunkSection::getSizeFromIndex( const ivec3 &vec ) noexcept
	{
		return vec.z * 16 + vec.y * 256 + vec.x;
	}

	NODISCARD ivec3 ChunkSection::getIndexFromSize( const uint32 size ) noexcept
	{
		const auto pz = size % Constants::CChunkY;
		return { pz % Constants::CChunkZ, pz / Constants::CChunkX, pz };
	}

	NODISCARD bool ChunkSection::hasMesh( ) const noexcept
	{
		return m_mesh.HasMesh( );
	}

	bool ChunkSection::hasLoaded( ) const noexcept
	{
		return m_mesh.HasLoaded( );
	}

	bool ChunkSection::shouldToRender( ) const noexcept
	{
		return hasMesh( ) && m_renderableChunk;
	}

	bool ChunkSection::isRenderable( ) const noexcept
	{
		return m_renderableChunk;
	}

	const RenderInfo &ChunkSection::GetRenderInfo( ) const
	{
		return m_mesh.GetModel( ).GetRenderInfo( );
	}

	void ChunkSection::createChunk( )
	{
		m_mesh.MakeMesh( *this );
	}

	void ChunkSection::loadBufferData( )
	{
		m_mesh.LoadBufferData( );
	}

	void ChunkSection::DeleteMesh( ) noexcept
	{
		m_mesh.DeleteMesh( );
	}

	void ChunkSection::render( ) const
	{
		BlockDatabase::getInstance( ).textureAtlas.bind( );
		GL::BindVao( m_mesh.GetModel( ).GetRenderInfo( ).vao );
		GL::DrawElements( m_mesh.GetIndicesSize( ) );
	}

	bool ChunkSection::outOfBound( const int32_t x, const int32_t y, const int32_t z ) noexcept
	{
		if( x < 0 || x >= Constants::CChunkX || y < 0 || y >= Constants::CChunkY || z < 0 || z >= Constants::CChunkZ )
			return true;
		return false;
	}
} // namespace Nocturn::rendering