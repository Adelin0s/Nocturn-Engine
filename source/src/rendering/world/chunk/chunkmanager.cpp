#include "rendering/world/chunk/chunkmanager.h"

#include "core/math/math.hpp"

namespace Nocturn::rendering
{
	FORCE_INLINE AdjacentChunk::AdjacentChunk( const int32 x, const int32 z ) noexcept
	{
		top	   = { x, z + 1 };
		bottom = { x, z - 1 };
		left   = { x - 1, z };
		right  = { x + 1, z };
	}

	FORCE_INLINE AdjacentChunk::AdjacentChunk( const ivec2 &vec ) noexcept
	{
		top	   = { vec.x, vec.y + 1 };
		bottom = { vec.x, vec.y - 1 };
		left   = { vec.x - 1, vec.y };
		right  = { vec.x + 1, vec.y };
	}

	ChunkManager::ChunkManager( TaskSystem &taskSystem ) noexcept :
		m_pTaskSystem( &taskSystem ),
		m_renderDistance( 2 )
	{
		m_noiseParams.octaves	 = 9;
		m_noiseParams.amplitude	 = 80;
		m_noiseParams.smoothness = 500;
		m_noiseParams.offset	 = 10;
		m_noiseParams.roughness	 = 0.51;

		LoadChunkNeighbors( { 0, 3 } );
	}

	void ChunkManager::LoadPendingChunks( const ivec3 &currentPosition )
	{
		const auto px = currentPosition.x / CHUNK_X;
		const auto pz = currentPosition.z / CHUNK_Z;

		const Noise noise( m_noiseParams, 2432 );

		if( px != m_lastPosition.x || pz != m_lastPosition.z ) // unique position
		{
			if( m_mapChunks.contains( { px, pz } ) && !m_mapChunks[ { px, pz } ].hasMesh( ) )
			{
				m_pendingChunks.emplace_back( ivec2( px, pz ) );
			}
			m_lastPosition.x = px;
			m_lastPosition.z = pz;
		}
	}

	// TODO : Find a way to process firstly neighbors chunk and after that process main chunk(current chunk)
	// the way is currently to process the chunks by one thread (instead of multi-threading)
	void ChunkManager::LoadChunkNeighbors( const ivec2 &chunkPosition ) noexcept
	{
		AdjacentChunk adjacentChunk{ chunkPosition };

		ChunkSection middleChunk{ chunkPosition };
		ChunkSection chunkLeft{ adjacentChunk.left };
		ChunkSection chunkRight{ adjacentChunk.right };
		ChunkSection chunkTop{ adjacentChunk.top };
		ChunkSection chunkBottom{ adjacentChunk.bottom };

		// set current chunk's neighbors
		middleChunk.setNeighbor( NeighborType::Left, chunkLeft );
		middleChunk.setNeighbor( NeighborType::Right, chunkRight );
		middleChunk.setNeighbor( NeighborType::Top, chunkTop );
		middleChunk.setNeighbor( NeighborType::Bottom, chunkBottom );

		// make sure that the neighbors have set the middle neighbor
		chunkLeft.setNeighbor( NeighborType::Right, middleChunk );
		chunkRight.setNeighbor( NeighborType::Left, middleChunk );
		chunkTop.setNeighbor( NeighborType::Bottom, middleChunk );
		chunkBottom.setNeighbor( NeighborType::Top, middleChunk );

		// update m_pending with chunk vec2 positions and insert current chunk and its neighbors
		if( !m_mapChunks.contains( adjacentChunk.top ) )
		{
			m_mapChunks.emplace( adjacentChunk.top, chunkTop );
			m_pendingChunks.emplace_back( adjacentChunk.top );
		}

		if( !m_mapChunks.contains( adjacentChunk.bottom ) )
		{
			m_mapChunks.emplace( adjacentChunk.bottom, chunkBottom );
			m_pendingChunks.emplace_back( adjacentChunk.bottom );
		}

		if( !m_mapChunks.contains( adjacentChunk.left ) )
		{
			m_mapChunks.emplace( adjacentChunk.left, chunkLeft );
			m_pendingChunks.emplace_back( adjacentChunk.left );
		}

		if( !m_mapChunks.contains( adjacentChunk.right ) )
		{
			m_mapChunks.emplace( adjacentChunk.right, chunkRight );
			m_pendingChunks.emplace_back( adjacentChunk.right );
		}

		if( !m_mapChunks.contains( chunkPosition ) )
		{
			m_mapChunks.emplace( chunkPosition, middleChunk );
			m_pendingChunks.emplace_back( chunkPosition );
		}
	}

	void ChunkManager::Update( const ivec3 &currentPosition )
	{
		// LoadPendingChunks( currentPosition );

		for( const auto &pchunk : m_pendingChunks )
		{
			if( !m_mapChunks[ pchunk ].hasMesh( ) )
			{
				std::cout << pchunk.x << ' ' << pchunk.y << ' ';
				// m_pTaskSystem->Async( [ & ]
				//{ GenerateNewChunk( m_mapChunks[ pchunk ] ); } );
				GenerateNewChunk( m_mapChunks[ pchunk ] );
			}
		}
		m_pendingChunks.clear( );

		for( const auto &[ first, second ] : m_mapChunks )
		{
			if( m_mapChunks[ first ].hasMesh( ) && !m_mapChunks[ first ].hasLoaded( ) )
			{
				m_mapChunks[ first ].loadBufferData( );
			}
		}
	}

	void ChunkManager::Render( const Camera &camera, ChunkRendering &chunkRender )
	{
		for( const auto &[ first, second ] : m_mapChunks )
		{
			if( m_mapChunks[ first ].hasMesh( ) )
			{
				chunkRender.add( second.getRenderInfo( ) );
			}
		}
		chunkRender.render( camera );
	}

	void ChunkManager::GenerateNewChunk( ChunkSection &chunk ) const noexcept
	{
		// WARNING ! : Multi-threading section
		const Noise noise( m_noiseParams, 2432 );

		const auto pchunk = chunk.getLocation( );

		for( int32 px = 0; px < CHUNK_X; px++ )
		{
			for( int32 pz = 0; pz < CHUNK_X; pz++ )
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

		chunk.createChunk( );

		std::cout << "\nExit";
	}
} // namespace Nocturn::rendering