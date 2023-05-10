#include "rendering/components/shaders/skyboxshader.h"

namespace Nocturn
{
	SkyboxShader::SkyboxShader( ) noexcept
		:
		NShader("skybox.vs" , "skybox.fs")
	{}

	void SkyboxShader::SetViewMatrix(const mat4& ViewMatrix) const
	{
		SetMatrix4("view", mat4(mat3(ViewMatrix)));
	}

	void SkyboxShader::SetProjectionMatrix(const mat4& ProjectionMatrix) const
	{
		SetMatrix4("projection", ProjectionMatrix);
	}
} // namespace Nocturn