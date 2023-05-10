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
#include "Data/Model.hpp"

#include "Rendering/Components/Shaders/SkyboxShader.h"
#include "Rendering/Components/Textures/TextureCube.h"
#include "Rendering/Renderer/IRenderer.h"

namespace Nocturn
{
	class NSkyboxRenderer: public INRenderer
	{
	public:
		NSkyboxRenderer() noexcept = default;

		/** Cant copy. */
		NSkyboxRenderer(const NSkyboxRenderer& SkyboxRenderer) = delete;
		NSkyboxRenderer(NSkyboxRenderer&& SkyboxRenderer) = delete;

		/** Cant move. */
		NSkyboxRenderer& operator=(const NSkyboxRenderer& SkyboxRenderer) = delete;
		NSkyboxRenderer& operator=(NSkyboxRenderer&& SkyboxRenderer) = delete;

		bool Initialize() override;

		void Render(const NCameraComponent* CameraComponent) override;

		bool HasRendererTag(const std::string& RendererTagIn) override;

		~NSkyboxRenderer() noexcept override = default;

	private:
		Model< VertexDataType::SkyboxDataType > m_model;
		SkyboxShader							m_skyboxShader;
		NTextureCube							m_textureCube;
	};
} // namespace Nocturn

#endif