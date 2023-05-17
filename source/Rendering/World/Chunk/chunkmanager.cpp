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

	void NChunkManager::CalculateLighting(const ivec2& PlayerChunkCoords)
	{
		for (int32 LightIteration = 0; LightIteration < 2; ++LightIteration)
		{
			for (int32 ChunkZ = PlayerChunkCoords.y - CChunkRadius; ChunkZ <= PlayerChunkCoords.y + CChunkRadius; ChunkZ++)
			{
				for (int32 ChunkX = PlayerChunkCoords.x - CChunkRadius; ChunkX <= PlayerChunkCoords.x + CChunkRadius; ChunkX++)
				{
					const int32 WorldChunkX = ChunkX * 16;
					const int32 WorldChunkZ = ChunkZ * 16;

					const ivec2 LocalChunkPos = glm::vec2(PlayerChunkCoords.x - ChunkX, PlayerChunkCoords.y - ChunkZ);
					const bool InRangeOfPlayer = (LocalChunkPos.x * LocalChunkPos.x) + (LocalChunkPos.y * LocalChunkPos.y) <= ((CChunkRadius) * (CChunkRadius));
					if (!InRangeOfPlayer)
					{
						// Skip over all chunks in range radius - 1
						continue;
					}

					const auto Chunk = GetChunk(vec3(WorldChunkX, 128.0f, WorldChunkZ));
					if (Chunk == nullptr)
					{
						continue;
					}

					if (!Chunk->ShouldCalculateLighting())
					{
						continue;
					}

					if (LightIteration == 0)
					{
						CalculateLightingChunkSky(Chunk, ivec2(ChunkX, ChunkZ));
					}
					else if (LightIteration == 1)
					{
						CalculateLightingChunk(Chunk, ivec2(ChunkX, ChunkZ));
						//chunk->needsToCalculateLighting = false;
					}
				}
			}
		}
	}

	void NChunkManager::CalculateLightingUpdate(ChunkSection* Chunk, const ivec2& ChunkCoordinates, const vec3& BlockPosition, const bool bRemovedLightSource, std::unordered_set<ChunkSection*>& ChunksToRetesselate)
	{
		const ivec3 LocalPosition = glm::floor(BlockPosition - vec3(ChunkCoordinates.x * 16.0f, 0.0f, ChunkCoordinates.y * 16.0f));
		const auto LocalX = LocalPosition.x;
		const auto LocalY = LocalPosition.y;
		const auto LocalZ = LocalPosition.z;
		const auto BlockThatsUpdating = Chunk->GetBlock(vec3(LocalX, LocalY, LocalZ));
		if (BlockThatsUpdating != EBlockId::Air && !bRemovedLightSource)
		{
			// Just placed a solid block
			std::queue<ivec3> BlocksToZero = {};
			std::queue<ivec3> BlocksToUpdate = {};
			BlocksToZero.push({ LocalX, LocalY, LocalZ });
			bool bIgnoreThisSolidBlock = true;
			// Zero out
			while (!BlocksToZero.empty())
			{
				RemoveNextLightLevel(Chunk, ChunkCoordinates, ChunksToRetesselate, BlocksToZero, BlocksToUpdate, bIgnoreThisSolidBlock);
				bIgnoreThisSolidBlock = false;
			}

			// Flood fill from all the light sources that were found
			while (!BlocksToUpdate.empty())
			{
				CalculateNextLightLevel(Chunk, ChunkCoordinates, ChunksToRetesselate, BlocksToUpdate);
			}

			BlocksToZero.push({ LocalX, LocalY, LocalZ });
			bIgnoreThisSolidBlock = true;
			// Zero out
			while (!BlocksToZero.empty())
			{
				RemoveNextSkyLevel(Chunk, ChunkCoordinates, ChunksToRetesselate, BlocksToZero, BlocksToUpdate, bIgnoreThisSolidBlock);
				bIgnoreThisSolidBlock = false;
			}

			// Flood fill from all the light sources that were found
			while (!BlocksToUpdate.empty())
			{
				CalculateNextSkyLevel(Chunk, ChunkCoordinates, ChunksToRetesselate, BlocksToUpdate);
			}
		}
		else if (bRemovedLightSource)
		{
			// Just removed a light source
			std::queue<ivec3> blocksToZero = {};
			std::queue<ivec3> blocksToUpdate = {};
			blocksToZero.push({ LocalX, LocalY, LocalZ });
			// Zero out
			while (!blocksToZero.empty())
			{
				RemoveNextLightLevel(Chunk, ChunkCoordinates, ChunksToRetesselate, blocksToZero, blocksToUpdate, false);
			}

			// Flood fill from all the light sources that were found
			while (!blocksToUpdate.empty())
			{
				CalculateNextLightLevel(Chunk, ChunkCoordinates, ChunksToRetesselate, blocksToUpdate);
			}
		}
		else if (BlockThatsUpdating != EBlockId::Air)
		{
			// Just added a light source
			std::queue< ivec3 > blocksToUpdate = {};
			blocksToUpdate.push({ LocalX, LocalY, LocalZ });
			const auto Block = GetBlock({ LocalX, LocalY, LocalZ });
			while( !blocksToUpdate.empty() )
			{
				CalculateNextLightLevel(Chunk, ChunkCoordinates, ChunksToRetesselate, blocksToUpdate);
			}
		}
		else
		{
			// Just removed a block
			std::queue<ivec3> blocksToUpdate = {};
			blocksToUpdate.push({ LocalX, LocalY, LocalZ });

			// My light level is now the max of all my neighbors minus one
			int myLightLevel = 0;
			int mySkyLevel = 0;
			for( int i = 0; i < FINormals3::CardinalDirections.size(); i++ )
			{
				const ivec3& Normal = FINormals3::CardinalDirections[i];
				const auto Block = GetBlock({LocalX + Normal.x, LocalY + Normal.y, LocalZ + Normal.z});
				if (Block.GetLight() - 1 > myLightLevel)
				{
					myLightLevel = Block.GetLight() - 1;
				}
				if (Block.GetSkyLight() - 1 > mySkyLevel)
				{
					mySkyLevel = Block.GetSkyLight() - 1;
				}

				// If the block above me is a sky block, I am also a sky block
				if (Block.GetSkyLight() - 1 == NBlock::CMaxLightLevel && Normal.y == 1)
				{
					mySkyLevel = NBlock::CMaxLightLevel;
				}
			}

			Chunk->SetLight({LocalX, LocalY, LocalZ}, myLightLevel);
			while (!blocksToUpdate.empty())
			{
				CalculateNextLightLevel(Chunk, ChunkCoordinates, ChunksToRetesselate, blocksToUpdate);
			}

			Chunk->SetSkyLight({LocalX, LocalY, LocalZ}, mySkyLevel);
			blocksToUpdate.push({ LocalX, LocalY, LocalZ });
			// If I was a sky block, set all transparent blocks below me to sky blocks
			if (mySkyLevel == NBlock::CMaxLightLevel)
			{
				for (int y = LocalY; y >= 0; y--)
				{
					const auto OtherBlock = GetBlock({LocalX, y, LocalZ});
					if (OtherBlock != EBlockId::Air)
					{
						break;
					}

					Chunk->SetSkyLight({ LocalX, y, LocalZ }, NBlock::CMaxLightLevel);
					blocksToUpdate.push({ LocalX, y, LocalZ });
				}
			}

			while (!blocksToUpdate.empty())
			{
				CalculateNextSkyLevel(Chunk, ChunkCoordinates, ChunksToRetesselate, blocksToUpdate);
			}
		}

		//for (auto chunkA : ChunksToRetesselate)
		//{
		//	for (auto chunkB : ChunksToRetesselate)
		//	{
		//		if (*chunkA != *chunkB)
		//		{
		//			if (chunkA->chunkCoords == chunkB->chunkCoords)
		//			{
		//				g_logger_warning("Duplicate, how did you get out of mother goose corner?!");
		//			}
		//		}
		//	}
		//}
	}

	void NChunkManager::GenerateNewChunk( ChunkSection &Chunk, const bool bShouldToCreateMesh ) noexcept
	{
		const Noise noise( m_noiseParams, 2432 );
		const auto pchunk = Chunk.GetLocation( );
		uint8 max = 0;
		uint8 ymax = 0;
		for( int32 px = 0; px < CChunkX; px++ )
		{
			for( int32 pz = 0; pz < CChunkZ; pz++ )
			{
				max = static_cast< uint8 >( noise.getHeight( px, pz, pchunk[ 0 ], pchunk[ 1 ] ) );
				int32 py;
				for( py = 0; py < max; py++ )
				{
					if( py == max - 1 )
						Chunk.SetBlock( EBlockId::Grass, px, py, pz );
					else if( py < max / 4 )
						Chunk.SetBlock( EBlockId::Stone, px, py, pz );
					else
						Chunk.SetBlock( EBlockId::Dirt, px, py, pz );
				}
				if( max > ymax )
					ymax = max;
				if ( 1 == std::rand() % 150 )
				{
					// generate tree
					GenerateTree( Chunk, px, py, pz );
				}
			}
		}
		Chunk.SetChunkMaxY( max );
		if( bShouldToCreateMesh )
		{
			Chunk.CreateChunk( );
		}
	}

	void NChunkManager::CalculateLightingChunkSky(ChunkSection* Chunk, const ivec2& ChunkCoordinates) const
	{
		for (int32 x = 0; x < CChunkX; x++)
		{
			for (int32 z = 0; z < CChunkZ; z++)
			{
				for (int32 y = CChunkY - 1; y >= 0; y--)
				{
					if (Chunk->GetBlock(x, y, z) != EBlockId::Air)
					{
						break;
					}

					// Set the block to the max light level since this has to be a sky block
					Chunk->SetSkyLight(vec3(x, y, z), NBlock::CMaxLightLevel);
				}
			}
		}
	}

	void NChunkManager::CalculateLightingChunk(ChunkSection* Chunk, const ivec2& ChunkCoordinates)
	{
		std::queue<ivec3> SkyBlocksToUpdate = {};
		for( int32 y = CChunkY - 1; y >= 0; y-- )
		{
			bool bAnyBlocksTransparent = false;
			for (int32 x = 0; x < CChunkX; x++)
			{
				for (int32 z = 0; z < CChunkZ; z++)
				{
					uint32 arrayExpansion = ChunkSection::GetSizeFromIndex(x, y, z);
					if (Chunk->GetBlock(x, y, z) != EBlockId::Air)
					{
						continue;
					}

					bAnyBlocksTransparent = true;
					if( Chunk->GetLight(vec3(x, y, z)) == 16 )
					{
						// If any of the horizontal neighbors is transparent and not a sky block, add this block
						// as a source
						
						for (size_t i = 0; i < FINormals3::CardinalDirectionsXZ.size(); ++i)
						{
							const auto BlockPosition = glm::highp_ivec3(x, y, z) + FINormals3::CardinalDirections[i];
							const auto Block = GetBlock(BlockPosition);
							if (Block == EBlockId::Air && Block.GetLight() != NBlock::CMaxLightLevel)
							{
								SkyBlocksToUpdate.push({ x, y, z });
								break;
							}
						}
					}
				}
			}

			if (!bAnyBlocksTransparent)
			{
				break;
			}
		}

		std::unordered_set< ChunkSection* > SkyChunksToRetesselate = {};
		while (!SkyBlocksToUpdate.empty())
		{
			CalculateNextSkyLevel(Chunk, ChunkCoordinates, SkyChunksToRetesselate, SkyBlocksToUpdate);
		}
	}

	void NChunkManager::CalculateNextLightLevel(ChunkSection* OriginalChunk, const ivec2& ChunkCoordinates, std::unordered_set<ChunkSection*>& ChunksToRetesselate, std::queue<ivec3>& BlocksToCheck)
	{
		const ivec3 BlockToUpdate = BlocksToCheck.front();
		BlocksToCheck.pop();

		if (!OriginalChunk)
		{
			LogWarning("Null chunk while updating block lighting!");
			return;
		}

		int32 BlockToUpdateX = BlockToUpdate.x;
		int32 BlockToUpdateY = BlockToUpdate.y;
		int32 BlockToUpdateZ = BlockToUpdate.z;
		ChunkSection* BlockToUpdateChunk = OriginalChunk;
		if (BlockToUpdateX >= CChunkX || BlockToUpdateX < 0 || BlockToUpdateZ >= CChunkZ || BlockToUpdateZ < 0)
		{
			if (!CheckPositionInBounds(*BlockToUpdateChunk, BlockToUpdateX, BlockToUpdateY, BlockToUpdateZ))
			{
				LogWarning("Position totally out of bounds...");
				return;
			}
			ChunksToRetesselate.insert(BlockToUpdateChunk);
		}

		if( !GetBlock(BlockToUpdate).IsTransparent() )
		{
			return;
		}

		const auto MyLightLevel = GetBlock(BlockToUpdate).GetLight();
		if (MyLightLevel > 0)
		{
			for (int i = 0; i < FINormals3::CardinalDirections.size(); i++)
			{
				const ivec3& iNormal = FINormals3::CardinalDirections[i];
				ivec3 Pos = ivec3(BlockToUpdateX + iNormal.x, BlockToUpdateY + iNormal.y, BlockToUpdateZ + iNormal.z);
				// @todo: Not sure here
				const auto Neighbor = BlockToUpdateChunk->GetBlock(Pos);
				const auto NeighborLight = Neighbor.GetLight();

				if (NeighborLight <= MyLightLevel - 2 && Neighbor.IsTransparent())
				{
					ChunkSection* neighborChunk = BlockToUpdateChunk;
					int neighborLocalX = Pos.x;
					int neighborLocalZ = Pos.z;
					if (CheckPositionInBounds(*neighborChunk, neighborLocalX, Pos.y, neighborLocalZ))
					{
						neighborChunk->SetLight({neighborLocalX, Pos.y, neighborLocalZ}, MyLightLevel - 1);
						BlocksToCheck.push(ivec3(BlockToUpdate.x + iNormal.x, BlockToUpdate.y + iNormal.y, BlockToUpdate.z + iNormal.z));
						ChunksToRetesselate.insert(neighborChunk);
					}
				}
			}
		}
	}

	void NChunkManager::RemoveNextLightLevel(ChunkSection* OriginalChunk, const ivec2& chunkCoordinates, std::unordered_set<ChunkSection*>& chunksToRetesselate, std::queue<ivec3>& blocksToCheck, std::queue<ivec3>& lightSources, bool bIgnoreThisSolidBlock)
	{
		ivec3 blockToUpdate = blocksToCheck.front();
		blocksToCheck.pop();

		if (!OriginalChunk)
		{
			LogWarning("Encountered weird null chunk while updating block lighting.");
			return;
		}

		int blockToUpdateX = blockToUpdate.x;
		int blockToUpdateY = blockToUpdate.y;
		int blockToUpdateZ = blockToUpdate.z;
		ChunkSection* blockToUpdateChunk = OriginalChunk;
		if (blockToUpdateX >= CChunkX || blockToUpdateX < 0 || blockToUpdateZ >= CChunkZ || blockToUpdateZ < 0)
		{
			if (!CheckPositionInBounds(*blockToUpdateChunk, blockToUpdateX, blockToUpdateY, blockToUpdateZ))
			{
				LogWarning("Position totally out of bounds...");
				return;
			}
			chunksToRetesselate.insert(blockToUpdateChunk);
		}

		if( !bIgnoreThisSolidBlock && !blockToUpdateChunk->GetBlock(blockToUpdate).IsTransparent() )
		{
			return;
		}

		int myOldLightLevel = blockToUpdateChunk->GetLight(blockToUpdate);
		blockToUpdateChunk->SetLight(blockToUpdate, 0);
		for (int i = 0; i < FINormals3::CardinalDirections.size(); i++)
		{
			const ivec3& iNormal = FINormals3::CardinalDirections[i];
			const ivec3 pos = ivec3(blockToUpdateX + iNormal.x, blockToUpdateY + iNormal.y, blockToUpdateZ + iNormal.z);
			const auto Neighbor = blockToUpdateChunk->GetBlock(pos);
			const int neighborLight = Neighbor.GetLight();
			if (neighborLight != 0 && neighborLight < myOldLightLevel && Neighbor.IsTransparent())
			{
				ChunkSection* neighborChunk = blockToUpdateChunk;
				int neighborLocalX = pos.x;
				int neighborLocalZ = pos.z;
				if (CheckPositionInBounds(*neighborChunk, neighborLocalX, pos.y, neighborLocalZ))
				{
					blocksToCheck.push(ivec3(blockToUpdate.x + iNormal.x, blockToUpdate.y + iNormal.y, blockToUpdate.z + iNormal.z));
					chunksToRetesselate.insert(neighborChunk);
				}
			}
			else if (neighborLight > myOldLightLevel)
			{
				ChunkSection* neighborChunk = blockToUpdateChunk;
				int neighborLocalX = pos.x;
				int neighborLocalZ = pos.z;
				if (CheckPositionInBounds(*neighborChunk, neighborLocalX, pos.y, neighborLocalZ))
				{
					lightSources.push(ivec3(blockToUpdate.x + iNormal.x, blockToUpdate.y + iNormal.y, blockToUpdate.z + iNormal.z));
					chunksToRetesselate.insert(neighborChunk);
				}
			}
		}
	}

	// TODO: Think about removing this duplication if it doesn't effect performance
	void NChunkManager::CalculateNextSkyLevel(ChunkSection* OriginalChunk, const ivec2& chunkCoordinates, std::unordered_set<ChunkSection*>& chunksToRetesselate, std::queue<ivec3>& blocksToCheck)
	{
		ivec3 blockToUpdate = blocksToCheck.front();
		blocksToCheck.pop();

		if (!OriginalChunk)
		{
			LogWarning("Encountered weird null chunk while updating block lighting.");
			return;
		}

		int blockToUpdateX = blockToUpdate.x;
		int blockToUpdateY = blockToUpdate.y;
		int blockToUpdateZ = blockToUpdate.z;
		ChunkSection* blockToUpdateChunk = OriginalChunk;
		if (blockToUpdateX >= CChunkX || blockToUpdateX < 0 || blockToUpdateZ >= CChunkZ || blockToUpdateZ < 0)
		{
			if (!CheckPositionInBounds(*blockToUpdateChunk, blockToUpdateX, blockToUpdateY, blockToUpdateZ))
			{
				return;
			}
			chunksToRetesselate.insert(blockToUpdateChunk);
		}

		if( !blockToUpdateChunk->GetBlock(blockToUpdate).IsTransparent() )
		{
			return;
		}

		const auto MyLightLevel = blockToUpdateChunk->GetBlock(blockToUpdate).GetLight();
		if (MyLightLevel > 0)
		{
			for (int i = 0; i < FINormals3::CardinalDirections.size(); i++)
			{
				const ivec3& iNormal = FINormals3::CardinalDirections[i];
				const ivec3 pos = ivec3(blockToUpdateX + iNormal.x, blockToUpdateY + iNormal.y, blockToUpdateZ + iNormal.z);
				const auto neighbor = blockToUpdateChunk->GetBlock(pos);
				int neighborLight = neighbor.GetSkyLight();
				if (neighborLight <= MyLightLevel - 2 && neighbor.IsTransparent())
				{
					ChunkSection* neighborChunk = blockToUpdateChunk;
					int neighborLocalX = pos.x;
					int neighborLocalZ = pos.z;
					if (CheckPositionInBounds(*neighborChunk, neighborLocalX, pos.y, neighborLocalZ))
					{
						neighborChunk->SetSkyLight({neighborLocalX, pos.y, neighborLocalZ}, MyLightLevel - 1);
						blocksToCheck.push(ivec3(blockToUpdate.x + iNormal.x, blockToUpdate.y + iNormal.y, blockToUpdate.z + iNormal.z));
						//g_logger_assert(iNormal.y != 1, "Sky sources should never propagate up once we get inside of here.");
						chunksToRetesselate.insert(neighborChunk);
					}
				}
			}
		}
	}

	void NChunkManager::RemoveNextSkyLevel(ChunkSection* OriginalChunk, const ivec2& ChunkCoordinates, std::unordered_set<ChunkSection*>& ChunksToRetesselate, std::queue<ivec3>& BlocksToCheck, std::queue<ivec3>& LightSources, const bool bIgnoreThisSolidBlock)
	{
		ivec3 blockToUpdate = BlocksToCheck.front();
		BlocksToCheck.pop();

		if (!OriginalChunk)
		{
			LogWarning("Encountered weird null chunk while updating block lighting.");
			return;
		}

		int blockToUpdateX = blockToUpdate.x;
		int blockToUpdateY = blockToUpdate.y;
		int blockToUpdateZ = blockToUpdate.z;
		ChunkSection* blockToUpdateChunk = OriginalChunk;
		if (blockToUpdateX >= CChunkX || blockToUpdateX < 0 || blockToUpdateZ >= CChunkZ || blockToUpdateZ < 0)
		{
			if (!CheckPositionInBounds(*blockToUpdateChunk, blockToUpdateX, blockToUpdateY, blockToUpdateZ))
			{
				return;
			}
			ChunksToRetesselate.insert(blockToUpdateChunk);
		}

		if (!bIgnoreThisSolidBlock && !blockToUpdateChunk->GetBlock(blockToUpdate).IsTransparent())
		{
			return;
		}

		int myOldLightLevel = blockToUpdateChunk->GetSkyLight(blockToUpdate);
		blockToUpdateChunk->SetSkyLight(blockToUpdate, 0);
		for (int i = 0; i < FINormals3::CardinalDirections.size(); i++)
		{
			const ivec3& iNormal = FINormals3::CardinalDirections[i];
			const ivec3 pos = ivec3(blockToUpdateX + iNormal.x, blockToUpdateY + iNormal.y, blockToUpdateZ + iNormal.z);
			const auto neighbor = blockToUpdateChunk->GetBlock(pos);
			int neighborLight = neighbor.GetSkyLight();
			bool neighborLightEffectedByMe = (neighborLight < myOldLightLevel) || (myOldLightLevel == 31 && iNormal.y == -1);
			if (neighborLight != 0 && neighborLightEffectedByMe && neighbor.IsTransparent())
			{
				ChunkSection* neighborChunk = blockToUpdateChunk;
				int neighborLocalX = pos.x;
				int neighborLocalZ = pos.z;
				if (CheckPositionInBounds(*neighborChunk, neighborLocalX, pos.y, neighborLocalZ))
				{
					BlocksToCheck.push(ivec3(blockToUpdate.x + iNormal.x, blockToUpdate.y + iNormal.y, blockToUpdate.z + iNormal.z));
				}
				ChunksToRetesselate.insert(neighborChunk);
			}
			else if (neighborLight > myOldLightLevel)
			{
				ChunkSection* neighborChunk = blockToUpdateChunk;
				int neighborLocalX = pos.x;
				int neighborLocalZ = pos.z;
				if (CheckPositionInBounds(*neighborChunk, neighborLocalX, pos.y, neighborLocalZ))
				{
					LightSources.push(ivec3(blockToUpdate.x + iNormal.x, blockToUpdate.y + iNormal.y, blockToUpdate.z + iNormal.z));
				}
				ChunksToRetesselate.insert(neighborChunk);
			}
		}
	}

	bool NChunkManager::CheckPositionInBounds(const ChunkSection& Chunk, int32& x, int32 y, int32& z) const
	{
		if (y < 0 || y >= CChunkY)
		{
			return false;
		}

		// Do a while loop, because the block could theoretically be like -32 which would be two chunks out
		while (x < 0)
		{
			const auto CurrentChunk = Chunk.TryGetNeighbor(NeighborType::Back);
			x = CChunkX + x;
			if (CurrentChunk == nullptr)
			{
				return false;
			}
		}
		while (z < 0)
		{
			const auto CurrentChunk = Chunk.TryGetNeighbor(NeighborType::Left);
			z = CChunkZ + z;
			if (CurrentChunk == nullptr)
			{
				return false;
			}
		}
		while (x >= CChunkX)
		{
			const auto CurrentChunk = Chunk.TryGetNeighbor(NeighborType::Front);
			x = x - CChunkX;
			if (CurrentChunk == nullptr)
			{
				return false;
			}
		}
		while (z >= CChunkZ)
		{
			const auto CurrentChunk = Chunk.TryGetNeighbor(NeighborType::Right);
			z = z - CChunkZ;
			if (CurrentChunk == nullptr)
			{
				return false;
			}
		}

		return true;
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