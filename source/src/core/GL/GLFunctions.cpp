#include "core/GL/GLFunctions.h"

#include <iostream>

#include "application/input/keyboard.h"

namespace Nocturn::GL
{
	void DrawElements( const int32_t indicesCount ) noexcept
	{
		if( Keyboard::keyWentDown( GLFW_KEY_P ) )
			bDrawMode = !bDrawMode;

		if( bDrawMode )
			glDrawElements( GL_LINES, indicesCount, GL_UNSIGNED_INT, nullptr );
		else
			glDrawElements( GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr );
	}

	void DrawArraysInstanced( const int32_t instanceCount ) noexcept
	{
		glDrawArraysInstanced( GL_TRIANGLES, 0, 36, instanceCount );
	}

	void BindVao( const uint32_t vao ) noexcept
	{
		glBindVertexArray( vao );
	}
} // namespace Nocturn::GL