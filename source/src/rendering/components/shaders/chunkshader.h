#ifndef BLOCK_SHADER
#define BLOCK_SHADER

#include "application/config/config.hpp"

#include "core/math/glm.hpp"

#include "rendering/components/shaders/shader.h"
#include "rendering/data/camera.h"

namespace Nocturn
{
	class BlockShader final: public Shader
	{
	public:
		BlockShader( const char *const pathVertexShader, const char *const pathFragmentShader ) noexcept;

		// cant copy
		BlockShader operator=( const BlockShader & ) = delete;
		BlockShader( const BlockShader & )			 = delete;

		// cant move
		BlockShader( BlockShader && ) = delete;
		BlockShader operator=( BlockShader && ) = delete;

		void setViewMatrix( const Camera &camera ) const override;
		void setProjectionMatrix( const Camera &camera ) const override;

		~BlockShader( ) noexcept override = default;
	};
} // namespace Nocturn

#endif