/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 24-08-2021 11:57:36                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 03-12-2021 10:32:03                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>

#include "core/components/transform.h"
#include "core/types/typedef.hpp"

namespace Nocturn
{
	struct RigidBody
	{
		void SetZeroForces( ) noexcept
		{
			velocity = vec3( 0.0f );
			acceleration = vec3(0.0f);
		}

		bool useGravity = true;
		vec3 acceleration{0.0f, -1.0f, 0.0f};
		vec3 velocity{ 0.0f, -20.0f, 0.0f };
	};
} // namespace Nocturn

#endif