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
#include "core/platform/platform.h"

namespace Nocturn
{
	struct Entity
	{
		Entity() noexcept = delete;
		Entity( const vec3& positionRef, const vec3& sizeRef );

		// cant copy
		Entity( const Entity &entity ) = delete;
		Entity &operator=( const Entity &entity ) = delete;

		// cant move
		Entity &operator=( Entity &&entity ) = delete;
		Entity( Entity &&entity ) = delete;

		NODISCARD virtual const AABB &GetBound( ) const noexcept NOCTURN_PURE;
		virtual void Update( double dt ) NOCTURN_PURE;

		virtual ~Entity( ) noexcept = default;

	protected:
		AABB m_bound;
	};
} // namespace Nocturn

#endif