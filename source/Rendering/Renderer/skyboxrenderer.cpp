#include "rendering/renderer/skyboxrenderer.h"

namespace Nocturn::Render
{
	RStatus SkyboxRenderer::Init( )
	{
		VertexType::SkyboxVertex vertexData;
		vertexData.vertices = 
		{
			-1.0f, 1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,

			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,

			-1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f
		};
		m_model.AddVertexData( vertexData );

		m_textureCube.SetFaces(
		{
			"right.jpg",
		    "left.jpg",
		    "top.jpg",
		    "bottom.jpg",
		    "front.jpg",
		    "back.jpg"
		} );
		m_textureCube.LoadCubemap(ETextureType::Skybox);
		m_skyboxShader.Init( );

		return RSucces;
	}

	void SkyboxRenderer::Render( const NCamera &Camera )
	{
		glDepthFunc( GL_LEQUAL );

		m_model.BindVAO( );

		m_textureCube.Bind( );

		m_skyboxShader.Bind( );
		m_skyboxShader.SetProjectionMatrix( Camera );
		m_skyboxShader.SetViewMatrix( Camera );

		GL::DrawArraysInstanced( );

		GL::BindVao( 0 );
		m_textureCube.Unbind( );
		m_skyboxShader.Unbind( );
		glDepthFunc( GL_LESS );
	}
} // namespace Nocturn::rendering