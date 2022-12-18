// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin                                                                                      
//   @ Create Time: 25-10-2021 6:34 PM                                                                                                                                                
//   @ Contact: cucorianu.adelin@protonmail.com                                                                                                                          
//   @ Modified time: 23-08-2022 9:49 PM                                                                                                                                    
//   @ Description:                                                                                                                                                                                
// =====================================================================

#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include "core/GL/GLFunctions.h"
#include "core/math/frustum.h"

#include "rendering/components/shaders/shader.h"
#include "rendering/world/block/blockdatabase.h"
#include "rendering/world/chunk/chunksection.h"
#include "rendering/renderer/baserenderer.h"

namespace Nocturn::Render
{
	class ChunkRenderer : public BaseRenderer
	{
	public:
		ChunkRenderer( ) noexcept = default;

		// cant copy
		ChunkRenderer( const ChunkRenderer & ) = delete;
		ChunkRenderer &operator=( const ChunkRenderer & ) = delete;

		// cant move
		ChunkRenderer( ChunkRenderer && ) = delete;
		ChunkRenderer &operator=( ChunkRenderer && ) = delete;

		RStatus Init() override;
		RStatus Render(const Camera &camera) override;

		void Add( const RenderInfo &renderInfo );
		NODISCARD size_t Size( ) const noexcept;

		~ChunkRenderer( ) noexcept = default;

	private:
		std::vector< RenderInfo >  m_chunks;
		std::unique_ptr< Shader >  m_shader;
	};
} // namespace Nocturn::rendering
#endif