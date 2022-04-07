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

		InitInitialChunks( camera );
	}

	void ChunkManager::InitInitialChunks( const Camera &camera )
	{
		const Noise noise( m_noiseParams, 2432 );

		for( int32_t x = 0; x < 10; x++ )
			for( int32_t z = 0; z < 10; z++ )
			{
				GenerateNewChunk( noise, x, z );
			}
		m_pendingChunks.clear( );
	}

	void ChunkManager::LoadFutureChunks( const Camera &camera )
	{
		const auto px = static_cast< int >( camera.getCameraPosition( ).x / CHUNK_X );
		const auto pz = static_cast< int >( camera.getCameraPosition( ).z / CHUNK_Z );

		const Noise noise( m_noiseParams, 2432 );

		if( px != m_lastPosition.x || pz != m_lastPosition.z ) // unique position
		{
			GenerateNewChunk( noise, px, pz );

			m_lastPosition.x = px;
			m_lastPosition.z = pz;
		}
	}

	void ChunkManager::InitTasks( )
	{
		for( const auto &chunk : m_mapChunks )
		{
			if( !chunk.second.hasMesh( ) )
			{
				m_pool.PushTask( [ & ]
								 { m_mapChunks[ chunk.first ].createChunk( ); } );
			}
		}
	}

	void ChunkManager::ThreadUpdate( )
	{
		/*for( const auto &chunk : m_updateChunks )
		{
			m_activeChunks.insert( chunk );

			m_pool.PushTask( [ & ]
							 { m_activeChunks[ chunk.first ].createChunk( ); } );
		}*/

		for( const auto &chunk : m_pendingChunks )
		{
			m_pool.PushTask( [ & ]
							 { m_mapChunks[ chunk ].createChunk( ); } );
		}
		m_pendingChunks.clear( );

		int32 cnt = 0;
		for( const auto &[ first, second ] : m_mapChunks )
		{
			if( m_mapChunks[ first ].hasMesh( ) )
			{
				++cnt;
				m_mapChunks[ first ].loadBufferData( );
			}
		}
	}

	void ChunkManager::Render( const Camera &camera, ChunkRendering &chunkRender )
	{
		uint32 c = 0;
		for( const auto &[ first, second ] : m_mapChunks )
		{
			if( m_mapChunks[ first ].hasMesh( ) )
			{
				chunkRender.add( second.getRenderInfo( ) );
				++c;
			}
		}
		std::cout << "Task executed: " << c << '\n';
		chunkRender.render( camera );
	}

	void ChunkManager::GenerateNewChunk( const Noise &noise, const int32 chunk_x, const int32 chunk_z ) noexcept
	{
		ChunkSection chunk( Chunk_t( chunk_x, 0, chunk_z ) );

		for( int32 px = 0; px < CHUNK_X; px++ )
		{
			for( int32 pz = 0; pz < CHUNK_X; pz++ )
			{
				// get max-value for each block of Y chunk
				const auto max = static_cast< int32 >( noise.getHeight( px, pz, chunk_x, chunk_z ) );
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
		m_mapChunks.insert( { { chunk_x, chunk_z }, chunk } );
		m_pendingChunks.emplace_back( ivec2( chunk_x, chunk_z ) );
	}

} // namespace Nocturn::rendering