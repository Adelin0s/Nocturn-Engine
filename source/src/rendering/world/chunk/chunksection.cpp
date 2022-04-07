#include "rendering/world/chunk/chunksection.h"
#include "rendering/world/block/block.h"

#include <iostream>

#include "core/math/noise.h"

namespace Nocturn::rendering
{
	ChunkSection::ChunkSection( const glm::vec3 &location ) :
		m_location( location )
	{
		m_blocks.reserve( CHUNK_SIZE );
	}

	void ChunkSection::setBlock( const BlockId id, const int32 x, const int32 y, const int32 z )
	{
		if( !outOfBound( x, y, z ) )
		{
			m_chunk.insert_or_assign( ivec3( x, y, z ), Block( id ) );
			m_layers[ y ].Update( );
		}
	}

	void ChunkSection::setBlock( const BlockId id, const glm::ivec3 &position )
	{
		if( !outOfBound( position.x, position.y, position.z ) )
		{
			m_chunk.insert_or_assign( position, Block( id ) );
			m_layers[ position.y ].Update( );
		}
	}

	glm::vec3 ChunkSection::getLocation( ) const
	{
		return m_location;
	}

	const ChunkBlockMap &ChunkSection::getChunk( ) const
	{
		return m_chunk;
	}

	NODISCARD ChunkLayer ChunkSection::getLayer( const int y ) const noexcept
	{
		return m_layers[ y ];
	}

	NODISCARD Block ChunkSection::getBlock( const int32_t x, const int32_t y, const int32_t z )
	{
		if( outOfBound( x, y, z ) )
			return BlockId::Air;
		return m_chunk[ ivec3( x, y, z ) ];
	}

	NODISCARD Block ChunkSection::getBlock( const glm::ivec3 &coords )
	{
		if( outOfBound( coords.x, coords.y, coords.z ) )
			return BlockId::Air;
		return m_chunk[ coords ];
	}

	NODISCARD size_t ChunkSection::getSizeOfBlockArray( ) const noexcept
	{
		return sizeof( m_blocks );
	}

	NODISCARD size_t ChunkSection::getSizeOfBlock( ) const noexcept
	{
		return sizeof( Block );
	}

	NODISCARD bool ChunkSection::hasMesh( ) const noexcept
	{
		return m_mesh.hasMesh( );
	}

	const RenderInfo &ChunkSection::getRenderInfo( ) const
	{
		return m_mesh.getModel( ).getRenderInfo( );
	}

	void ChunkSection::createChunk( )
	{
		m_mesh.makeMesh( *this );
	}

	void ChunkSection::loadBufferData( )
	{
		m_mesh.loadBufferData( );
	}

	void ChunkSection::render( ) const
	{
		BlockDatabase::getInstance( ).textureAtlas.bind( );
		GL::bindVAO( m_mesh.getModel( ).getRenderInfo( ).vao );
		GL::drawElements( m_mesh.getIndicesSize( ) );
	}

	bool ChunkSection::outOfBound( const int32_t x, const int32_t y, const int32_t z ) noexcept
	{
		if( x < 0 || x >= CHUNK_X || y < 0 || y >= CHUNK_Y || z < 0 || z >= CHUNK_Z )
			return true;
		return false;
	}
} // namespace Nocturn::rendering