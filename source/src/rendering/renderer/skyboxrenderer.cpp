#include "rendering/renderer/skyboxrenderer.h"

namespace Nocturn::Render
{
	RStatus SkyboxRenderer::Init( )
	{
		VertexType::SkyboxVertex vertexData;
		vertexData.vertices = {
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

		m_textureCube.setFaces(
		{
			"right.jpg",
		    "left.jpg",
		    "top.jpg",
		    "bottom.jpg",
		    "front.jpg",
		    "back.jpg"
		} );
		m_textureCube.loadCubemap( "skybox" );
		m_skyboxShader.init( );

		return RSucces;
	}

	RStatus SkyboxRenderer::Render( const Camera &camera )
	{
		glDepthFunc( GL_LEQUAL );

		m_model.BindVAO( );

		m_textureCube.bind( );

		m_skyboxShader.bind( );
		m_skyboxShader.setProjectionMatrix( camera );
		m_skyboxShader.setViewMatrix( camera );

		GL::DrawArraysInstanced( );

		m_textureCube.unbind( );
		glDepthFunc( GL_LESS );

		return RSucces;
	}
} // namespace Nocturn::rendering