#include "rendering/components/shaders/skyboxshader.h"

namespace Nocturn
{
    SkyboxShader::SkyboxShader() noexcept
    :   Shader              (Config::skyboxVertexShader, Config::skyboxFragmentShader)
    { }

    void SkyboxShader::setViewMatrix(const Camera &camera) const
    {
        set4Matrix("projection", camera.getProjectionMatrix());
    }

    void SkyboxShader::setProjectionMatrix(const Camera &camera) const
    {
        set4Matrix("view", glm::mat4(glm::mat3(camera.getViewMatrix())));
    }
}