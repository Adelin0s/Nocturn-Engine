#ifndef SPECTATOR_H
#define SPECTATOR_H

#include "entity.h"
#include "core/physics/rigidbody.h"

namespace Nocturn
{
	class Spectator final: public Entity
	{
	public:
		Spectator() noexcept = delete;
		Spectator( NTransform &transform ) noexcept;

		// cant copy
		Spectator( const Spectator & ) = delete;
		Spectator &operator=( const Spectator & ) = delete;

		// cant move
		Spectator( Spectator && ) = delete;
		Spectator &operator=( Spectator && ) = delete;

		NODISCARD const AABB &GetBound( ) const noexcept override;
		void Update( double DeltaTime ) override;

		~Spectator() noexcept override = default;
 
	private:
		NTransform *m_pTransform{ };
		NRigidBody *m_pRigidBody{ };
		float	   m_speed;

		void HandleMouseInput( ) const noexcept;
		void HandleKeyboardInput( ) const noexcept;
	};
}

#endif 