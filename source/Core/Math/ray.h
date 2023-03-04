#ifndef RAY_H
#define RAY_H

#include "core/types/typedef.hpp"

namespace Nocturn
{
	class Ray
	{
	public:
		Ray( ) noexcept = delete;
		Ray( const vec3 &position, const vec3 &direction );

		// cant copy
		Ray( const Ray & ) = delete;
		Ray &operator=( const Ray & ) = delete;

		// cant move
		Ray( Ray && ) = delete;
		Ray operator=( Ray && ) = delete;

		void		Step( const float scale ) noexcept;
		const vec3 &GetEnd( ) const noexcept;
		float		GetLength( ) const noexcept;

		~Ray( ) noexcept = default;

	private:
		vec3 m_origin;
		vec3 m_direction;
	};

} // namespace Nocturn

#endif