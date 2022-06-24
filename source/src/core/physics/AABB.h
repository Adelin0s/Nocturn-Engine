#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>

#include "core/platform/platform.h"
#include "core/types/typedef.hpp"

namespace Nocturn
{
	struct AABB
	{
		AABB( ) noexcept = delete;
		AABB( const vec3 &sizeRef );

		~AABB( ) noexcept = default;

		vec3 origin{};
		vec3 size{};
	};
} // namespace Nocturn::Physics

#endif
