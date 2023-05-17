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

		/**
		 * @brief Initializes the skybox renderer.
		 * @return True if initialization is successful, false otherwise.
		 */
		bool Initialize() override;

		/**
		 * @brief Checks if the renderer has a specific renderer tag.
		 * @param RendererTagIn The renderer tag to check.
		 * @return True if the renderer has the specified tag, false otherwise.
		 */
		bool HasRendererTag(const std::string& RendererTagIn) override;

		/**
		 * @brief Reloads the shaders used by the skybox renderer.
		 */
		void ReloadShaders() override;

		/**
		 * @brief Renders the skybox using the specified camera component.
		 * @param CameraComponent The camera component to use for rendering.
		 * @param bShouldReloadShaders Flag indicating whether the shaders should be reloaded before rendering.
		 */
		void Render(const NCameraComponent* CameraComponent, bool bShouldReloadShaders = false) override;

		~NSkyboxRenderer() noexcept override = default;

	private:
		/**< The model of the skybox. */
		Model< VertexDataType::SkyboxDataType > m_model;

		/**< The skybox shader. */
		SkyboxShader m_skyboxShader;

		/**< The skybox texture cube. */
		NTextureCube m_textureCube;
	};
} // namespace Nocturn

#endif