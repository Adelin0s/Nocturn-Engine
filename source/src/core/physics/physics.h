#ifndef PHYSICS_H
#define PHYSICS_H

#include "core/components/transform.h"

#include "core/physics/rigidbody.h"
#include "core/types/typedef.hpp"
#include "rendering/components/entity/player.h"
#include "rendering/world/chunk/chunkmanager.h"

namespace Nocturn
{
	using namespace rendering;

	class Physics
	{
	public:
		Physics( ) noexcept = delete;
		Physics( const Entity &player, ChunkManager &chunkManager, Transform &transform, RigidBody &rigidBody );

		// cant copy
		Physics( const Physics &rigidBody ) = delete;
		Physics &operator=( const Physics &rigidBody ) = delete;

		// cant move
		Physics &operator=( Physics &&rigidBody ) = delete;
		Physics( Physics &&rigidBody )			  = delete;

		void Update( double dt );

		~Physics( ) noexcept = default;

	private:
		const Entity  *m_pPlayer{ };
		ChunkManager  *m_pChunkManager{ };
		Transform	  *m_pTransform{ };
		RigidBody	  *m_pRigidBody{ };
		vec3		   normal{ 0.0f };

		static constexpr inline vec3 CMaxVelocity{ 5.0f };
		static constexpr inline vec3 CGravity{ 0.0f, -6.8f, 0.0f };
		static constexpr inline float CPhysicsUpdateRate = 1.0f / 120;
		static constexpr inline float CHorizontalDrag = 8.0f;
		static constexpr inline float CVerticalDrag = 1.0f;

		void  ProcessCollision( float &minTime, const vec3& velocity ) noexcept;
		NODISCARD float SweptCollision( const vec3 &velocity, const vec3 &min, const vec3 &max, const vec3 &minI, const vec3 &maxI, float minTime, float x, float y, float z ) noexcept;
	};

} // namespace Nocturn

#endif