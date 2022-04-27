#include "rendering/world/chunk/chunkmanager.h"

#include "core/math/math.hpp"

namespace Nocturn::rendering
{
	ChunkManager::ChunkManager( const Camera &camera ) noexcept :
		m_renderDistance( 2 )
	{
		m_pendingChunks.reserve( CMaxPendingChunks );

		m_noiseParams.octaves	 = 9;
		m_noiseParams.amplitude	 = 80;
		m_noiseParams.smoothness = 500;
		m_noiseParams.offset	 = 10;
		m_noiseParams.roughness	 = 0.51;

		InitInitialChunks( );
	}

	void ChunkManager::InitInitialChunks( ) noexcept
	{
		for( int32_t x = 0; x < 10; x++ )
			for( int32_t z = 0; z < 10; z++ )
			{
				m_pendingChunks.emplace_back( ivec2( x, z ) );
			}
	}

	void ChunkManager::LoadPendingChunks( const ivec3 &currentPosition )
	{
		const auto px = static_cast< int >( currentPosition.x / CHUNK_X );
		const auto pz = static_cast< int >( currentPosition.z / CHUNK_Z );

		const Noise noise( m_noiseParams, 2432 );

		if( px != m_lastPosition.x || pz != m_lastPosition.z ) // unique position
		{
			if( !m_mapChunks[ { px, pz } ].hasMesh( ) )
			{
				m_pendingChunks.emplace_back( ivec2( px, pz ) );
				m_pendingChunks.emplace_back( ivec2( px, pz + 1 ) );
				m_pendingChunks.emplace_back( ivec2( px, pz + 2 ) );
				m_pendingChunks.emplace_back( ivec2( px, pz + 3 ) );
				m_pendingChunks.emplace_back( ivec2( px, pz + 4 ) );
				m_pendingChunks.emplace_back( ivec2( px, pz + 5 ) );
			}
			m_lastPosition.x = px;
			m_lastPosition.z = pz;
		}
	}

	void ChunkManager::ThreadUpdate( const ivec3 &currentPosition )
	{
		// LoadPendingChunks( currentPosition );

		for( const auto &pchunk : m_pendingChunks )
		{
			m_mapChunks.insert( { pchunk, ChunkSection( Chunk_t( pchunk.x, 0, pchunk.y ) ) } );
			// m_pool.PushTask( [ & ]
			//{ GenerateNewChunk( m_mapChunks[ pchunk ] ); } );
		}
		m_pendingChunks.clear( );

		for( const auto &[ first, second ] : m_mapChunks )
		{
			if( m_mapChunks[ first ].hasMesh( ) )
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
		const Noise noise( m_noiseParams, 2432 );

		const auto pchunk = static_cast< ivec3 >( chunk.getLocation( ) );

		for( int32 px = 0; px < CHUNK_X; px++ )
		{
			for( int32 pz = 0; pz < CHUNK_X; pz++ )
			{
				const auto max = static_cast< int32 >( noise.getHeight( px, pz, pchunk.x, pchunk.z ) );
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
	}

} // namespace Nocturn::rendering