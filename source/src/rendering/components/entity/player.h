/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 01-12-2021 21:11:16                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 07-12-2021 19:38:22                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "core/physics/AABB.h"
#include "core/physics/rigidbody.h"

#include "rendering/components/entity/camera.h"
#include "rendering/components/entity/entity.h"

#include "rendering/renderer/renderer.h"

namespace Nocturn
{
	using namespace rendering;

	class Player final: public Entity
	{
	public:
		static inline constexpr double CMouseSensitivity = 0.1;
		static inline constexpr vec3   CPlayerBound		 = { 0.55f, 1.8f, 0.55 };

		Player( ) noexcept = delete;
		Player( Transform &transform, RigidBody &rigidbody ) noexcept;

		// cant copy
		Player( const Player &player ) = delete;
		Player &operator=( const Player &player ) = delete;

		// cant move
		Player &operator=( Player &&player ) = delete;
		Player( Player &&player ) = delete;

		NODISCARD const AABB &GetBound( ) const noexcept override;
		void Update( double dt ) override;

		~Player( ) noexcept override = default;

	private:
		Transform *m_pTransform{ };
		RigidBody *m_pRigidBody{ };
		vec3	   m_position{ };
		bool	   m_type = true;
		float	   m_speed;

		void HandleMouseInput( ) const noexcept;
		void HandleKeyboardInput( ) const noexcept;
	};
} // namespace Nocturn

#endif