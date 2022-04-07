/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 26-10-2021 14:31:10                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 18-11-2021 17:24:11                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef GL_FUNCTIONS
#define GL_FUNCTIONS

#include <glad/glad.h>
#include <cstdint>

namespace Nocturn::GL
{
	void drawElements(const uint32_t indicesCount) noexcept;
	void drawArraysInstanced(const uint32_t instance_count = 1) noexcept;
	void bindVAO(const uint32_t vao) noexcept;
}

#endif
