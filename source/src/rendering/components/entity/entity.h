/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 01-12-2021 21:11:16                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 07-12-2021 19:38:22                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef ENTITY_H
#define ENTITY_H

#include "core/physics/AABB.h"

namespace Nocturn
{
	struct Entity
	{
		Entity( ) noexcept;

		Entity( const glm::vec3 &pos, const glm::vec3 &rot );
		Entity( const glm::vec3 &pos, const glm::vec3 &rot, const glm::vec3 &box );

		// TODO : View entity virtual functions
		//virtual void Collide( ) NOCTURN_PURE;
		//virtual void Update( ) NOCTURN_PURE;
		//virtual void GetBox( ) NOCTURN_PURE;

		virtual ~Entity( ) noexcept NOCTURN_PURE;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 velocity;

		AABB box;
	};
} // namespace Nocturn

#endif