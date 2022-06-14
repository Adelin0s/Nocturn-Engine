#ifndef CHUNK_SHADER
#define CHUNK_SHADER

#include "application/config/config.hpp"

#include "core/math/glm.hpp"

#include "rendering/components/shaders/shader.h"
#include "rendering/data/camera.h"

namespace Nocturn
{
	class ChunkShader: public Shader
	{
	public:
		ChunkShader( ) noexcept;
		ChunkShader( const ChunkShader & ) = delete;
		ChunkShader( ChunkShader && )	   = delete;

		ChunkShader operator=( const ChunkShader & ) = delete;
		ChunkShader operator=( ChunkShader && ) = delete;

		void setViewMatrix( const Camera &camera ) const override;
		void setProjectionMatrix( const Camera &camera ) const override;
	};
} // namespace Nocturn

#endif