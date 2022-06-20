#ifndef RENDERER_H
#define RENDERER_H

#include "core/types/typedef.hpp"

#include "rendering/components/entity/camera.h"
#include "style.h"

namespace Nocturn::Renderer
{
	using namespace rendering;

	void Init( const Camera &cameraRef );
	void Render( );

	void DrawLine( const vec3 &start, const vec3 &end, const Style &style );
	void DrawBox( const glm::vec3 &center, const glm::vec3 &size, const Style &style );

	void Free( );
} // namespace Nocturn::Renderer

#endif