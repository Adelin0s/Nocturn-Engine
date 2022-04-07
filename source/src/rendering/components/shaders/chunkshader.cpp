#include "rendering/components/shaders/chunkshader.h"

namespace Nocturn
{
    ChunkShader::ChunkShader() noexcept
    :   Shader              (Config::chunkVertexShader, Config::chunkFragmentShader)
    { }

    void ChunkShader::setViewMatrix(const Camera &camera) const
    {
        set4Matrix("projection", camera.getProjectionMatrix());
    }

    void ChunkShader::setProjectionMatrix(const Camera &camera) const
    {
        set4Matrix("view", camera.getViewMatrix());
    }
}