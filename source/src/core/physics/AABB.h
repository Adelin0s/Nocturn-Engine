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
		AABB( const vec3 &size );

		~AABB( ) noexcept = default;

	private:
		vec3 m_origin{};
		vec3 m_size{};
	};
} // namespace Nocturn::Physics

#endif
