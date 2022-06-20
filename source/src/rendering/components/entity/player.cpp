#include "rendering/components/entity/player.h"

#include "application/input/keyboard.h"
#include "application/input/mouse.h"

namespace Nocturn
{
	static constexpr double CMouseSensitivity = 0.1;

	Player::Player( Transform &transform ) noexcept
		:
		m_pTransform( &transform ), m_speed( 10 )
	{}

	void Player::Update( const double dt ) const
	{
		HandleMouseInput( dt );
		HandleKeyboardInput( dt );
		m_pTransform->position.y -= 0.1f;
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
		float speed = 2.5f;
		if( Keyboard::key( GLFW_KEY_LEFT_SHIFT ) )
			speed = 10.0f;
		const float velocity = m_speed * static_cast< float >( dt ) * speed;

		if( Keyboard::key( GLFW_KEY_W ) )
		{
			m_pTransform->position += m_pTransform->forward * velocity;
		}
		if( Keyboard::key( GLFW_KEY_S ) )
		{
			m_pTransform->position -= m_pTransform->forward * velocity;
		}
		if( Keyboard::key( GLFW_KEY_A ) )
		{
			m_pTransform->position -= m_pTransform->right * velocity;
		}
		if( Keyboard::key( GLFW_KEY_D ) )
		{
			m_pTransform->position += m_pTransform->right * velocity;
		}
		if( Keyboard::key( GLFW_KEY_Q ) )
		{
			m_pTransform->position.y -= 1.0f * velocity;
		}
		if( Keyboard::key( GLFW_KEY_E ) )
		{
			m_pTransform->position.y += 1.0f * velocity;
		}
	}
} // namespace Nocturn