/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 11-10-2021 14:01:06                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 17-12-2021 16:45:34                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef BLOCK_DATA
#define BLOCK_DATA

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "core/platform/platform.h"
#include "rendering/components/textures/texturecube.h"
#include "rendering/world/block/blockdataholder.hpp"

namespace Nocturn::rendering
{
	class BlockData
	{
	public:
		BlockData( ) noexcept = default;
		BlockData( const std::string &blockName );
		BlockData( const BlockData &smth ) = delete;
		BlockData( BlockData &&smth )	   = delete;

		BlockData &operator=( const BlockData &smth ) = delete;
		BlockData &operator=( BlockData &&smth ) = delete;

		NODISCARD const BlockDataHolder &getData( ) const noexcept;

		~BlockData( ) noexcept = default;

	private:
		BlockDataHolder m_blockDataHolder;
	};
} // namespace Nocturn::rendering
#endif
