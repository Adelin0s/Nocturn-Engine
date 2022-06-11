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
	class Rigidbody
	{
	public:
		Rigidbody( ) noexcept;
		Rigidbody( float mass, const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &acceleration );
		Rigidbody( const Rigidbody &rigidbody ) = default; /* default behaviour  */
		Rigidbody( Rigidbody && )				= delete;

		Rigidbody &operator=( const Rigidbody & ) = delete;
		Rigidbody &operator=( Rigidbody && ) = delete;

		/* void setPosition(const glm::vec3 &position); */
		/* void setVelocity(const glm::vec3 &velocity); */
		/* void setAcceleration(const glm::vec3 &acceleration); */

		NODISCARD const glm::vec3 &GetPosition( ) const noexcept;

		void Update( const double dt );
		void ApplyForce( const glm::vec3 &force );
		void ApplyForce( const glm::vec3 &direction, const float magnitude );
		void ApplyAcceleration( const glm::vec3 &acceleration );
		void ApplyAcceleration( const glm::vec3 &direction, const float magnitude );
		void ApplyImpulse( const glm::vec3 &force, double dt );
		void ApplyImpulse( const glm::vec3 &direction, const float magnitude, const double dt );
		void TransferEnergy( const float joules, const glm::vec3 direction );

		~Rigidbody( ) noexcept = default;

	private:
		vec3 m_position;
		vec3 m_velocity;
		vec3 m_acceleration;

		float m_mass;
	};
} // namespace Nocturn
#endif