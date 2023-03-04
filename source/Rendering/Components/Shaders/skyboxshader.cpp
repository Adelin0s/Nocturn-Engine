#include "rendering/components/shaders/skyboxshader.h"

namespace Nocturn
{
	SkyboxShader::SkyboxShader( ) noexcept
		:
		NShader("skybox.vs" , "skybox.fs")
	{}

	void SkyboxShader::SetViewMatrix( const NCamera& Camera ) const
	{
		SetMatrix4( "projection", Camera.GetProjectionMatrix( ) );
	}

	void SkyboxShader::SetProjectionMatrix( const NCamera &Camera ) const
	{
		SetMatrix4( "view", glm::mat4( glm::mat3( Camera.GetViewMatrix( ) ) ) );
	}
} // namespace Nocturn