#include "rendering/world/chunk/chunkmesh.h"

#include "rendering/world/block/block.h"

#include "core/components/constants.hpp"
#include "rendering/world/block/blockdatabase.h"
#include "rendering/world/chunk/chunksection.h"

namespace Nocturn
{
	inline void AdjacentBlock::update(const uint32_t x, const uint32_t y, const uint32_t z)
	{
		top	   = { x, y + 1, z };
		bottom = { x, y - 1, z };
		left   = { x - 1, y, z };
		right  = { x + 1, y, z };
		front  = { x, y, z + 1 };
		back   = { x, y, z - 1 };
	}

	void ChunkMesh::Initialize(const NChunkSection* ChunkIn)
	{
		if( ChunkIn == nullptr )
		{
			LogError("Invalid nullptr ChunkIn parameter!");
		}

		Chunk = ChunkIn;
	}

	NODISCARD uint32 ChunkMesh::GetIndicesSize() const noexcept
	{
		return static_cast< uint32 >(Mesh.indices.size());
	}

	void ChunkMesh::MakeMesh(const NChunkSection* ChunkIn)
	{
		// We don't need to generate where our chunk's neighbors have all blocks solid.
		// Can continue because the current layer is basically hidden in real scenario.
		if (Chunk == nullptr)
		{
			LogError("Invalid nullptr Chunk parameter!");
			return;
		}
		Chunk = ChunkIn;

		auto &ChunkBlocks = Chunk->GetBlocks();
		for( int32 LayerY = 0; LayerY < CChunkY; LayerY++ )
		{
			if( ShouldPassLayer(LayerY) )
			{
				continue;
			}

			GenerateMeshLayer(LayerY);
		}
			
		bHasMesh = true; // flag to know if the buffer data can be loaded
	}

	void ChunkMesh::ReloadMesh(const NChunkSection* ChunkIn)
	{
		MakeMesh(ChunkIn);
		bShouldToReloadMesh = true;
	}

	void ChunkMesh::LoadBufferData()
	{
		if( bHasMesh && !bHasLoaded )
		{
			std::cout << "Loading buffer data!\n";
			m_model.AddData(Mesh);
			bHasLoaded = true;
		}

		if( bShouldToReloadMesh )
		{
			std::cout << "Reloading data!\n";
			m_model.ReloadData(Mesh);

			bShouldToReloadMesh = false;
		}
	}

	void ChunkMesh::DeleteMesh() noexcept
	{
		if( bHasMesh )
		{
			m_index		= 0;
			bHasLoaded = false;
			bHasMesh	= false;

			Mesh.Clear();
			//m_model.DeleteData();
		}
	}

	void ChunkMesh::GenerateMeshLayer(const uint32 LayerY)
	{
		AdjacentBlock directions;

		for( int32 x = 0; x < CChunkX; x++ )
		{
			for( int32 z = 0; z < CChunkZ; z++ )
			{
				const auto BlockData = Chunk->GetBlocks().at(NChunkSection::GetSizeFromIndex(x, LayerY, z)).GetData();

				const Block_t position(x, LayerY, z);
				directions.update(x, LayerY, z);

				AddBlockDataLight({x, LayerY, z});

				/* Up/Down */
				MakeFace(topFace, BlockData.m_textureTop, position, directions.top);
				MakeFace(bottomFace, BlockData.m_textureBottom, position, directions.bottom);

				/* Left/Right */
				MakeFace(leftFace, BlockData.m_textureSide, position, directions.left);
				MakeFace(rightFace, BlockData.m_textureSide, position, directions.right);

				/* Back/Front */
				MakeFace(backFace, BlockData.m_textureSide, position, directions.back);
				MakeFace(frontFace, BlockData.m_textureSide, position, directions.front);
			}
		}
	}

	void ChunkMesh::MakeFace(const Vertices_t& blockFace, const glm::vec2& textureCoords, const Block_t& BlockPosition, const ivec3& adjBlock)
	{
		if( ShouldMakeFace(BlockPosition, adjBlock) )
		{
			const auto& Coords = NTextureAtlas::GetTexture(textureCoords);
			AddFace(blockFace, Coords, Chunk->GetLocation(), BlockPosition);
		}
	}

	void ChunkMesh::AddBlockDataLight(const vec3& BlockCoords)
	{
		
	}


	bool ChunkMesh::ShouldMakeFace(const Block_t& blockCoords, const ivec3& adjCoords) const noexcept
	{
		if( Chunk->GetBlock(blockCoords) == EBlockId::Air )
			return false;

		if( Chunk->GetAdjacentBlock(adjCoords) != EBlockId::Air )
		{
			return false;
		}

		return true;
	}

	bool ChunkMesh::ShouldPassLayer(const uint32 LayerY) const noexcept
	{
		if( LayerY + 1 < CChunkY && !Chunk->GetLayer(LayerY + 1).IsAllSolid() )
		{
			return false;
		}

		if( const auto neighbor = Chunk->TryGetNeighbor(NeighborType::Left); nullptr != neighbor )
		{
			if( !neighbor->GetLayer(LayerY).IsAllSolid() )
			{
				// std::cout << neighbor->GetLayer( y ).getNumberOfBlocks( ) << ' ';
				return false;
			}
		}

		if( const auto neighbor = Chunk->TryGetNeighbor(NeighborType::Right); nullptr != neighbor )
		{
			if( !neighbor->GetLayer(LayerY).IsAllSolid() )
			{
				// std::cout << neighbor->GetLayer( y ).getNumberOfBlocks( ) << ' ';
				return false;
			}
		}

		if( const auto neighbor = Chunk->TryGetNeighbor(NeighborType::Front); nullptr != neighbor )
		{
			if( !neighbor->GetLayer(LayerY).IsAllSolid() )
			{
				// std::cout << neighbor->GetLayer( y ).getNumberOfBlocks( ) << ' ';
				return false;
			}
		}

		if( const auto neighbor = Chunk->TryGetNeighbor(NeighborType::Back); nullptr != neighbor )
		{
			if( !neighbor->GetLayer(LayerY).IsAllSolid() )
			{
				// std::cout << neighbor->GetLayer( y ).getNumberOfBlocks( ) << ' ';
				return false;
			}
		}

		return true;
	}

	void ChunkMesh::AddFace(const Vertices_t& Face, const Textures_t& TexturesCoords, const ivec2& ChunkPosition, const Block_t& BlockPosition)
	{
		auto& indices  = Mesh.indices;
		auto& vertices = Mesh.vertices;
		auto& textures = Mesh.textures;

		indices.insert(indices.end(), { m_index, m_index + 1, m_index + 2, m_index + 2, m_index + 3, m_index });
		m_index += 4;

		/* we have 4 set of vertices with 3 coords x, y, z  */
		for( uint32_t i = 0, index = 0; i < 4; i++ )
		{
			vertices.push_back(Face[ index++ ] + ChunkPosition[ 0 ] * CChunkX + BlockPosition.x);
			vertices.push_back(Face[ index++ ] + BlockPosition.y);
			vertices.push_back(Face[ index++ ] + ChunkPosition[ 1 ] * CChunkZ + BlockPosition.z);
		}
		textures.insert(textures.end(), TexturesCoords.begin(), TexturesCoords.end());
	}
} // namespace Nocturn