#include "rendering/components/shaders/skyboxshader.h"

namespace Nocturn
{
	SkyboxShader::SkyboxShader( ) noexcept
		:
		Shader( Config::CSkyboxVertexShader, Config::CSkyboxFragmentShader )
	{}

	void SkyboxShader::setViewMatrix( const Camera &camera ) const
	{
		setMatrix4( "projection", camera.GetProjectionMatrix( ) );
	}

	void SkyboxShader::setProjectionMatrix( const Camera &camera ) const
	{
		setMatrix4( "view", glm::mat4( glm::mat3( camera.GetViewMatrix( ) ) ) );
	}
} // namespace Nocturn