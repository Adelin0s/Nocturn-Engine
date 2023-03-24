#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "core/types/typedef.hpp"

namespace Nocturn
{
	struct NTransform
	{
		vec3 Position;
		vec3 Scale;
		vec3 Rotation;

		vec3 Forward;
		vec3 Up;
		vec3 Right;
		vec3 Direction;
	};

	namespace TransformSystem
	{
		void Update( NTransform *Transform );
	}
} // namespace Nocturn

#endif