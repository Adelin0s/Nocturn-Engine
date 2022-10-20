#include "rendering/world/chunk/chunkmanager.h"

#include "application/input/keyboard.h"
#include "core/math/math.hpp"
#include "core/logging/logging.h"

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
		/*m_noiseParams.octaves	 = 20;
		m_noiseParams.amplitude	 = 80;
		m_noiseParams.smoothness = 400;
		m_noiseParams.offset	 = 10;
		m_noiseParams.roughness	 = 0.51;*/

		m_noiseParams.octaves	 = 0;
		m_noiseParams.amplitude	 = 20;
		m_noiseParams.smoothness = 0;
		m_noiseParams.offset	 = 10;
		m_noiseParams.roughness	 = 0.51;

		for( int x = 0; x < 10; x++ )
		for( int z = 0; z < 10; z++ )
		{
			m_pendingChunks.emplace_back( [ =, Self = this ]( ) -> void
			{
				Self->GenerateChunkMesh( { x, z } );
			} );
		}
	}

	const ChunkSection &ChunkManager::operator[]( const ivec2 &index ) noexcept
	{
		return m_mapChunks[ index ];
	}

	ChunkSection &ChunkManager::GetChunk( const vec3 &worldPosition ) noexcept
	{
		const auto chunkPosition = Math::ToChunkCoords( worldPosition );
		return m_mapChunks[ chunkPosition ];
	}

	ChunkSection &ChunkManager::GetChunk( const ivec2 &chunkPosition ) noexcept
	{
		return m_mapChunks[ chunkPosition ];
	}

	Block ChunkManager::GetBlock( const vec3 &worldPosition ) noexcept
	{
		const auto &chunk = GetChunk( worldPosition );
		const auto blockPosition = Math::ToBlockCoords( worldPosition );
		return chunk.getBlock( blockPosition );
	}

	/**
	 * \brief This function set a block depending on BlockId & WorldPosition. Warning: This function is not thread safe!
	 * \param blockId the id of the block to be set
	 * \param worldPosition the world position block
	 */
	void ChunkManager::SetBlock( const BlockId blockId, const vec3 &worldPosition ) noexcept
	{
		const auto chunkPosition = Math::ToChunkCoords( worldPosition );
		auto &chunk = GetChunk( chunkPosition );
		chunk.DeleteMesh( );
		chunk.SetBlock( blockId, worldPosition );
		m_pendingChunks.emplace_back( [ &chunk ]( ) -> void
		{
			chunk.createChunk( );
		} );
	}

	/// <summary>
	///	TODO: Need to update!!! Really? :))
	///	This function generates the current chunk and its 4 neighbors(left, right, top and bottom).
	///	The main idea was to generate the current chunk and its neighbors then render only the current chunk.
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
			pMiddleChunk->SetNeighbor( NeighborType::Front, chunk );
		}
		else
		{
			auto &chunk = m_mapChunks[ adjacentChunk.front ];
			pMiddleChunk->SetNeighbor( NeighborType::Front, chunk );
		}

		// Bottom Chunk
		if( !m_mapChunks.contains( adjacentChunk.back ) )
		{
			m_mapChunks.emplace( adjacentChunk.back, ChunkSection{ adjacentChunk.back } );
			auto &chunk = m_mapChunks[ adjacentChunk.back ];
			GenerateNewChunk( chunk );
			pMiddleChunk->SetNeighbor( NeighborType::Back, chunk );
		}
		else
		{
			auto &chunk = m_mapChunks[ adjacentChunk.back ];
			pMiddleChunk->SetNeighbor( NeighborType::Back, chunk );
		}

		// Left Chunk
		if( !m_mapChunks.contains( adjacentChunk.left ) )
		{
			m_mapChunks.emplace( adjacentChunk.left, ChunkSection{ adjacentChunk.left } );
			auto &chunk = m_mapChunks[ adjacentChunk.left ];
			GenerateNewChunk( chunk );
			pMiddleChunk->SetNeighbor( NeighborType::Left, chunk );
		}
		else
		{
			auto &chunk = m_mapChunks[ adjacentChunk.left ];
			pMiddleChunk->SetNeighbor( NeighborType::Left, chunk );
		}

		// Right Chunk
		if( !m_mapChunks.contains( adjacentChunk.right ) )
		{
			m_mapChunks.emplace( adjacentChunk.right, ChunkSection{ adjacentChunk.right } );
			auto &chunk = m_mapChunks[ adjacentChunk.right ];
			GenerateNewChunk( chunk );
			pMiddleChunk->SetNeighbor( NeighborType::Right, chunk );
		}
		else
		{
			auto &chunk = m_mapChunks[ adjacentChunk.right ];
			pMiddleChunk->SetNeighbor( NeighborType::Right, chunk );
		}

		if( !m_mapChunks.contains( chunkPosition ) )
		{
			m_mapChunks.emplace( chunkPosition, middleChunk );
			pMiddleChunk = &m_mapChunks[ chunkPosition ]; // take the pointer from m_mapChunks map not from the local chunk
		}
		GenerateNewChunk( *pMiddleChunk, true );
		pMiddleChunk->SetRenderableChunk( );
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
			chunk.SetBlock( BlockId::Air, 3, y--, 1 );
			chunk.createChunk( );
		}

		if( Keyboard::keyWentDown( GLFW_KEY_LEFT_CONTROL) )
		{
			auto &chunk = m_mapChunks[ { 0, 0 } ];
			chunk.DeleteMesh( );
			chunk.SetBlock( BlockId::Stone, x++, 35, 1 );
			chunk.createChunk( );
		}

		if (Keyboard::keyWentDown( GLFW_KEY_C ))
		{
			auto &chunk = m_mapChunks[ { 1, 1 } ];
			chunk.DeleteMesh( );
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
		for( const auto &[ position, chunk ] : m_mapChunks )
		{
			if( m_mapChunks[ position ].shouldToRender( ) )
			{
				const auto maxy = chunk.GetChunkMaxY( );
				const auto minView = vec3(position[0] * Constants::CChunkX, maxy, position[1] * Constants::CChunkZ);
				if( frustum.IsBoxVisible( minView, minView + vec3( 16.0f ) ) )
				{
					 //auto renderInfo = second.getRenderInfo( );
					chunkRender.Add( chunk.GetRenderInfo( ) );
				}
			}
		}
		//std::cout << "Size-rendered:" << chunkRender.Size( ) << '\n';
		chunkRender.Render( camera );
	}

	void ChunkManager::GenerateNewChunk( ChunkSection &chunk, const bool shouldToCreateMesh ) noexcept
	{
		const Noise noise( m_noiseParams, 2432 );
		const auto pchunk = chunk.getLocation( );
		uint8 max = 0;
		uint8 ymax = 0;
		for( int32 px = 0; px < Constants::CChunkX; px++ )
		{
			for( int32 pz = 0; pz < Constants::CChunkZ; pz++ )
			{
				max = static_cast< uint8 >( noise.getHeight( px, pz, pchunk[ 0 ], pchunk[ 1 ] ) );
				int32 py;
				for( py = 0; py < max; py++ )
				{
					if( py == max - 1 )
						chunk.SetBlock( BlockId::Grass, px, py, pz );
					else if( py < max / 4 )
						chunk.SetBlock( BlockId::Stone, px, py, pz );
					else
						chunk.SetBlock( BlockId::Dirt, px, py, pz );
				}
				if( max > ymax )
					ymax = max;
				if ( 1 == std::rand() % 150 )
				{
					// generate tree
					GenerateTree( chunk, px, py, pz );
				}
			}
		}
		chunk.SetChunkMaxY( max );
		if( shouldToCreateMesh )
		{
			chunk.createChunk( );
		}
	}

	void ChunkManager::GenerateTree( ChunkSection &chunk, const int px, const int pymax, const int pz )
	{
		const auto leaf1 = pymax + 4;
		const auto leaf2 = pymax + 5;
		const auto leaf3 = pymax + 6;

		chunk.SetBlock( BlockId::OakBark, px, pymax, pz );
		chunk.SetBlock( BlockId::OakBark, px, pymax + 1, pz );
		chunk.SetBlock( BlockId::OakBark, px, pymax + 2, pz );
		chunk.SetBlock( BlockId::OakBark, px, pymax + 3, pz );

		chunk.SetBlock( BlockId::OakLeaf, px - 1, leaf1, pz - 1 );
		chunk.SetBlock( BlockId::OakLeaf, px,	  leaf1, pz - 1 );
		chunk.SetBlock( BlockId::OakLeaf, px + 1, leaf1, pz - 1 );
		chunk.SetBlock( BlockId::OakLeaf, px - 1, leaf1, pz );
		chunk.SetBlock( BlockId::OakLeaf, px,     leaf1, pz );
		chunk.SetBlock( BlockId::OakLeaf, px + 1, leaf1, pz );
		chunk.SetBlock( BlockId::OakLeaf, px - 1, leaf1, pz + 1 );
		chunk.SetBlock( BlockId::OakLeaf, px,     leaf1, pz + 1 );
		chunk.SetBlock( BlockId::OakLeaf, px + 1, leaf1, pz + 1 );

		chunk.SetBlock( BlockId::OakLeaf, px - 1, leaf2, pz - 1 );
		chunk.SetBlock( BlockId::OakLeaf, px,	  leaf2, pz - 1 );
		chunk.SetBlock( BlockId::OakLeaf, px + 1, leaf2, pz - 1 );
		chunk.SetBlock( BlockId::OakLeaf, px - 1, leaf2, pz );
		chunk.SetBlock( BlockId::OakLeaf, px,     leaf2, pz );
		chunk.SetBlock( BlockId::OakLeaf, px + 1, leaf2, pz );
		chunk.SetBlock( BlockId::OakLeaf, px - 1, leaf2, pz + 1 );
		chunk.SetBlock( BlockId::OakLeaf, px,     leaf2, pz + 1 );
		chunk.SetBlock( BlockId::OakLeaf, px + 1, leaf2, pz + 1 );

		chunk.SetBlock( BlockId::OakLeaf, px - 1, leaf3, pz - 1 );
		chunk.SetBlock( BlockId::OakLeaf, px,     leaf3, pz - 1 );
		chunk.SetBlock( BlockId::OakLeaf, px + 1, leaf3, pz - 1 );
		chunk.SetBlock( BlockId::OakLeaf, px - 1, leaf3, pz );
		chunk.SetBlock( BlockId::OakLeaf, px,     leaf3, pz );
		chunk.SetBlock( BlockId::OakLeaf, px + 1, leaf3, pz );
		chunk.SetBlock( BlockId::OakLeaf, px - 1, leaf3, pz + 1 );
		chunk.SetBlock( BlockId::OakLeaf, px,     leaf3, pz + 1 );
		chunk.SetBlock( BlockId::OakLeaf, px + 1, leaf3, pz + 1 );
	}

} // namespace Nocturn::rendering