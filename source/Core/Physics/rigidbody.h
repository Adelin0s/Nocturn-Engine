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

#include "core/types/typedef.hpp"

namespace Nocturn
{
	struct NRigidBody
	{
		void SetZeroForces( ) noexcept
		{
			Velocity = vec3( 0.0f );
			Acceleration = vec3(0.0f);
		}

		bool UseGravity = true;
		bool OnGround = false;
		vec3 Acceleration{1.0f, 0.0f, 1.0f};
		vec3 Velocity{ 0.0f, -5.0f, 0.0f };
	};
} // namespace Nocturn

#endif