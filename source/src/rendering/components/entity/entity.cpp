#include "entity.h"

namespace Nocturn
{
	Entity::Entity( const vec3& positionRef, const vec3& sizeRef )
		:		m_bound( positionRef, sizeRef )
	{ }
} // namespace Nocturn
