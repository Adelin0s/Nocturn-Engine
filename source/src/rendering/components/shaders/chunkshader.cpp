#include "rendering/components/shaders/chunkshader.h"

namespace Nocturn
{
	BlockShader::BlockShader( const char *const pathVertexShader, const char *const pathFragmentShader ) noexcept
		:
		Shader( pathVertexShader, pathFragmentShader )
	{}

	void BlockShader::setViewMatrix( const Camera &camera ) const
	{
		set4Matrix( "projection", camera.getProjectionMatrix( ) );
	}

	void BlockShader::setProjectionMatrix( const Camera &camera ) const
	{
		set4Matrix( "view", camera.getViewMatrix( ) );
	}
} // namespace Nocturn