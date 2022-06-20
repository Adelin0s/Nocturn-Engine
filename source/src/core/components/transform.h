#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "core/types/typedef.hpp"

namespace Nocturn
{
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation;

		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;
	};

	namespace TransformSystem
	{
		void Init( Transform &transform );
		void Update( );
	}
} // namespace Nocturn

#endif