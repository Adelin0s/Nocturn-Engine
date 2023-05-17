#ifndef SKYBOX_SHADER
#define SKYBOX_SHADER

#include "application/config/config.hpp"

#include "core/math/glm.hpp"

#include "rendering/components/shaders/shader.h"

namespace Nocturn
{
    class SkyboxShader : public NShader
    {
    public:
        SkyboxShader() noexcept;

        /** Cant move. */
        SkyboxShader(const SkyboxShader &) = delete;
        SkyboxShader(SkyboxShader &&) = delete;

        /** Cant copy. */
        SkyboxShader operator=(const SkyboxShader &) = delete;
        SkyboxShader operator=(SkyboxShader &&) = delete;

        /**
         * @brief Sets the view matrix uniform in the shader.
         * @param ViewMatrix The view matrix.
         */
        void SetViewMatrix(const mat4 &ViewMatrix) const override;

        /**
         * @brief Sets the projection matrix uniform in the shader.
         * @param ProjectionMatrix The projection matrix.
         */
        void SetProjectionMatrix(const mat4 &ProjectionMatrix) const override;

        ~SkyboxShader() noexcept override = default;
    };
}

#endif 