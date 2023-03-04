/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 26-10-2021 14:31:10                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 18-11-2021 17:24:11                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef GL_FUNCTIONS
#define GL_FUNCTIONS

#include <cstdint>
#include <glad/glad.h>

namespace Nocturn::GL
{
	inline bool bDrawMode = false;

	void DrawElements( int32_t indicesCount ) noexcept;
	void DrawArraysInstanced( int32_t instanceCount = 1 ) noexcept;
	void BindVao( uint32_t vao ) noexcept;
} // namespace Nocturn::GL

#endif
