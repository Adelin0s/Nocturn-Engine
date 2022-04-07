#include "rendering/renderer/chunkrenderer.h"

namespace Nocturn::rendering
{
	void ChunkRendering::init( )
	{
		m_shader.init( );
	}

	void ChunkRendering::add( const RenderInfo &renderInfo )
	{
		m_chunks.emplace_back( renderInfo );
	}

	void ChunkRendering::render( const Camera &camera )
	{
		if( m_chunks.empty( ) )
			return;

		BlockDatabase::getInstance( ).textureAtlas.bind( );
		BlockDatabase::getInstance( ).textureAtlas.load( );
		m_shader.activate( );
		m_shader.setProjectionMatrix( camera );
		m_shader.setViewMatrix( camera );

		for( const auto &chunk : m_chunks )
		{
			GL::bindVAO( chunk.vao );
			GL::drawElements( chunk.indicesCount );
		}

		m_chunks.clear( );
	}
} // namespace Nocturn::rendering