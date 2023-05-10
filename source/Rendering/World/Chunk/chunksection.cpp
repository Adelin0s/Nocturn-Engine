#include "rendering/world/chunk/chunksection.h"
#include "rendering/world/block/block.h"

#include "core/math/math.hpp"
#include "core/math/noise.h"

namespace Nocturn
{
	ChunkSection::ChunkSection(const ivec2& Location) :
		m_chunk(Constants::CChunkMaxSize),
		m_location(Location)
	{
	}

	NBlock ChunkSection::operator[](const ivec3& position) const noexcept
	{
		return m_chunk[ GetSizeFromIndex(position) ];
	}

	void ChunkSection::SetBlock(const EBlockId blockId, const int32 worldX, const int32 worldY, const int32 worldZ) noexcept
	{
		// Normalize to chunk coords
		const auto& chunkPosition = Math::ToBlockCoords(worldX, worldY, worldZ);
		SetBlock(blockId, chunkPosition);
	}

	void ChunkSection::SetBlock(const EBlockId blockId, const ivec3& worldPosition) noexcept
	{
		// Normalize to chunk coords
		const auto& position = Math::ToBlockCoords(worldPosition);
		const auto	block	 = m_chunk[ GetSizeFromIndex(position) ];

		if( EBlockId::Air == block && EBlockId::Air != blockId )
			m_layers[ position.y ].Increase();

		if( EBlockId::Air != block && EBlockId::Air == blockId )
			m_layers[ position.y ].Decrease();

		m_chunk[ GetSizeFromIndex(position) ] = blockId;
	}

	void ChunkSection::SetNeighbor(const NeighborType type, ChunkSection& chunk) noexcept
	{
		if( NeighborType::Left == type )
		{
			m_neighbor.left = &chunk;
		}
		else if( NeighborType::Right == type )
		{
			m_neighbor.right = &chunk;
		}
		else if( NeighborType::Front == type )
		{
			m_neighbor.top = &chunk;
		}
		else if( NeighborType::Back == type )
		{
			m_neighbor.bottom = &chunk;
		}
	}

	void ChunkSection::SetRenderableChunk() noexcept
	{
		m_renderableChunk = true;
	}

	ChunkSection* ChunkSection::TryGetNeighbor(const NeighborType type) const noexcept
	{
		if( type == NeighborType::Left && m_neighbor.left )
			return m_neighbor.left;

		if( type == NeighborType::Right && m_neighbor.right )
			return m_neighbor.right;

		if( type == NeighborType::Front && m_neighbor.top )
			return m_neighbor.top;

		if( type == NeighborType::Back && m_neighbor.bottom )
			return m_neighbor.bottom;

		return nullptr;
	}

	ivec2 ChunkSection::GetLocation() const
	{
		return m_location;
	}

	const std::vector< NBlock >& ChunkSection::GetChunk() const
	{
		return m_chunk;
	}

	ChunkLayer ChunkSection::GetLayer(const int y) const
	{
		return m_layers[ y ];
	}

	NBlock ChunkSection::GetBlock(const int32_t x, const int32_t y, const int32_t z) const noexcept
	{
		if( OutOfBound(x, y, z) )
			return EBlockId::Air;

		const auto SizeFromIndex = GetSizeFromIndex(x, y, z);
		if (SizeFromIndex > Constants::CChunkMaxSize)
		{
			LogWarning("Invalid index to get block from vector chunk!");
			return EBlockId::Air;
		}

		return m_chunk[ SizeFromIndex ];
	}

	NBlock ChunkSection::GetBlock(const ivec3& coords) const noexcept
	{
		if( OutOfBound(coords.x, coords.y, coords.z) )
			return EBlockId::Air;

		const auto SizeFromIndex = GetSizeFromIndex(coords);
		if (SizeFromIndex > Constants::CChunkMaxSize)
		{
			LogWarning("Invalid index to get block from vector chunk!");
			return EBlockId::Air;
		}
		
		return m_chunk[ SizeFromIndex ];
	}

	NBlock ChunkSection::GetAdjacentBlock(const ivec3& coords) const noexcept
	{
		const auto px = coords.x;
		const auto py = coords.y;
		const auto pz = coords.z;

		if( px == -1 )
		{
			const auto& neighbor = TryGetNeighbor(NeighborType::Back);

			assert(neighbor != nullptr);

			return neighbor->GetBlock(Constants::CChunkX - 1, py, pz);
		}
		if( px == Constants::CChunkX )
		{
			const auto& neighbor = TryGetNeighbor(NeighborType::Front);

			assert(neighbor != nullptr);

			return neighbor->GetBlock(0, py, pz);
		}
		if( pz == -1 )
		{
			const auto& neighbor = TryGetNeighbor(NeighborType::Left);

			assert(neighbor != nullptr);

			return neighbor->GetBlock(px, py, Constants::CChunkZ - 1);
		}
		if( pz == Constants::CChunkZ )
		{
			const auto& neighbor = TryGetNeighbor(NeighborType::Right);

			assert(neighbor != nullptr);

			return neighbor->GetBlock(px, py, 0);
		}

		return GetBlock(px, py, pz);
	}

	constexpr size_t ChunkSection::GetSizeOfBlock() noexcept
	{
		return sizeof(NBlock);
	}

	/// <summary>
	/// Return size from (x, y, z) to chunk position (uint32)
	/// </summary>
	/// <param name="x">column</param>
	/// <param name="y">height</param>
	/// <param name="z">row</param>
	/// <returns>uint32 size</returns>
	uint32 ChunkSection::GetSizeFromIndex(const uint32 x, const uint32 y, const uint32 z) noexcept
	{
		return z * 16 + y * 256 + x;
	}

	/// <summary>
	/// Return a size from (ivec3) to chunk position
	/// </summary>
	/// <param name="vec">vec3 stands for chunk position</param>
	/// <returns>uint32 stands for size of current chunk</returns>
	uint32 ChunkSection::GetSizeFromIndex(const ivec3& vec) noexcept
	{
		return vec.z * 16 + vec.y * 256 + vec.x;
	}

	ivec3 ChunkSection::GetIndexFromSize(const uint32 size) noexcept
	{
		const auto pz = size % Constants::CChunkY;
		return { pz % Constants::CChunkZ, pz / Constants::CChunkX, pz };
	}

	bool ChunkSection::HasMesh() const noexcept
	{
		return m_mesh.HasMesh();
	}

	bool ChunkSection::HasLoaded() const noexcept
	{
		return m_mesh.HasLoaded();
	}

	bool ChunkSection::ShouldToRender() const noexcept
	{
		return HasMesh() && m_renderableChunk;
	}

	bool ChunkSection::IsRenderable() const noexcept
	{
		return m_renderableChunk;
	}

	const RenderInfo& ChunkSection::GetRenderInfo() const
	{
		return m_mesh.GetModel().GetRenderInfo();
	}

	void ChunkSection::CreateChunk()
	{
		m_mesh.MakeMesh(*this);
	}

	void ChunkSection::LoadBufferData()
	{
		m_mesh.LoadBufferData();
	}

	void ChunkSection::DeleteMesh() noexcept
	{
		m_mesh.DeleteMesh();
	}

	bool ChunkSection::OutOfBound(const int32_t x, const int32_t y, const int32_t z) noexcept
	{
		if( x < 0 || x >= Constants::CChunkX || y < 0 || y >= Constants::CChunkY || z < 0 || z >= Constants::CChunkZ )
			return true;
		return false;
	}
} // namespace Nocturn