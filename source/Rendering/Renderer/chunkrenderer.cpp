#include "rendering/renderer/chunkrenderer.h"

namespace Nocturn::Render
{
	RStatus ChunkRenderer::Init( )
	{
		Shader = std::make_unique< NShader >( "block.vs", "block.fs" );
		Shader->Init( );
		Texture = std::make_unique< NTextureAtlas >( "block/default_pack.png" );

		return RSucces;
	}

	void ChunkRenderer::Add( const RenderInfo &renderInfo )
	{
		ChunksRenderInfo.emplace_back( renderInfo );
	}

	NODISCARD size_t ChunkRenderer::Size( ) const noexcept
	{
		return ChunksRenderInfo.size( );
	}

	void ChunkRenderer::Render( const NCamera &Camera )
	{
		if( ChunksRenderInfo.empty( ) )
			return;

		Texture->Bind();
		Shader->Bind( );
		Shader->SetProjectionMatrix( Camera );
		Shader->SetViewMatrix( Camera );

		for( const auto &chunk : ChunksRenderInfo )
		{
			GL::BindVao( chunk.vao );
			GL::DrawElements( chunk.indicesCount );
		}
		GL::BindVao( 0 );
		Shader->Unbind( );
		ChunksRenderInfo.clear( );
	}
} // namespace Nocturn::rendering