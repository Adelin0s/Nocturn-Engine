#ifndef SKYBOX_SHADER
#define SKYBOX_SHADER

#include "application/config/config.hpp"

#include "core/math/glm.hpp"

#include "rendering/components/entity/camera.h"
#include "rendering/components/shaders/shader.h"

namespace Nocturn
{
    class SkyboxShader : public NShader
    {
    public:
        SkyboxShader() noexcept;
        SkyboxShader(const SkyboxShader &) = delete;
        SkyboxShader(SkyboxShader &&) = delete;

        SkyboxShader operator=(const SkyboxShader &) = delete;
        SkyboxShader operator=(SkyboxShader &&) = delete;

        void SetViewMatrix(const NCamera &Camera) const override;
        void SetProjectionMatrix(const NCamera &Camera) const override;

        ~SkyboxShader() noexcept override = default;
    };
}

#endif 