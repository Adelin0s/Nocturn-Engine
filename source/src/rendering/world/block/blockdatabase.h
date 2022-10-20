/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 24-10-2021 14:58:32                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 17-12-2021 16:13:02                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef BLOCK_DATABASE_H
#define BLOCK_DATABASE_H

#include <array>
#include <memory>

#include "core/platform/platform.h"
#include "rendering/components/textures/textureatlas.h"
#include "rendering/world/block/block.h"
#include "rendering/world/block/blockdata.h"

namespace Nocturn::rendering
{
	/* HIERARCHY : BlockDatabase : m_blocks<BlockType> -> BlockType : m_blockData<BlockData> -> BlockData : m_blockDataHolder<BlockDataHolder> */

	/* Singleton is evil, yeah. but for now it's ok. for future i will update this method*/
	/* Singleton class */
	class BlockDatabase
	{
	public:
		BlockDatabase( const BlockDatabase &smth ) = delete;
		BlockDatabase( BlockDatabase &&smth )	   = delete;

		BlockDatabase &operator=( const BlockDatabase &smth ) = delete;
		BlockDatabase &operator=( BlockDatabase &&smth ) = delete;

		static BlockDatabase			 &getInstance( ); /* get instance  */
		NODISCARD const BlockDataHolder &getData( const BlockId id ) const noexcept;

	private:
		BlockDatabase( ) noexcept;
		~BlockDatabase( ) noexcept = default;

		std::array< std::unique_ptr< BlockData >, static_cast< unsigned >( BlockId::End ) > m_blocks;

	public:
		TextureAtlas textureAtlas;
	};
} // namespace Nocturn::rendering

#endif
