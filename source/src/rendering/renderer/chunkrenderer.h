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

namespace Nocturn::rendering
{
	class ChunkRendering
	{
	public:
		ChunkRendering( ) noexcept = default;

		// cant copy
		ChunkRendering( const ChunkRendering & ) = delete;
		ChunkRendering &operator=( const ChunkRendering & ) = delete;

		// cant move
		ChunkRendering( ChunkRendering && ) = delete;
		ChunkRendering &operator=( ChunkRendering && ) = delete;

		void Init( );
		void Add( const RenderInfo &renderInfo );
		void Render( const Camera &camera );

		NODISCARD size_t Size( ) const noexcept;

		~ChunkRendering( ) noexcept = default;

	private:
		std::vector< RenderInfo >  m_chunks;
		std::unique_ptr< Shader >  m_shader;
	};
} // namespace Nocturn::rendering
#endif