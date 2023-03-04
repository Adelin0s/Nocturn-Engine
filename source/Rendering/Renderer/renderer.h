#ifndef RENDERER_H
#define RENDERER_H

#include "core/types/typedef.hpp"

#include "rendering/components/entity/camera.h"
#include "rendering/renderer/style.h"

namespace Nocturn::Render
{
	void Init( const NCamera &Camera );

	void DrawLine( const vec3 &start, const vec3 &end, const Style &style );
	void DrawBox( const vec3 &position, const vec3 &size, const Style &style );

	void Render( );

	void Free( );
}

#endif