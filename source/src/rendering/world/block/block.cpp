#include "rendering/world/block/block.h"
#include "rendering/world/block/blockdatabase.h"

namespace Nocturn::rendering
{
	Block::Block( const BlockId_t id ) :
		m_id( id )
	{}

	Block::Block( const BlockId id ) :
		m_id( static_cast< BlockId_t >( id ) )
	{}

	void Block::operator=( BlockId id )
	{
		m_id = static_cast< BlockId_t >( id );
	}

	bool Block::operator==( const BlockId id ) const
	{
		return m_id == static_cast< BlockId_t >( id );
	}

	bool Block::operator==( const Block &block ) const
	{
		return m_id == block.m_id;
	}

	bool Block::operator!=( const Block &block ) const
	{
		return m_id != block.m_id;
	}

	NODISCARD const BlockDataHolder &Block::getData( ) const
	{
		return BlockDatabase::getInstance( ).getData( static_cast< BlockId >( m_id ) );
	}
} // namespace Nocturn::rendering