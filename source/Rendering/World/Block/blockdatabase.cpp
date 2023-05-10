#include "rendering/world/block/blockdatabase.h"

namespace Nocturn
{
	BlockDatabase::BlockDatabase() noexcept
	{
		m_blocks[ static_cast< int >(EBlockId::Air) ]		= std::make_unique< BlockData >("air");
		m_blocks[ static_cast< int >(EBlockId::Grass) ]		= std::make_unique< BlockData >("grass");
		m_blocks[ static_cast< int >(EBlockId::Dirt) ]		= std::make_unique< BlockData >("dirt");
		m_blocks[ static_cast< int >(EBlockId::Stone) ]		= std::make_unique< BlockData >("stone");
		m_blocks[ static_cast< int >(EBlockId::OakBark) ]	= std::make_unique< BlockData >("oakbark");
		m_blocks[ static_cast< int >(EBlockId::OakLeaf) ]	= std::make_unique< BlockData >("oakleaf");
		m_blocks[ static_cast< int >(EBlockId::Sand) ]		= std::make_unique< BlockData >("sand");
		m_blocks[ static_cast< int >(EBlockId::Water) ]		= std::make_unique< BlockData >("water");
		m_blocks[ static_cast< int >(EBlockId::Cactus) ]	= std::make_unique< BlockData >("cactus");
		m_blocks[ static_cast< int >(EBlockId::Rose) ]		= std::make_unique< BlockData >("rose");
		m_blocks[ static_cast< int >(EBlockId::TallGrass) ] = std::make_unique< BlockData >("tallgrass");
		m_blocks[ static_cast< int >(EBlockId::DeadShrub) ] = std::make_unique< BlockData >("deadshrub");
	}

	BlockDatabase& BlockDatabase::GetInstance()
	{
		static BlockDatabase instance;
		return instance;
	}

	const BlockDataHolder& BlockDatabase::GetData(const uint8 BlockId) const noexcept
	{
		return m_blocks[ static_cast< uint32_t >(BlockId) ]->getData();
	}
} // namespace Nocturn