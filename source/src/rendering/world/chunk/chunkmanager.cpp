#include "rendering/world/chunk/chunkmanager.h"

#include "application/input/keyboard.h"
#include "core/math/math.hpp"

namespace Nocturn::rendering
{
	FORCE_INLINE AdjacentChunk::AdjacentChunk( const int32 x, const int32 z ) noexcept
	{
		front = { x + 1, z };
		back  = { x - 1, z };
		left  = { x, z - 1 };
		right = { x, z + 1 };
	}

	FORCE_INLINE AdjacentChunk::AdjacentChunk( const ivec2 &vec ) noexcept
	{
		front = { vec.x + 1, vec.y };
		back  = { vec.x - 1, vec.y };
		left  = { vec.x, vec.y - 1 };
		right = { vec.x, vec.y + 1 };
	}

	ChunkManager::ChunkManager( TaskSystem &taskSystem ) noexcept :
		m_pTaskSystem( &taskSystem ),
		m_renderDistance( 2 )
	{
		/*m_noiseParams.octaves	 = 9;
		m_noiseParams.amplitude	 = 80;
		m_noiseParams.smoothness = 500;
		m_noiseParams.offset	 = 10;
		m_noiseParams.roughness	 = 0.51;*/

		m_noiseParams.octaves	 = 20;
		m_noiseParams.amplitude	 = 80;
		m_noiseParams.smoothness = 400;
		m_noiseParams.offset	 = 10;
		m_noiseParams.roughness	 = 0.51;

		for( int x = 0; x < 1; x++ )
			for( int z = 0; z < 1; z++ )
			{
				m_pendingChunks.emplace_back( [ =, Self = this ]( )
											  { Self->GenerateChunkMesh( { x, z } ); } );
			}
	}

	const ChunkSection &ChunkManager::operator[]( const ivec2 &index ) noexcept
	{
		return m_mapChunks[ index ];
	}

	ChunkSection &ChunkManager::GetChunk( const ivec2 &index )
	{
		return m_mapChunks[ index ];
	}

	/// <summary>
	///	TODO: Need to update!!! Really? :))
	///	This function generates the current chunk and its 4 neighbors(left, right, top and bottom).
	///	The main idea was to generate the current chunk and its neighbors and then render only the current chunk.
	///	Whether the current chunk was generated or not(it already exists) it is marked as a renderable chunk.
	/// </summary>
	/// <param name="chunkPosition">The current chunk's position</param>
	void ChunkManager::GenerateChunkMesh( const ivec2 &chunkPosition ) noexcept
	{
		AdjacentChunk adjacentChunk{ chunkPosition };
		ChunkSection  middleChunk{ chunkPosition };
		auto *pMiddleChunk = &middleChunk;

		if( m_mapChunks.contains( chunkPosition ) )
		{
			pMiddleChunk = &m_mapChunks[ chunkPosition ];
		}

		// Top Chunk
		if( !m_mapChunks.contains( adjacentChunk.front ) )
		{
			m_mapChunks.emplace( adjacentChunk.front, ChunkSection{ adjacentChunk.front } );
			auto &chunk = m_mapChunks[ adjacentChunk.front ];
			GenerateNewChunk( chunk );
			pMiddleChunk->setNeighbor( NeighborType::Front, chunk );
		}
		else
		{
			auto &chunk = m_mapChunks[ adjacentChunk.front ];
			pMiddleChunk->setNeighbor( NeighborType::Front, chunk );
		}

		// Bottom Chunk
		if( !m_mapChunks.contains( adjacentChunk.back ) )
		{
			m_mapChunks.emplace( adjacentChunk.back, ChunkSection{ adjacentChunk.back } );
			auto &chunk = m_mapChunks[ adjacentChunk.back ];
			GenerateNewChunk( chunk );
			pMiddleChunk->setNeighbor( NeighborType::Back, chunk );
		}
		else
		{
			auto &chunk = m_mapChunks[ adjacentChunk.back ];
			pMiddleChunk->setNeighbor( NeighborType::Back, chunk );
		}

		// Left Chunk
		if( !m_mapChunks.contains( adjacentChunk.left ) )
		{
			m_mapChunks.emplace( adjacentChunk.left, ChunkSection{ adjacentChunk.left } );
			auto &chunk = m_mapChunks[ adjacentChunk.left ];
			GenerateNewChunk( chunk );
			pMiddleChunk->setNeighbor( NeighborType::Left, chunk );
		}
		else
		{
			auto &chunk = m_mapChunks[ adjacentChunk.left ];
			pMiddleChunk->setNeighbor( NeighborType::Left, chunk );
		}

		// Right Chunk
		if( !m_mapChunks.contains( adjacentChunk.right ) )
		{
			m_mapChunks.emplace( adjacentChunk.right, ChunkSection{ adjacentChunk.right } );
			auto &chunk = m_mapChunks[ adjacentChunk.right ];
			GenerateNewChunk( chunk );
			pMiddleChunk->setNeighbor( NeighborType::Right, chunk );
		}
		else
		{
			auto &chunk = m_mapChunks[ adjacentChunk.right ];
			pMiddleChunk->setNeighbor( NeighborType::Right, chunk );
		}

		if( !m_mapChunks.contains( chunkPosition ) )
		{
			m_mapChunks.emplace( chunkPosition, middleChunk );
			pMiddleChunk = &m_mapChunks[ chunkPosition ]; // take the pointer from m_mapChunks map not from the local chunk
		}
		GenerateNewChunk( *pMiddleChunk, true );
		pMiddleChunk->setRenderableChunk( );
	}

