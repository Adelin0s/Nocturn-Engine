#include "spectator.h"

#include "player.h"
#include "application/input/keyboard.h"
#include "application/input/mouse.h"

namespace Nocturn
{
	Spectator::Spectator( NTransform &Transform) noexcept
		:		Entity( Transform.Position, vec3(1.0f, 1.0f, 1.0f) )
		,		m_pTransform( &Transform )
		,		m_speed( 0.05f )
	{ }

	const AABB &Spectator::GetBound( ) const noexcept
	{
		return m_bound;
	}

	void Spectator::Update( double DeltaTime )
	{
		HandleKeyboardInput( );
		HandleMouseInput( );
	}

	void Spectator::HandleMouseInput( ) const noexcept
	{
		double dx = Mouse::getDx( );
		double dy = Mouse::getDy( );

		if( dx || dy )
		{
			dx *= NPlayer::CMouseSensitivity;
			dy *= NPlayer::CMouseSensitivity;

			m_pTransform->Rotation.x += dx;
			m_pTransform->Rotation.y += dy;

			if( m_pTransform->Rotation.y > 89.0f )
				m_pTransform->Rotation.y = 89.0f;
			if( m_pTransform->Rotation.y < -89.0f )
				m_pTransform->Rotation.y = -89.0f;
		}
	}

	void Spectator::HandleKeyboardInput( ) const noexcept
	{
		float localSpeed = m_speed;
		if( Keyboard::key( GLFW_KEY_LEFT_SHIFT ) )
			localSpeed = m_speed + 5.0f;

		if( Keyboard::key( GLFW_KEY_W ) )
		{
			m_pTransform->Position += m_pTransform->Forward * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_S ) )
		{
			m_pTransform->Position -= m_pTransform->Forward * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_A ) )
		{
			m_pTransform->Position -= m_pTransform->Right * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_D ) )
		{
			m_pTransform->Position += m_pTransform->Right * localSpeed;
		}
		if( Keyboard::key( GLFW_KEY_Q ) )
		{
			//m_pTransform->position.y -= 0.15f;
		}
		if( Keyboard::key( GLFW_KEY_E ) )
		{
			//m_pTransform->position.y += 0.15f;
		}
	}
}
