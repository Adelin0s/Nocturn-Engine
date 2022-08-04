#include "core/physics/AABB.h"

namespace Nocturn
{
	AABB::AABB( const vec3 &positionRef, const vec3 &sizeRef )
		:	position( positionRef )
		,	size( sizeRef )
	{ }

	void AABB::Update( const vec3 &positionRef ) noexcept
	{
		position = positionRef;
	}

	vec3 AABB::GetMin( ) const noexcept
	{
		const vec3 p1 = position + size * 0.5f;
		const vec3 p2 = position - size * 0.5f;

		return { fminf( p1.x, p2.x ),
				 fminf( p1.y, p2.y ),
				 fminf( p1.z, p2.z ) };
	}

	vec3 AABB::GetMax( ) const noexcept
	{
		const vec3 p1 = position + size * 0.5f;
		const vec3 p2 = position - size * 0.5f;

		return { fmaxf( p1.x, p2.x ),
				 fmaxf( p1.y, p2.y ),
				 fmaxf( p1.z, p2.z ) };
	}
}