	int x = 1;
	int y = 35;

	void ChunkManager::Update( const ivec3 &currentPosition )
	{
		for( const auto &chunk : m_pendingChunks )
		{
			chunk( );
		}
		m_pendingChunks.clear( );

		if( Keyboard::keyWentDown( GLFW_KEY_B ) )
		{
			auto &chunk = m_mapChunks[ { 0, 0 } ];
			chunk.DeleteMesh( ); 
			chunk.setBlock( BlockId::Air, 3, y--, 1 );
			chunk.createChunk( );
		}

		if( Keyboard::keyWentDown( GLFW_KEY_LEFT_CONTROL) )
		{
			auto &chunk = m_mapChunks[ { 0, 0 } ];
			chunk.DeleteMesh( );
			chunk.setBlock( BlockId::OakBark, x++, 35, 1 );
			chunk.createChunk( );
		}

		for( const auto &[ first, second ] : m_mapChunks )
		{
			if( m_mapChunks[ first ].hasMesh( ) && !m_mapChunks[ first ].hasLoaded( ) )
			{
				m_mapChunks[ first ].loadBufferData( );
			}
		}
	}

	// TODO: Should to seperate Render function?
	void ChunkManager::Render( const Camera &camera, Frustum &frustum, ChunkRendering &chunkRender )
	{
		for( const auto &[ first, second ] : m_mapChunks )
		{
			if( m_mapChunks[ first ].shouldToRender( ) )
			{
				// auto renderInfo = second.getRenderInfo( );
				chunkRender.Add( second.getRenderInfo( ) );
			}
		}
		chunkRender.Render( camera );
	}

	void ChunkManager::GenerateNewChunk( ChunkSection &chunk, const bool shouldToCreateMesh ) const noexcept
	{
		const Noise noise( m_noiseParams, 2432 );
		const auto pchunk = chunk.getLocation( );
		for( int32 px = 0; px < Constants::CChunkX; px++ )
		{
			for( int32 pz = 0; pz < Constants::CChunkZ; pz++ )
			{
				const auto max = static_cast< int32 >( noise.getHeight( px, pz, pchunk[ 0 ], pchunk[ 1 ] ) );
				for( int32 py = 0; py < max; py++ )
				{
					if( py == max - 1 )
						chunk.setBlock( BlockId::Grass, px, py, pz );
					else if( py < max / 4 )
						chunk.setBlock( BlockId::Stone, px, py, pz );
					else
						chunk.setBlock( BlockId::Dirt, px, py, pz );
				}
			}
		}

		if( shouldToCreateMesh )
		{
			chunk.createChunk( );
		}
	}
} // namespace Nocturn::rendering