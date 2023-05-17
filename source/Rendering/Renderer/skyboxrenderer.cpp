#include "rendering/renderer/skyboxrenderer.h"

#include "application/input/keyboard.h"
#include "Context/Components/CameraComponent.h"

namespace Nocturn
{
	bool NSkyboxRenderer::Initialize()
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
		m_skyboxShader.Init();

		RendererTag = "SkyboxRenderer";

		return true;
	}

	bool NSkyboxRenderer::HasRendererTag(const std::string& RendererTagIn)
	{
		return RendererTag == RendererTagIn;
	}

	void NSkyboxRenderer::ReloadShaders()
	{
		m_skyboxShader.ReloadShader();	
	}

	void NSkyboxRenderer::Render(const NCameraComponent* CameraComponent, const bool bShouldReloadShaders)
	{
		glDepthFunc( GL_LEQUAL );

		if (bShouldReloadShaders)
		{
			m_skyboxShader.ReloadShader();
		}
		m_model.BindVAO( );
		m_textureCube.Bind( );
		m_skyboxShader.Bind( );

		m_skyboxShader.SetProjectionMatrix(CameraComponent->GetProjectionMatrix());
		m_skyboxShader.SetViewMatrix(CameraComponent->GetViewMatrix());

		GL::DrawArraysInstanced( );

		GL::BindVao( 0 );
		m_textureCube.Unbind( );
		m_skyboxShader.Unbind( );
		glDepthFunc( GL_LESS );
	}
} // namespace Nocturn