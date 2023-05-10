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

		virtual bool Initialize() = 0;

		virtual void Render(const NCameraComponent* CameraComponent) = 0;

		virtual bool HasRendererTag(const std::string& RendererTagIn) = 0;

		virtual ~INRenderer() noexcept = default;

	protected:
		std::string RendererTag;
	};
} // namespace Nocturn
#endif