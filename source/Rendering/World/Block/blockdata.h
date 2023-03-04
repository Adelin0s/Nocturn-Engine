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
#include "core/types/typedef.hpp"
#include "rendering/components/textures/texturecube.h"

namespace Nocturn::rendering
{
	enum class BlockId : uint8_t;

	struct BlockDataHolder
	{
		BlockId m_id;

		vec2 m_textureTop;
		vec2 m_textureSide;
		vec2 m_textureBottom;
	};

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
