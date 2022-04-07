/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 25-10-2021 20:35:41                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 08-12-2021 18:59:41                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include "core/GL/GLFunctions.h"

#include "rendering/components/shaders/chunkshader.h"
#include "rendering/world/block/blockdatabase.h"
#include "rendering/world/chunk/chunksection.h"

namespace Nocturn::rendering
{
	class ChunkRendering
	{
	public:
		ChunkRendering( ) noexcept				 = default;
		ChunkRendering( const ChunkRendering & ) = delete;
		ChunkRendering( ChunkRendering && )		 = delete;
		ChunkRendering &operator=( const ChunkRendering & ) = delete;
		ChunkRendering &operator=( ChunkRendering && ) = delete;

		void init( );
		void add( const RenderInfo &renderInfo );
		void render( const Camera &camera );

		~ChunkRendering( ) noexcept = default;

	private:
		std::vector< RenderInfo > m_chunks;
		ChunkShader				  m_shader;
	};
} // namespace Nocturn::rendering
#endif