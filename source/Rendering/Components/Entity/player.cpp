#include "rendering/components/entity/player.h"

#include <iostream>

#include "application/input/keyboard.h"
#include "application/input/mouse.h"

namespace Nocturn
{
	NPlayer::NPlayer( ) noexcept
		,		m_pTransform( &transform )
		,		m_pRigidBody( &rigidbody )
		,		m_speed( 1.5f )
	{ }

	void NPlayer::Update( const double DeltaTime )
	{
		const Style playerBoxStyle( Colors::redWine, 0.05f );

		Render::DrawBox( m_pTransform->Position, CNPlayerBound, playerBoxStyle );

		m_bound.Update( );

		HandleMouseInput( );
		HandleKeyboardInput( );
	}

	void NPlayer::HandleMouseInput( ) const noexcept
	{
		
	}

	void NPlayer::HandleKeyboardInput( ) const noexcept
	{

	}
} // namespace Nocturn