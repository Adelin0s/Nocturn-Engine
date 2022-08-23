#include "rendering/components/entity/player.h"

#include <iostream>

#include "application/input/keyboard.h"
#include "application/input/mouse.h"

namespace Nocturn
{
	Player::Player( Transform &transform, RigidBody& rigidbody ) noexcept
		:		Entity( transform.position, CPlayerBound )
		,		m_pTransform( &transform )
		,		m_pRigidBody( &rigidbody )
		,		m_speed( 0.5f )
	{ }

	const AABB& Player::GetBound( ) const noexcept
	{
		return m_bound;
	}

	void Player::Update( const double dt )
	{
		const Style playerBoxStyle( Colors::redWine, 0.05f );

		Renderer::DrawBox( m_pTransform->position, CPlayerBound, playerBoxStyle );

		m_bound.Update( );

		//HandleMouseInput( );
		HandleKeyboardInput( );
	}

	void Player::HandleMouseInput( ) const noexcept
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

	void Player::HandleKeyboardInput( ) const noexcept
	{
		float localSpeed = m_speed;
		if( Keyboard::key( GLFW_KEY_LEFT_SHIFT ) )
			localSpeed = m_speed + 5.0f;

		m_pRigidBody->velocity.x = 0;
		m_pRigidBody->velocity.z = 0;

		if( Keyboard::key( GLFW_KEY_UP ) )
		{
			m_pRigidBody->velocity.x = m_pTransform->forward.x * localSpeed;
			m_pRigidBody->velocity.z = m_pTransform->forward.z * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_DOWN ) )
		{
			m_pRigidBody->velocity.x = -m_pTransform->forward.x * localSpeed;
			m_pRigidBody->velocity.z = -m_pTransform->forward.z * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_LEFT ) )
		{
			m_pRigidBody->velocity.x = -m_pTransform->right.x * localSpeed;
			m_pRigidBody->velocity.z = -m_pTransform->right.z * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_RIGHT ) )
		{
			m_pRigidBody->velocity.x = m_pTransform->right.x * localSpeed;
			m_pRigidBody->velocity.z = m_pTransform->right.z * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_Q ) )
		{
			m_pTransform->position.y -= 0.5f;
		}
		if( Keyboard::key( GLFW_KEY_E ) )
		{
			m_pTransform->position.y += 0.5f;
		}
	}
} // namespace Nocturn