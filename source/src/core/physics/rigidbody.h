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

#include "core/platform/platform.h"
#include "core/types/typedef.hpp"

namespace Nocturn
{
	struct RigidBody
	{
		explicit RigidBody(const vec3& velocityRef)
		:	velocity( velocityRef )
		{ }

		void SetZeroForces( ) noexcept
		{
			velocity = vec3( 0.0f );
		}

		vec3 velocity {0.0f, 0.025f, 0.0f};
	};
} // namespace Nocturn


#endif