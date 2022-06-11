#include "rigidbody.h"

#include <cmath>
#include <iostream>

namespace Nocturn
{
	Rigidbody::Rigidbody( ) noexcept :
		m_position( 0.0f ),
		m_velocity( 0 ),
		m_acceleration( 0 ),
		m_mass( 1.0f )
	{}

	Rigidbody::Rigidbody( float mass, const glm::vec3 &position, const glm::vec3 &velocity, const glm::vec3 &acceleration ) :
		m_mass( mass ), m_position( position ), m_velocity( velocity ), m_acceleration( acceleration )
	{}

	const glm::vec3 &Rigidbody::GetPosition( ) const noexcept
	{
		return m_position;
	}

	void Rigidbody::Update( const double dt )
	{
		// TODO: Update vec3(float) to vec3(double)
		const auto fdt = static_cast< float >( dt );

		m_position += m_velocity * fdt + 0.5f * m_acceleration * ( fdt * fdt );
		m_velocity += m_acceleration * fdt;
	}

	void Rigidbody::ApplyForce( const glm::vec3 &force )
	{
		m_acceleration += force / m_mass;
	}

	void Rigidbody::ApplyForce( const glm::vec3 &direction, const float magnitude )
	{
		ApplyForce( direction * magnitude );
	}

	void Rigidbody::ApplyAcceleration( const glm::vec3 &acceleration )
	{
		m_acceleration += acceleration;
	}

	void Rigidbody::ApplyAcceleration( const glm::vec3 &direction, const float magnitude )
	{
		ApplyForce( direction * magnitude );
	}

	void Rigidbody::ApplyImpulse( const glm::vec3 &force, const double dt )
	{
		m_velocity += force / m_mass * static_cast< float >( dt );
	}

	void Rigidbody::ApplyImpulse( const glm::vec3 &direction, const float magnitude, const double dt )
	{
		ApplyImpulse( direction * magnitude, dt );
	}

	void Rigidbody::TransferEnergy( const float joules, const glm::vec3 direction )
	{
		if( joules == 0.f )
		{
			return;
		}

		// comes from formula: KE = 1/2 * m * v^2
		const glm::vec3 deltaV = direction * sqrt( 2 * std::abs( joules ) / m_mass );

		m_velocity += joules > 0 ? deltaV : -deltaV;
	}
} // namespace Nocturn