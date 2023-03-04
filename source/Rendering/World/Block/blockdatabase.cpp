#include "rendering/world/block/blockdatabase.h"

namespace Nocturn::rendering
{
	BlockDatabase::BlockDatabase( ) noexcept
	{
		m_blocks[ static_cast< int >( BlockId::Air ) ]		 = std::make_unique< BlockData >( "air" );
		m_blocks[ static_cast< int >( BlockId::Grass ) ]	 = std::make_unique< BlockData >( "grass" );
		m_blocks[ static_cast< int >( BlockId::Dirt ) ]		 = std::make_unique< BlockData >( "dirt" );
		m_blocks[ static_cast< int >( BlockId::Stone ) ]	 = std::make_unique< BlockData >( "stone" );
		m_blocks[ static_cast< int >( BlockId::OakBark ) ]	 = std::make_unique< BlockData >( "oakbark" );
		m_blocks[ static_cast< int >( BlockId::OakLeaf ) ]	 = std::make_unique< BlockData >( "oakleaf" );
		m_blocks[ static_cast< int >( BlockId::Sand ) ]		 = std::make_unique< BlockData >( "sand" );
		m_blocks[ static_cast< int >( BlockId::Water ) ]	 = std::make_unique< BlockData >( "water" );
		m_blocks[ static_cast< int >( BlockId::Cactus ) ]	 = std::make_unique< BlockData >( "cactus" );
		m_blocks[ static_cast< int >( BlockId::Rose ) ]		 = std::make_unique< BlockData >( "rose" );
		m_blocks[ static_cast< int >( BlockId::TallGrass ) ] = std::make_unique< BlockData >( "tallgrass" );
		m_blocks[ static_cast< int >( BlockId::DeadShrub ) ] = std::make_unique< BlockData >( "deadshrub" );
	}

	BlockDatabase &BlockDatabase::getInstance( )
	{
		static BlockDatabase instance;
		return instance;
	}

	NODISCARD const BlockDataHolder &BlockDatabase::getData( const BlockId id ) const noexcept
	{
		return m_blocks[ static_cast< uint32_t >( id ) ]->getData( );
	}
} // namespace Nocturn::rendering