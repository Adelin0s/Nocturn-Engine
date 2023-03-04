#include "core/physics/AABB.h"

namespace Nocturn
{
	AABB::AABB( const vec3 &position, const vec3 &size ) noexcept
		:	position( position )
		,	size( size )
		,	min( position - size )
		,	max( position + size )
	{ }

	void AABB::Update() noexcept
	{
		min = (position - 0.5f) - size * 0.5f;
		max = (position - 0.5f) + size * 0.5f;
	}
}
