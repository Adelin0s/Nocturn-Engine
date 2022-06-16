#include "rendering/renderer/skyboxrenderer.h"

namespace Nocturn::rendering
{
	SkyboxRendering::SkyboxRendering( )
	{
		std::vector< float > vertices = {
			-1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,

			-1.0f,
			-1.0f,
			1.0f,
			-1.0f,
			-1.0f,
			-1.0f,
			-1.0f,
			1.0f,
			-1.0f,
			-1.0f,
			1.0f,
			-1.0f,
			-1.0f,
			1.0f,
			1.0f,
			-1.0f,
			-1.0f,
			1.0f,

			1.0f,
			-1.0f,
			-1.0f,
			1.0f,
			-1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			-1.0f,
			1.0f,
			-1.0f,
			-1.0f,

			-1.0f,
			-1.0f,
			1.0f,
			-1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			-1.0f,
			1.0f,
			-1.0f,
			-1.0f,
			1.0f,

			-1.0f,
			1.0f,
			-1.0f,
			1.0f,
			1.0f,
			-1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			1.0f,
			-1.0f,
			1.0f,
			1.0f,
			-1.0f,
			1.0f,
			-1.0f,

			-1.0f,
			-1.0f,
			-1.0f,
			-1.0f,
			-1.0f,
			1.0f,
			1.0f,
			-1.0f,
			-1.0f,
			1.0f,
			-1.0f,
			-1.0f,
			-1.0f,
			-1.0f,
			1.0f,
			1.0f,
			-1.0f,
			1.0f
		};

		m_model.generateVAO( );
		m_model.addVBO( 3, vertices );
		m_textureCube.setFaces(
			{ "right.jpg",
			  "left.jpg",
			  "top.jpg",
			  "bottom.jpg",
			  "front.jpg",
			  "back.jpg" } );
		m_textureCube.loadCubemap( "skybox" );
		m_skyboxShader.init( );
	}

	void SkyboxRendering::render( const Camera &camera )
	{
		glDepthFunc( GL_LEQUAL );
		m_model.bindVAO( );
		m_textureCube.bind( );
		m_skyboxShader.activate( );
		m_skyboxShader.setProjectionMatrix( camera );
		m_skyboxShader.setViewMatrix( camera );
		GL::drawArraysInstanced( );
		m_textureCube.unbind( );
		VertexArray::clear( );
		glDepthFunc( GL_LESS );
	}
} // namespace Nocturn::rendering