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

	struct RaycastResult
	{
		vec3 point;
		vec3 blockCenter;
		vec3 blockSize;
		vec3 hitNormal;
		bool hit;
	};

	class NPhysics
	{
	public:
		NPhysics( ) noexcept = delete;
		NPhysics( const Entity &player, ChunkManager &chunkManager, NTransform &transform, NRigidBody &rigidBody );

		// cant copy
		NPhysics( const NPhysics &NPhysics ) = delete;
		NPhysics &operator=( const NPhysics &NPhysics ) = delete;

		// cant move
		NPhysics &operator=( NPhysics &&Physics ) = delete;
		NPhysics( NPhysics &&Physics ) = delete;

		NODISCARD RaycastResult RaycastStatic( const vec3 &Origin, const vec3 &NormalDirection, float MaxDistance, bool bDraw = false ) const noexcept;
		void Update( double DeltaTime );

		~NPhysics( ) noexcept = default;

	private:
		const Entity *m_pPlayer{ };
		ChunkManager *m_pChunkManager{ };
		NTransform	 *m_pTransform{ };
		NRigidBody	 *m_pRigidBody{ };
		vec3		  normal{ 0.0f };

		static constexpr inline vec3  CMaxVelocity{ 5.0f };
		static constexpr inline vec3  CGravity{ 0.0f, -6.8f, 0.0f };
		static constexpr inline float CPhysicsUpdateRate = 1.0f / 120;
		static constexpr inline float CHorizontalDrag	 = 8.0f;
		static constexpr inline float CVerticalDrag		 = 1.0f;

		void ProcessCollision( float &minTime, const vec3 &velocity ) noexcept;
		NODISCARD float SweptCollision( const vec3 &velocity, const vec3 &min, const vec3 &max, const vec3 &minI, const vec3 &maxI, float minTime, float x, float y, float z ) noexcept;

		bool DoRaycast( const vec3 &Origin, const vec3 &NormalDirection, float MaxDistance, bool Draw, const vec3 &BlockCorner, const vec3 &Step, RaycastResult *Out ) const noexcept;
	};

} // namespace Nocturn

#endif