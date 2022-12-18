// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin
//   @ Create Time: 18-12-2022 2:25 PM
//   @ Contact: cucorianu.adelin@protonmail.com
//   @ Modified time: 18-12-2022 2:25 PM
//   @ Description:
// =====================================================================

#ifndef BASE_RENDERER_H
#define BASE_RENDERER_H

#include "core/core.h"

namespace Nocturn::Render
{
	class BaseRenderer
	{
	public:
		BaseRenderer() noexcept;

		virtual RStatus Init( ) = 0;
		virtual RStatus Render( const Camera &camera ) = 0;

		virtual ~BaseRenderer() noexcept = default;
	};
} // namespace Nocturn::Render
#endif