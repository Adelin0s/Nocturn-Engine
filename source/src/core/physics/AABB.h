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
		AABB( const vec3 &positionRef, const vec3 &sizeRef );

		~AABB( ) noexcept = default;

		void Update( const vec3& positionRef ) noexcept;

		NODISCARD vec3 GetMin( ) const noexcept;
		NODISCARD vec3 GetMax( ) const noexcept;

		vec3 position{};
		vec3 size{};
	};
} // namespace Nocturn::Physics

#endif
