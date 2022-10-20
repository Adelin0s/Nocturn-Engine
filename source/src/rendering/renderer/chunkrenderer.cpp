#include "rendering/renderer/chunkrenderer.h"

namespace Nocturn::rendering
{
	void ChunkRendering::Init( )
	{
		m_shader = std::make_unique< Shader >( Config::CChunkVertexShader, Config::CChunkFragmentShader );
		m_shader->init( );
	}

	void ChunkRendering::Add( const RenderInfo &renderInfo )
	{
		m_chunks.emplace_back( renderInfo );
	}

	NODISCARD size_t ChunkRendering::Size( ) const noexcept
	{
		return m_chunks.size( );
	}

	void ChunkRendering::Render( const Camera &camera )
	{
		if( m_chunks.empty( ) )
			return;

		m_shader->bind( );
		m_shader->setProjectionMatrix( camera );
		m_shader->setViewMatrix( camera );

		for( const auto &chunk : m_chunks )
		{
			GL::BindVao( chunk.vao );
			GL::DrawElements( chunk.indicesCount );
		}
		GL::BindVao( 0 );
		m_chunks.clear( );
	}
} // namespace Nocturn::rendering