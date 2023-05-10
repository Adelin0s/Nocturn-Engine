#ifndef RENDERER_H
#define RENDERER_H

#include "core/types/typedef.hpp"

#include "rendering/renderer/style.h"

namespace Nocturn
{
	// Forward declares
	class NCameraComponent;
}

namespace Nocturn::Render
{
	void Init(const NCameraComponent* CameraComponentIn);

	void DrawLine(const vec3& start, const vec3& end, const Style& style);
	void DrawBox(const vec3& position, const vec3& size, const Style& style);

	void Render();

	void Free();
}

#endif