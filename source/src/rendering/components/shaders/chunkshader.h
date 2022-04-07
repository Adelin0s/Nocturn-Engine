#ifndef CHUNK_SHADER
#define CHUNK_SHADER

#include "application/config/config.hpp"

#include "core/math/glm.hpp"

#include "rendering/data/camera.h"
#include "rendering/components/shaders/shader.h"

namespace Nocturn
{
	class ChunkShader : public Shader
	{
	public:
		ChunkShader() noexcept;
		ChunkShader(const ChunkShader&) = delete;
		ChunkShader(ChunkShader&&) = delete;

		ChunkShader operator=(const ChunkShader&) = delete;
		ChunkShader operator=(ChunkShader&&) = delete;

		void setViewMatrix(const Camera& camera) const;
		void setProjectionMatrix(const Camera& camera) const;
	};
}

#endif