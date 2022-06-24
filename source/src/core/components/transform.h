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
	};

	namespace TransformSystem
	{
		void Init( Transform &transform );
		void Update( );
	}
} // namespace Nocturn

#endif