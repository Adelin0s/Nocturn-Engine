#include "rendering/world/chunk/chunkmesh.h"

#include "rendering/world/block/block.h"

#include "rendering/world/block/blockdatabase.h"
#include "rendering/world/block/blockdataholder.hpp"
#include "rendering/world/chunk/chunksection.h"
#include "rendering/world/worldconstants.h"

namespace // block faces coords
{
	const std::array< float, 12 > frontFace{
		0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1
	};

	const std::array< float, 12 > backFace{
		1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0
	};

	const std::array< float, 12 > leftFace{
		0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0
	};

	const std::array< float, 12 > rightFace{
		1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1
	};

	const std::array< float, 12 > topFace{
		0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0
	};

	const std::array< float, 12 > bottomFace{
		0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1
	};
} // namespace

namespace Nocturn::rendering
{
	inline void AdjacentBlock::update( const uint32_t x, const uint32_t y, const uint32_t z )
	{
		top	   = { x, y + 1, z };
		bottom = { x, y - 1, z };
		left   = { x - 1, y, z };
		right  = { x + 1, y, z };
		front  = { x, y, z + 1 };
		back   = { x, y, z - 1 };
	}

	ChunkMesh::ChunkMesh( ChunkSection &chunk ) :
		m_pChunk( &chunk )
	{}

	NODISCARD const Model &ChunkMesh::getModel( ) const
	{
		return m_model;
	}

	NODISCARD uint32 ChunkMesh::getIndicesSize( ) const noexcept
	{
		return static_cast< uint32 >( m_mesh.indices.size( ) );
	}

	void ChunkMesh::makeMesh( ChunkSection &pchunk )
	{
		// We don't need to generate where our chunk's neighbors have all blocks solid.
		// Can continue because the current layer is basically hidden in real scenario.
		m_pChunk = &pchunk;
		AdjacentBlock directions;

		auto chunk = m_pChunk->getChunk( );

		uint32 cnt = 0;
		for( int32 z = 0; z < CHUNK_Z; z++ )
			for( int32 y = 0; y < CHUNK_Y; y++ )
			{
				for( int32 x = 0; x < CHUNK_X; x++ )
				{
					if( shouldPassLayer( y ) )
					{
						continue;
					}

					const auto &data = chunk[ ChunkSection::getSizeFromIndex( x, y, z ) ].getData( );

					const Block_t position( x, y, z );
					directions.update( x, y, z );

					/* Up/Down */
					makeFace( topFace, data.m_textureTop, position, directions.top );
					makeFace( bottomFace, data.m_textureBottom, position, directions.bottom );

					/* Left/Right */
					makeFace( leftFace, data.m_textureSide, position, directions.left );
					makeFace( rightFace, data.m_textureSide, position, directions.right );

					/* Back/Front */
					makeFace( backFace, data.m_textureSide, position, directions.back );
					makeFace( frontFace, data.m_textureSide, position, directions.front );
				}
			}
		m_hasMesh = true; // flag to know if the buffer data can be loaded
	}

	void ChunkMesh::loadBufferData( )
	{
		if( m_hasMesh && !m_hasLoaded )
		{
			m_model.addData( m_mesh );
			m_hasLoaded = true;
		}
	}

	NODISCARD bool ChunkMesh::hasMesh( ) const noexcept
	{
		return m_hasMesh;
	}

	NODISCARD bool ChunkMesh::hasLoaded( ) const noexcept
	{
		return m_hasLoaded;
	}

	void ChunkMesh::DeleteMesh( ) noexcept
	{
		if( m_hasMesh )
		{
			m_index		= 0;
			m_faces		= 0;
			m_hasLoaded = false;
			m_hasMesh	= false;

			m_mesh.clear( );
			m_model.deleteData( );
		}
	}

	void ChunkMesh::makeFace( const Vertices_t &blockFace, const glm::vec2 &textureCoords, const Block_t &blockPosition, const ivec3 &adjBlock )
	{
		if( shouldMakeFace( blockPosition, adjBlock ) )
		{
			const auto &texture = BlockDatabase::getInstance( ).textureAtlas.getTexture( textureCoords );
			addFace( blockFace, texture, m_pChunk->getLocation( ), blockPosition );
		}
	}

	NODISCARD bool ChunkMesh::shouldMakeFace( const Block_t &blockCoords, const ivec3 &adjCoords ) const noexcept
	{
		if( m_pChunk->getBlock( blockCoords ) == BlockId::Air )
			return false;

		if( m_pChunk->getAdjacentBlock( adjCoords ) != BlockId::Air )
		{
			return false;
		}

		return true;
	}

	/// <summary>
	/// Checks if the neighbors have all the blocks set on the current layer y
	/// </summary>
	/// <param name="y">current layer</param>
	/// <returns>True if all blocks are set or False</returns>
	NODISCARD bool ChunkMesh::shouldPassLayer( const int32 y ) const noexcept
	{
		if( y + 1 < CHUNK_Y && !m_pChunk->getLayer( y + 1 ).IsAllSolid( ) )
		{
			return false;
		}

		if( const auto neighbor = m_pChunk->tryGetNeighbor( NeighborType::Left ); nullptr != neighbor )
		{
			if( !neighbor->getLayer( y ).IsAllSolid( ) )
			{
				// std::cout << neighbor->getLayer( y ).getNumberOfBlocks( ) << ' ';
				return false;
			}
		}

		if( const auto neighbor = m_pChunk->tryGetNeighbor( NeighborType::Right ); nullptr != neighbor )
		{
			if( !neighbor->getLayer( y ).IsAllSolid( ) )
			{
				// std::cout << neighbor->getLayer( y ).getNumberOfBlocks( ) << ' ';
				return false;
			}
		}

		if( const auto neighbor = m_pChunk->tryGetNeighbor( NeighborType::Front ); nullptr != neighbor )
		{
			if( !neighbor->getLayer( y ).IsAllSolid( ) )
			{
				// std::cout << neighbor->getLayer( y ).getNumberOfBlocks( ) << ' ';
				return false;
			}
		}

		if( const auto neighbor = m_pChunk->tryGetNeighbor( NeighborType::Back ); nullptr != neighbor )
		{
			if( !neighbor->getLayer( y ).IsAllSolid( ) )
			{
				// std::cout << neighbor->getLayer( y ).getNumberOfBlocks( ) << ' ';
				return false;
			}
		}

		return true;
	}

	void ChunkMesh::addFace( const Vertices_t &face, const Textures_t &texturesCoords, const ivec2 &chunkPosition, const Block_t &blockPosition )
	{
		m_faces++;

		auto &indices  = m_mesh.indices;
		auto &vertices = m_mesh.vertices;
		auto &textures = m_mesh.textures;

		indices.insert( indices.end( ), { m_index, m_index + 1, m_index + 2, m_index + 2, m_index + 3, m_index } );
		m_index += 4;

		/* we have 4 set of vertices with 3 coords x, y, z  */
		for( uint32_t i = 0, index = 0; i < 4; i++ )
		{
			vertices.push_back( face[ index++ ] + chunkPosition[ 0 ] * CHUNK_X + blockPosition.x );
			vertices.push_back( face[ index++ ] + blockPosition.y );
			vertices.push_back( face[ index++ ] + chunkPosition[ 1 ] * CHUNK_Z + blockPosition.z );
		}
		textures.insert( textures.end( ), texturesCoords.begin( ), texturesCoords.end( ) );
	}
} // namespace Nocturn::rendering