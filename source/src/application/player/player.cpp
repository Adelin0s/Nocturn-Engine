#include "application/player/player.h"

namespace Nocturn
{
	Player::Player( ) noexcept :
		m_position( glm::vec3( 0.0f, 260.0f, 2.0f ) )
	{}

	vec3 Player::GetPlayerPosition( ) const noexcept
	{
		return m_camera->getCameraPosition( );
	}

	const Camera &Player::GetCamera( ) const noexcept
	{
		return *m_camera;
	}

	void Player::Init( ) noexcept
	{
		m_camera = std::make_unique< Camera >( );
	}

	void Player::Update( const double dt )
	{
		m_camera->Update( dt );
	}
} // namespace Nocturn