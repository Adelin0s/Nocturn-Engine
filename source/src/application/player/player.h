/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 01-12-2021 21:11:16                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 07-12-2021 19:38:22                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "core/physics/rigidbody.h"
#include "rendering/data/camera.h"

namespace Nocturn
{
	struct Entity
	{
	};

	class Player: public Entity
	{
	public:
		Player( ) noexcept;

		Player( const Player &player ) = delete;
		Player( Player &&player )	   = delete;

		Player &operator=( const Player &player ) = delete;
		Player &operator=( Player &&player ) = delete;

		NODISCARD vec3			GetPlayerPosition( ) const noexcept;
		NODISCARD const Camera &GetCamera( ) const noexcept;

		void Init( ) noexcept;
		void Update( const double dt );

		~Player( ) noexcept = default;

	private:
		vec3					  m_position;
		std::unique_ptr< Camera > m_camera;
		// Rigidbody				  m_rigidbody; inactive
	};
} // namespace Nocturn

#endif