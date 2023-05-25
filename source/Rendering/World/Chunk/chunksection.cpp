#include "rendering/world/chunk/chunksection.h"
#include "rendering/world/block/block.h"

#include "core/math/math.hpp"
#include "core/math/noise.h"

namespace Nocturn
{
	NChunkSection::NChunkSection(const ivec2& Location)
	:
		m_chunk(CChunkMaxSize),
		m_location(Location)
	{
		m_mesh.Initialize(this);
	}

	NBlock NChunkSection::operator[](const ivec3& Position) const noexcept
	{
		return m_chunk[ GetSizeFromIndex(Position) ];
	}

	void NChunkSection::SetBlock(const EBlockId blockId, const int32 worldX, const int32 worldY, const int32 worldZ) noexcept
	{
		// Normalize to chunk coords
		const auto& chunkPosition = Math::ToBlockCoords(worldX, worldY, worldZ);
		SetBlock(blockId, chunkPosition);
	}

	void NChunkSection::SetLight(const vec3& BlockPosition, const uint8 LightLevel) noexcept
	{
		m_chunk[GetSizeFromIndex(BlockPosition)].SetLight(LightLevel);
	}

	void NChunkSection::SetSkyLight(const vec3& BlockPosition, const uint8 LightLevel) noexcept
	{
		m_chunk[GetSizeFromIndex(BlockPosition)].SetSkyLight(LightLevel);
	}

	void NChunkSection::SetBlock(const EBlockId blockId, const ivec3& worldPosition) noexcept
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

	void NChunkSection::SetNeighbor(const NeighborType type, NChunkSection& chunk) noexcept
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

	void NChunkSection::SetRenderableChunk() noexcept
	{
		bIsRenderableChunk = true;
	}

	NChunkSection* NChunkSection::TryGetNeighbor(const NeighborType type) const noexcept
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

	ivec2 NChunkSection::GetLocation() const noexcept
	{
		return m_location;
	}

	const std::vector< NBlock >& NChunkSection::GetBlocks() const
	{
		return m_chunk;
	}

	NBlock NChunkSection::GetBlock(const int32_t x, const int32_t y, const int32_t z) const noexcept
	{
		if( OutOfBound(x, y, z) )
			return EBlockId::Air;

		const auto SizeFromIndex = GetSizeFromIndex(x, y, z);
		if (SizeFromIndex > CChunkMaxSize)
		{
			LogWarning("Invalid index to get block from vector chunk!");
			return EBlockId::Air;
		}

		return m_chunk[ SizeFromIndex ];
	}

	NBlock NChunkSection::GetBlock(const ivec3& coords) const noexcept
	{
		if( OutOfBound(coords.x, coords.y, coords.z) )
			return EBlockId::Air;

		const auto SizeFromIndex = GetSizeFromIndex(coords);
		if (SizeFromIndex > CChunkMaxSize)
		{
			LogWarning("The index to retrieve block from the chunk vector is invalid!");
			return EBlockId::Air;
		}
		
		return m_chunk[ SizeFromIndex ];
	}

	uint8 NChunkSection::GetLight(const vec3& BlockPosition) const noexcept
	{
		const auto Size = GetSizeFromIndex(BlockPosition);
		if( Size > CChunkMaxSize )
		{
			LogWarning("The index to retrieve light from the chunk vector is invalid!")
			return 0;
		}

		return m_chunk[ Size ].GetLight();
	}

	uint8 NChunkSection::GetSkyLight(const vec3& BlockPosition) const noexcept
	{
		const auto Size = GetSizeFromIndex(BlockPosition);
		if( Size > CChunkMaxSize )
		{
			LogWarning("The index to retrieve light from the chunk vector is invalid!")
			return 0;
		}

		return m_chunk[ Size ].GetSkyLight();
	}

	NBlock NChunkSection::GetAdjacentBlock(const ivec3& coords) const noexcept
	{
		const auto px = coords.x;
		const auto py = coords.y;
		const auto pz = coords.z;

		if( px == -1 )
		{
			const auto& neighbor = TryGetNeighbor(NeighborType::Back);

			assert(neighbor != nullptr);

			return neighbor->GetBlock(CChunkX - 1, py, pz);
		}
		if( px == CChunkX )
		{
			const auto& neighbor = TryGetNeighbor(NeighborType::Front);

			assert(neighbor != nullptr);

			return neighbor->GetBlock(0, py, pz);
		}
		if( pz == -1 )
		{
			const auto& neighbor = TryGetNeighbor(NeighborType::Left);

			assert(neighbor != nullptr);

			return neighbor->GetBlock(px, py, CChunkZ - 1);
		}
		if( pz == CChunkZ )
		{
			const auto& neighbor = TryGetNeighbor(NeighborType::Right);

			assert(neighbor != nullptr);

			return neighbor->GetBlock(px, py, 0);
		}

		return GetBlock(px, py, pz);
	}

	constexpr size_t NChunkSection::GetSizeOfBlock() noexcept
	{
		return sizeof(NBlock);
	}

	// TODO: Review here, should to revers z and x
	uint32 NChunkSection::GetSizeFromIndex(const uint32 x, const uint32 y, const uint32 z) noexcept
	{
		return z * 16 + y * 256 + x;
	}

	// Same here
	uint32 NChunkSection::GetSizeFromIndex(const ivec3& vec) noexcept
	{
		return vec.z * 16 + vec.y * 256 + vec.x;
	}

	ivec3 NChunkSection::GetIndexFromSize(const uint32 size) noexcept
	{
		const auto pz = size % CChunkY;
		return { pz % CChunkZ, pz / CChunkX, pz };
	}

	bool NChunkSection::HasMesh() const noexcept
	{
		return m_mesh.HasMesh();
	}

	bool NChunkSection::HasLoaded() const noexcept
	{
		return m_mesh.HasLoaded();
	}

	bool NChunkSection::ShouldToRender() const noexcept
	{
		return HasMesh() && bIsRenderableChunk;
	}

	bool NChunkSection::IsRenderable() const noexcept
	{
		return bIsRenderableChunk;
	}

	const RenderInfo& NChunkSection::GetRenderInfo() const
	{
		return m_mesh.GetModel().GetRenderInfo();
	}

	void NChunkSection::CreateChunk()
	{
		m_mesh.MakeMesh(this);
	}

	void NChunkSection::ReloadChunk()
	{
		m_mesh.ReloadMesh(this);
	}

	void NChunkSection::LoadBufferData()
	{
		m_mesh.LoadBufferData();
	}

	void NChunkSection::DeleteMesh() noexcept
	{
		m_mesh.DeleteMesh();
	}

	bool NChunkSection::OutOfBound(const int32_t x, const int32_t y, const int32_t z) noexcept
	{
		if( x < 0 || x >= CChunkX || y < 0 || y >= CChunkY || z < 0 || z >= CChunkZ )
			return true;
		return false;
	}
} // namespace Nocturn