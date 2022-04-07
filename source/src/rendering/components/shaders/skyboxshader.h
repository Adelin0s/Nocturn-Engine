#ifndef SKYBOX_SHADER
#define SKYBOX_SHADER

#include "application/config/config.hpp"

#include "core/math/glm.hpp"

#include "rendering/data/camera.h"
#include "rendering/components/shaders/shader.h"

namespace Nocturn
{
    class SkyboxShader : public Shader
    {
    public:
        SkyboxShader() noexcept;
        SkyboxShader(const SkyboxShader &) = delete;
        SkyboxShader(SkyboxShader &&) = delete;

        SkyboxShader operator=(const SkyboxShader &) = delete;
        SkyboxShader operator=(SkyboxShader &&) = delete;

        void setViewMatrix(const Camera &camera) const;
        void setProjectionMatrix(const Camera &camera) const;

        ~SkyboxShader() noexcept = default;
    };
}

#endif 