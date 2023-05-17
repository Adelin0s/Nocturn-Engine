// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin
//   @ Create Time: 18-12-2022 2:25 PM
//   @ Contact: cucorianu.adelin@protonmail.com
//   @ Modified time: 18-12-2022 2:25 PM
//   @ Description:
// =====================================================================

#ifndef BASE_RENDERER_H
#define BASE_RENDERER_H

#include "Core/core.h"
#include "Context/Components/CameraComponent.h"

namespace Nocturn
{
	class INRenderer
	{
	public:
		INRenderer() noexcept = default;

		/**
		 * @brief Initializes the renderer.
		 * @return True if initialization is successful, false otherwise.
		 */
		virtual bool Initialize() = 0;

		/**
		 * @brief Checks if the renderer has a specific renderer tag.
		 * @param RendererTagIn The renderer tag to check.
		 * @return True if the renderer has the specified tag, false otherwise.
		 */
		virtual bool HasRendererTag(const std::string& RendererTagIn) = 0;

		/**
		 * @brief Reloads the shaders used by the renderer.
		 */
		virtual void ReloadShaders() = 0;

		/**
		 * @brief Renders the scene using the specified camera component.
		 * @param CameraComponent The camera component to use for rendering.
		 * @param bShouldReloadShaders Flag indicating whether the shaders should be reloaded before rendering.
		 */
		virtual void Render(const NCameraComponent* CameraComponent, bool bShouldReloadShaders = false) = 0;

		virtual ~INRenderer() noexcept = default;

	protected:
		/** The tag associated with the renderer. */
		std::string RendererTag;
	};
} // namespace Nocturn
#endif