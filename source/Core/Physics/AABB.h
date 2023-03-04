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
		AABB( const vec3& position, const vec3& size) noexcept;

		// cant copy
		AABB( const AABB & ) = delete;
		AABB &operator=( const AABB & ) = delete;

		// cant move
		AABB( AABB &&) = delete;
		AABB &operator=( AABB && ) = delete;

		void Update( ) noexcept;

		~AABB() noexcept = default;

		const vec3 &position{ };
		const vec3 &size{ };
		vec3		min{ };
		vec3		max{ };
	};
} // namespace Nocturn::Physics

#endif
