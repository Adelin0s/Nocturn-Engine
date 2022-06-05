/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 27-10-2021 19:51:56                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 10-11-2021 21:14:17                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef BLOCK_DATA_HOLDER_HPP
#define BLOCK_DATA_HOLDER_HPP

#include <glm/glm.hpp>

#include "rendering/world/block/block.h"

namespace Nocturn::rendering
{
	struct BlockDataHolder
	{
		BlockId m_id;

		glm::vec2 m_textureTop;
		glm::vec2 m_textureSide;
		glm::vec2 m_textureBottom;
	};
} // namespace Nocturn::rendering

#endif