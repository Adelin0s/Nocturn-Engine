#include <queue>
#include <unordered_set>

#include "rendering/world/chunk/chunkmanager.h"

#include "application/input/keyboard.h"
#include "core/math/math.hpp"
#include "rendering/renderer/chunkrenderer.h"

namespace Nocturn
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

	NChunkManager::NChunkManager( NTaskSystem &taskSystem ) noexcept :
		m_pTaskSystem( &taskSystem ),
		m_renderDistance( 2 )
	{
		m_noiseParams.octaves	 = 20;
		m_noiseParams.amplitude	 = 80;
		m_noiseParams.smoothness = 400;
		m_noiseParams.offset	 = 10;
		m_noiseParams.roughness	 = 0.51;

		/*m_noiseParams.octaves	 = 0;
		m_noiseParams.amplitude	 = 20;
		m_noiseParams.smoothness = 0;
		m_noiseParams.offset	 = 10;
		m_noiseParams.roughness	 = 0.51;*/

		for( int x = 0; x < 10; x++ )
		for( int z = 0; z < 10; z++ )
		{
			m_pendingChunks.emplace_back( [ =, Self = this ]( ) -> void
			{
				Self->GenerateChunkMesh( { x, z } );
			} );
		}
	}

	const ChunkSection &NChunkManager::operator[]( const ivec2 &Index ) const noexcept
	{
		return Chunks.at(Index);
	}

	ChunkSection* NChunkManager::GetChunk(const vec3& WorldPosition) noexcept
	{
		const auto ChunkPosition = Math::ToChunkCoords(WorldPosition);
		if (!Chunks.contains(ChunkPosition))
		{
			LogWarning("Failed to get chunk from world position: [%f %f %f]!", WorldPosition.x, WorldPosition.y, WorldPosition.z);
			return nullptr;
		}

		return &Chunks[ ChunkPosition ];
	}

	ChunkSection* NChunkManager::GetChunk( const ivec2 &ChunkPosition ) noexcept
	{
		if (!Chunks.contains(ChunkPosition))
		{
			LogWarning("Failed to get chunk from chunk position: [%f %f %f]!", ChunkPosition.x, ChunkPosition.y);
			return nullptr;
		}

		return &Chunks[ ChunkPosition ];
	}

	NBlock NChunkManager::GetBlock( const vec3 &WorldPosition ) noexcept
	{
		const auto CurrentChunk = GetChunk( WorldPosition );
		if (CurrentChunk == nullptr)
		{
			LogWarning("Failed to get chunk from world position: [%f %f %f]!", WorldPosition.x, WorldPosition.y, WorldPosition.z);
			return EBlockId::Air;
		}

		const auto blockPosition = Math::ToBlockCoords( WorldPosition );
		return CurrentChunk->GetBlock( blockPosition );
	}

	void NChunkManager::SetBlock( const EBlockId BlockId, const vec3 &WorldPosition ) noexcept
	{
		const auto chunkPosition = Math::ToChunkCoords( WorldPosition );
		auto Chunk = GetChunk( chunkPosition );
		if (Chunk == nullptr)
		{
			LogError("Failed to get chunk from world position (%.2f, %.2f, %.2f)", WorldPosition);
			return;
		}

		Chunk->DeleteMesh( );
		Chunk->SetBlock( BlockId, WorldPosition );
		m_pendingChunks.emplace_back( [ Chunk ]( ) -> void
		{
			Chunk->CreateChunk( );
		} );
	}

	void NChunkManager::GenerateChunkMesh( const ivec2 &ChunkPosition ) noexcept
	{
		AdjacentChunk adjacentChunk{ ChunkPosition };
		ChunkSection  middleChunk{ ChunkPosition };
		auto *pMiddleChunk = &middleChunk;

		if( Chunks.contains( ChunkPosition ) )
		{
			pMiddleChunk = &Chunks[ ChunkPosition ];
		}

		// Top Chunk
		if( !Chunks.contains( adjacentChunk.front ) )
		{
			Chunks.emplace( adjacentChunk.front, ChunkSection{ adjacentChunk.front } );
			auto &chunk = Chunks[ adjacentChunk.front ];
			GenerateNewChunk( chunk );
			pMiddleChunk->SetNeighbor( NeighborType::Front, chunk );
		}
		else
		{
			auto &chunk = Chunks[ adjacentChunk.front ];
			pMiddleChunk->SetNeighbor( NeighborType::Front, chunk );
		}

		// Bottom Chunk
		if( !Chunks.contains( adjacentChunk.back ) )
		{
			Chunks.emplace( adjacentChunk.back, ChunkSection{ adjacentChunk.back } );
			auto &chunk = Chunks[ adjacentChunk.back ];
			GenerateNewChunk( chunk );
			pMiddleChunk->SetNeighbor( NeighborType::Back, chunk );
		}
		else
		{
			auto &chunk = Chunks[ adjacentChunk.back ];
			pMiddleChunk->SetNeighbor( NeighborType::Back, chunk );
		}

		// Left Chunk
		if( !Chunks.contains( adjacentChunk.left ) )
		{
			Chunks.emplace( adjacentChunk.left, ChunkSection{ adjacentChunk.left } );
			auto &chunk = Chunks[ adjacentChunk.left ];
			GenerateNewChunk( chunk );
			pMiddleChunk->SetNeighbor( NeighborType::Left, chunk );
		}
		else
		{
			auto &chunk = Chunks[ adjacentChunk.left ];
			pMiddleChunk->SetNeighbor( NeighborType::Left, chunk );
		}

		// Right Chunk
		if( !Chunks.contains( adjacentChunk.right ) )
		{
			Chunks.emplace( adjacentChunk.right, ChunkSection{ adjacentChunk.right } );
			auto &chunk = Chunks[ adjacentChunk.right ];
			GenerateNewChunk( chunk );
			pMiddleChunk->SetNeighbor( NeighborType::Right, chunk );
		}
		else
		{
			auto &chunk = Chunks[ adjacentChunk.right ];
			pMiddleChunk->SetNeighbor( NeighborType::Right, chunk );
		}

		if( !Chunks.contains( ChunkPosition ) )
		{
			Chunks.emplace( ChunkPosition, middleChunk );
			pMiddleChunk = &Chunks[ ChunkPosition ]; // take the pointer from Chunks map not from the local chunk
		}
		GenerateNewChunk( *pMiddleChunk, true );
		pMiddleChunk->SetRenderableChunk( );
	}

	int x = 1;
	int y = 35;

	void NChunkManager::Update(const double DeltaTime)
	{
		if( Keyboard::key(GLFW_KEY_O) )
		{
			auto* Chunk = GetChunk({0, 1});
			Chunk->DeleteMesh();
			Chunk->SetBlock(EBlockId::Sand, 2, 44, 19);
			Chunk->CreateChunk();
		}

		for( const auto& chunk : m_pendingChunks )
		{
			chunk();
		}
		m_pendingChunks.clear();

		if( Keyboard::keyWentDown(GLFW_KEY_B) )
		{
			auto& chunk = Chunks[ { 0, 0 } ];
			chunk.DeleteMesh();
			chunk.SetBlock(EBlockId::Air, 3, y--, 1);
			chunk.CreateChunk();
		}

		if( Keyboard::keyWentDown(GLFW_KEY_LEFT_CONTROL) )
		{
			auto& chunk = Chunks[ { 0, 0 } ];
			chunk.DeleteMesh();
			chunk.SetBlock(EBlockId::Stone, x++, 35, 1);
			chunk.CreateChunk();
		}

		if( Keyboard::keyWentDown(GLFW_KEY_C) )
		{
			auto& chunk = Chunks[ { 1, 1 } ];
			chunk.DeleteMesh();
			chunk.CreateChunk();
		}

		for( const auto& [ first, second ] : Chunks )
		{
			if( Chunks[ first ].HasMesh() && !Chunks[ first ].HasLoaded() )
			{
				Chunks[ first ].LoadBufferData();
			}
		}
	}

	//void NChunkManager::UpdateBlockLight()
	//{
	//	std::queue< std::pair< ivec3, uint8 > > LightQueue; // Queue of blocks with light to update
	//	std::unordered_set< ivec3 >				Visited;  // Set of already visited blocks

	//	// Add light sources to the queue
	//	for( const auto& [ Position, Chunk ] : Chunks )
	//	{
	//		for( int x = 0; x < Constants::CChunkX; x++ )
	//		{
	//			for( int y = 0; y < Constants::CChunkY; y++ )
	//			{
	//				for( int z = 0; z < Constants::CChunkZ; z++ )
	//				{
	//					const auto& Block = Chunk.GetBlock(x, y, z);
	//					if (Block != EBlockId::Air)
	//					{
	//						if( Block.BlockLight.Level > 0 )
	//						{
	//							// Get in world block position
	//							const auto BlockPos = ivec3( Chunk.GetLocation().x, 0,  Chunk.GetLocation().y) * Constants::CChunkSize + ivec3{x, y, z};
	//	                        LightQueue.emplace(BlockPos, Block.BlockLight.Level);
	//	                        Visited.emplace(BlockPos);
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}

	//	// Propagate light
	//	while( !LightQueue.empty() )
	//	{
	//		auto [ Position, Level ] = LightQueue.front();
	//		LightQueue.pop();

	//		// Update block light level
	//		const auto& Chunk = GetChunk({Position.x, Position.z});
	//		auto& BlockLight = Chunk.GetLight(Position.x + Chunk.GetPosition().x * Constants::CChunkSize.x, Position.y, Position.z + Chunk.GetPosition().y * Constants::CChunkSize.z);
	//		if( BlockLight.level < Level )
	//		{
	//			BlockLight.level = Level;
	//			Chunk.SetDirty();
	//		}

	//		// Add neighboring blocks to the queue
	//		for( const auto& Offset : Constants::CNeighborOffsets )
	//		{
	//			auto NeighborPosition	   = Position + Offset;
	//			auto NeighborChunkPosition = GetChunkPosition(NeighborPosition);

	//			// Check if neighboring block is in the same chunk
	//			if( NeighborChunkPosition == Chunk.GetPosition() )
	//			{
	//				auto& NeighborBlockLight = Chunk.GetLight(NeighborPosition - Chunk.GetPosition() * Constants::CChunkSize);
	//				if( NeighborBlockLight.level < Level - Constants::CBlockLightDecay )
	//				{
	//					NeighborBlockLight.level = Level - Constants::CBlockLightDecay;
	//					LightQueue.emplace(NeighborPosition, NeighborBlockLight.level);
	//				}
	//			}
	//			else
	//			{
	//				auto NeighborChunkIter = Chunks.find(NeighborChunkPosition);
	//				if( NeighborChunkIter != Chunks.end() )
	//				{
	//					auto& NeighborChunk		 = NeighborChunkIter->second;
	//					auto& NeighborBlockLight = NeighborChunk.GetLight(NeighborPosition - NeighborChunk.GetPosition() * Constants::CChunkSize);
	//					if( NeighborBlockLight.level < Level - Constants::CBlockLightDecay )
	//					{
	//						NeighborBlockLight.level = Level - Constants::CBlockLightDecay;
	//						LightQueue.emplace(NeighborPosition, NeighborBlockLight.level);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	void NChunkManager::GenerateNewChunk( ChunkSection &chunk, const bool shouldToCreateMesh ) noexcept
	{
		const Noise noise( m_noiseParams, 2432 );
		const auto pchunk = chunk.GetLocation( );
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
						chunk.SetBlock( EBlockId::Grass, px, py, pz );
					else if( py < max / 4 )
						chunk.SetBlock( EBlockId::Stone, px, py, pz );
					else
						chunk.SetBlock( EBlockId::Dirt, px, py, pz );
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
			chunk.CreateChunk( );
		}
	}

	void NChunkManager::GenerateTree( ChunkSection &chunk, const int px, const int pymax, const int pz )
	{
		const auto leaf1 = pymax + 4;
		const auto leaf2 = pymax + 5;
		const auto leaf3 = pymax + 6;

		chunk.SetBlock(EBlockId::OakBark, px, pymax, pz);
		chunk.SetBlock(EBlockId::OakBark, px, pymax + 1, pz);
		chunk.SetBlock(EBlockId::OakBark, px, pymax + 2, pz);
		chunk.SetBlock(EBlockId::OakBark, px, pymax + 3, pz);

		chunk.SetBlock(EBlockId::OakLeaf, px - 1, leaf1, pz - 1);
		chunk.SetBlock(EBlockId::OakLeaf, px, leaf1, pz - 1);
		chunk.SetBlock(EBlockId::OakLeaf, px + 1, leaf1, pz - 1);
		chunk.SetBlock(EBlockId::OakLeaf, px - 1, leaf1, pz);
		chunk.SetBlock(EBlockId::OakLeaf, px, leaf1, pz);
		chunk.SetBlock(EBlockId::OakLeaf, px + 1, leaf1, pz);
		chunk.SetBlock(EBlockId::OakLeaf, px - 1, leaf1, pz + 1);
		chunk.SetBlock(EBlockId::OakLeaf, px, leaf1, pz + 1);
		chunk.SetBlock(EBlockId::OakLeaf, px + 1, leaf1, pz + 1);

		chunk.SetBlock(EBlockId::OakLeaf, px - 1, leaf2, pz - 1);
		chunk.SetBlock(EBlockId::OakLeaf, px, leaf2, pz - 1);
		chunk.SetBlock(EBlockId::OakLeaf, px + 1, leaf2, pz - 1);
		chunk.SetBlock(EBlockId::OakLeaf, px - 1, leaf2, pz);
		chunk.SetBlock(EBlockId::OakLeaf, px, leaf2, pz);
		chunk.SetBlock(EBlockId::OakLeaf, px + 1, leaf2, pz);
		chunk.SetBlock(EBlockId::OakLeaf, px - 1, leaf2, pz + 1);
		chunk.SetBlock(EBlockId::OakLeaf, px, leaf2, pz + 1);
		chunk.SetBlock(EBlockId::OakLeaf, px + 1, leaf2, pz + 1);

		chunk.SetBlock(EBlockId::OakLeaf, px - 1, leaf3, pz - 1);
		chunk.SetBlock(EBlockId::OakLeaf, px, leaf3, pz - 1);
		chunk.SetBlock(EBlockId::OakLeaf, px + 1, leaf3, pz - 1);
		chunk.SetBlock(EBlockId::OakLeaf, px - 1, leaf3, pz);
		chunk.SetBlock(EBlockId::OakLeaf, px, leaf3, pz);
		chunk.SetBlock(EBlockId::OakLeaf, px + 1, leaf3, pz);
		chunk.SetBlock(EBlockId::OakLeaf, px - 1, leaf3, pz + 1);
		chunk.SetBlock(EBlockId::OakLeaf, px, leaf3, pz + 1);
		chunk.SetBlock(EBlockId::OakLeaf, px + 1, leaf3, pz + 1);
	}

	FChunkManagerRenderContext::FChunkManagerRenderContext(const NChunkManager* ChunkManagerIn) noexcept
	:
		ChunkManager(ChunkManagerIn)
	{
	}

	const ChunkMap& FChunkManagerRenderContext::GetChunkMap() const noexcept
	{
		return ChunkManager->Chunks;
	}
} // namespace Nocturn