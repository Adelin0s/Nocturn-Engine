#include "rendering/renderer/chunkrenderer.h"

namespace Nocturn::rendering
{
	void ChunkRendering::init( )
	{
		m_shader = std::make_unique< Shader >( Config::CChunkVertexShader, Config::CChunkFragmentShader );
		m_shader->init( );
	}

	void ChunkRendering::add( const RenderInfo &renderInfo )
	{
		m_chunks.emplace_back( renderInfo );
	}

	NODISCARD size_t ChunkRendering::size( ) const noexcept
	{
		return m_chunks.size( );
	}

	void ChunkRendering::render( const Camera &camera )
	{
		if( m_chunks.empty( ) )
			return;

		m_shader->bind( );
		m_shader->setProjectionMatrix( camera );
		m_shader->setViewMatrix( camera );

		for( const auto &chunk : m_chunks )
		{
			GL::bindVAO( chunk.vao );
			GL::drawElements( chunk.indicesCount );
		}

		m_chunks.clear( );
	}
} // namespace Nocturn::rendering