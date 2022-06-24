#include "rendering/components/entity/player.h"

#include <iostream>

#include "application/input/keyboard.h"
#include "application/input/mouse.h"

namespace Nocturn
{
	Player::Player( Transform &transform, RigidBody& rigidbody ) noexcept
		:		Entity( CPlayerBound )
		,		m_pTransform( &transform )
		,		m_pRigidBody( &rigidbody )
		,		m_speed( 2.5f )
	{ }

	const AABB& Player::GetBound( ) const noexcept
	{
		return m_bound;
	}

	void Player::Update( const double dt )
	{
		m_pRigidBody->velocity.x = 0;
		m_pRigidBody->velocity.z = 0;

		HandleMouseInput( dt );
		HandleKeyboardInput( dt );
	}

	void Player::HandleMouseInput( const double dt ) const
	{
		double dx = Mouse::getDx( );
		double dy = Mouse::getDy( );

		if( dx || dy )
		{
			dx *= CMouseSensitivity;
			dy *= CMouseSensitivity;

			m_pTransform->rotation.x += dx;
			m_pTransform->rotation.y += dy;

			if( m_pTransform->rotation.y > 89.0f )
				m_pTransform->rotation.y = 89.0f;
			if( m_pTransform->rotation.y < -89.0f )
				m_pTransform->rotation.y = -89.0f;
		}
	}

	void Player::HandleKeyboardInput( const double dt ) const
	{
		float localSpeed = m_speed;
		if( Keyboard::key( GLFW_KEY_LEFT_SHIFT ) )
			localSpeed = m_speed + 5.0f;

		if( Keyboard::key( GLFW_KEY_W ) )
		{
			m_pRigidBody->velocity.x += m_pTransform->forward.x * localSpeed;
			m_pRigidBody->velocity.z += m_pTransform->forward.z * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_S ) )
		{
			m_pRigidBody->velocity.x += -m_pTransform->forward.x * localSpeed;
			m_pRigidBody->velocity.z += -m_pTransform->forward.z * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_A ) )
		{
			m_pRigidBody->velocity.x += -m_pTransform->right.x * localSpeed;
			m_pRigidBody->velocity.z += -m_pTransform->right.z * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_D ) )
		{
			m_pRigidBody->velocity.x += m_pTransform->right.x * localSpeed;
			m_pRigidBody->velocity.z += m_pTransform->right.z * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_Q ) )
		{
			m_pTransform->position.y -= 0.15f;
		}
		if( Keyboard::key( GLFW_KEY_E ) )
		{
			m_pTransform->position.y += 0.15f;
		}
	}
} // namespace Nocturn