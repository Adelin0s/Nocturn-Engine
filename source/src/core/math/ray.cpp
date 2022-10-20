#include "ray.h"

namespace Nocturn
{
	Ray::Ray( const glm::vec3 &position, const vec3 &direction )
	{}

	void Ray::Step( const float scale ) noexcept
	{
		//
	}

	const vec3 &Ray::GetEnd( ) const noexcept
	{
		return vec3( );
	}

	float Ray::GetLength( ) const noexcept
	{
		return 0.;
	}
} // namespace Nocturn