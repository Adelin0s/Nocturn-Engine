// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin                                                                                      
//   @ Create Time: 01-12-2021 21:11:16                                                                                                                                             
//   @ Contact: cucorianu.adelin@protonmail.com                                                                                                                          
//   @ Modified time: 15-03-2023 12:58 AM                                                                                                                                    
//   @ Description:                                                                                                                                                                                
// =====================================================================

#pragma once

#include "Context/GameFramework/Actor.h"

#include "core/physics/AABB.h"
#include "core/physics/rigidbody.h"

#include "rendering/components/entity/camera.h"
#include "rendering/components/entity/entity.h"

#include "rendering/renderer/renderer.h"

namespace Nocturn
{
	class NPlayer: public NActor
	{
	public:
		static inline constexpr vec3 CNPlayerBound = { 0.55f, 1.8f, 0.55 };

		NPlayer( ) noexcept = delete;

		// cant copy
		NPlayer( const NPlayer &Player ) = delete;
		NPlayer &operator=( const NPlayer &Player ) = delete;

		// cant move
		NPlayer &operator=( NPlayer &&Player ) = delete;
		NPlayer( NPlayer &&Player ) = delete;

		/** Method that is called every frame. */
		void Update( double DeltaTime ) override;

		~NPlayer( ) noexcept override = default;

	private:
		NTransform *m_pTransform{ };
		NRigidBody *m_pRigidBody{ };

		void HandleMouseInput( ) const noexcept;
		void HandleKeyboardInput( ) const noexcept;
	};
} // namespace Nocturn
