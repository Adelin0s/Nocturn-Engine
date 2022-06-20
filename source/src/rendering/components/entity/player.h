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

#include "rendering/components/entity/camera.h"
#include "rendering/components/entity/entity.h"

namespace Nocturn
{
	class Player
	{
	public:
		Player( ) noexcept = delete;
		explicit Player( Transform &transform ) noexcept;

		// cant copy
		Player( const Player &player ) = delete;
		Player &operator=( const Player &player ) = delete;

		// cant move
		Player &operator=( Player &&player ) = delete;
		Player( Player &&player )	   = delete;

		void Update( double dt ) const;

		~Player( ) noexcept = default;

	private:
		Transform *m_pTransform{};
		float	   m_speed;

		void HandleMouseInput( double dt ) const;
		void HandleKeyboardInput( double dt ) const;
	};
} // namespace Nocturn

#endif