#include "rendering/renderer/skyboxrenderer.h"

namespace Nocturn::rendering
{
	SkyboxRendering::SkyboxRendering( )
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
	}

	void SkyboxRendering::render( const Camera &camera )
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
	}
} // namespace Nocturn::rendering