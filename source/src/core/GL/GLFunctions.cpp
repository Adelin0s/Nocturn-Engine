#include "core/GL/GLFunctions.h"

#include <iostream>

#include "application/input/keyboard.h"

namespace Nocturn::GL
{
	void drawElements( const uint32_t indicesCount ) noexcept
	{
		if( Keyboard::keyWentDown( GLFW_KEY_P ) )
			bDrawMode = !bDrawMode;

		if( bDrawMode )
			glDrawElements( GL_LINES, indicesCount, GL_UNSIGNED_INT, nullptr );
		else
			glDrawElements( GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr );
	}

	void drawArraysInstanced( const uint32_t instance_count ) noexcept
	{
		glDrawArraysInstanced( GL_TRIANGLES, 0, 36, instance_count );
	}

	void bindVAO( const uint32_t vao ) noexcept
	{
		glBindVertexArray( vao );
	}
} // namespace Nocturn::GL