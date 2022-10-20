#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "core/types/typedef.hpp"

namespace Nocturn
{
	struct Transform
	{
		vec3 position;
		vec3 scale;
		vec3 rotation;

		vec3 forward;
		vec3 up;
		vec3 right;

		vec3 direction;
	};

	namespace TransformSystem
	{
		void Update( Transform *transform );
	}
} // namespace Nocturn

#endif