/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 17-10-2021 17:26:54                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 08-12-2021 23:40:54                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef SKYBOX_RENDERER_H
#define SKYBOX_RENDERER_H

#include "core/GL/GLFunctions.h"
#include "data/model.hpp"

#include "rendering/components/shaders/skyboxshader.h"
#include "rendering/components/textures/texturecube.h"
#include "rendering/renderer/baserenderer.h"

namespace Nocturn::Render
{
	class SkyboxRenderer : IRenderer
	{
	public:
		SkyboxRenderer( ) noexcept = default;

		// cant copy
		SkyboxRenderer( const SkyboxRenderer & ) = delete;
		SkyboxRenderer( SkyboxRenderer && ) = delete;

		// cant move
		SkyboxRenderer &operator=( const SkyboxRenderer & ) = delete;
		SkyboxRenderer &operator=( SkyboxRenderer && ) = delete;

		void Render( const NCamera &Camera ) override;
		RStatus Init( ) override;

		~SkyboxRenderer( ) noexcept = default;

	private:
		Model< VertexDataType::SkyboxDataType > m_model;
		SkyboxShader m_skyboxShader;
		NTextureCube m_textureCube;
	};
} // namespace Nocturn::rendering

#endif