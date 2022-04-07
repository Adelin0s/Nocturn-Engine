#include "rendering/world/block/blockdata.h"

namespace Nocturn::rendering
{
	BlockData::BlockData( const std::string &block_name )
	{
		const std::string path = Config::DIR_BLOCKSTATES + block_name + ".json";
		std::ifstream	  file( path );

		if( !file.is_open( ) )
		{
			throw std::runtime_error( "ERROR: Unable to open the block file " + block_name + "." );
		}

		nlohmann::json l_json = nlohmann::json::parse( file );

		if( l_json.contains( "id" ) )
		{
			m_blockDataHolder.m_id = l_json[ "id" ];
		}

		if( l_json.contains( "texture_top" ) )
		{
			uint32_t i = 0;
			for( const auto &item : l_json[ "texture_top" ] )
				m_blockDataHolder.m_textureTop[ i++ ] = item;
		}

		if( l_json.contains( "texture_side" ) )
		{
			uint32_t i = 0;
			for( const auto &item : l_json[ "texture_side" ] )
				m_blockDataHolder.m_textureSide[ i++ ] = item;
		}

		if( l_json.contains( "texture_bottom" ) )
		{
			uint32_t i = 0;
			for( const auto &item : l_json[ "texture_bottom" ] )
				m_blockDataHolder.m_textureBottom[ i++ ] = item;
		}
		if( l_json.contains( "texture_all" ) )
		{
			uint32_t i = 0;
			for( const auto &item : l_json[ "texture_all" ] )
			{
				m_blockDataHolder.m_textureTop[ i ]		 = item;
				m_blockDataHolder.m_textureSide[ i ]	 = item;
				m_blockDataHolder.m_textureBottom[ i++ ] = item;
			}
		}
	}

	NODISCARD const BlockDataHolder &BlockData::getData( ) const noexcept
	{
		return m_blockDataHolder;
	}
} // namespace Nocturn::rendering
