#include "core/GL/GLFunctions.h"

namespace Nocturn::GL
{
	void drawElements( const uint32_t indicesCount ) noexcept
	{
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