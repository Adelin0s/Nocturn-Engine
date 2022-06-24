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

	enum class CollisionFace : uint8
	{
		None = 0
		, Top
		, Bottom
		, Front
		, Back
		, Left
		, Right
	};

	struct CollisionResult
	{
		vec3 overlap;
		CollisionFace face;
	};

	class Physics
	{
	public:
		static inline vec3	gravity{ 0.0f, 20.0f, 0.0f };
		static inline vec3	terminalVelocity = { 50.0f, 50.0f, 50.0f };
		static inline float updateRate = 1.0f / 60.0f;

		Physics( ) noexcept = delete;

		Physics( const Entity &player, ChunkManager& chunkManager, Transform &transform, RigidBody &rigidBody );

		// cant copy
		Physics( const Physics &rigidBody ) = delete;
		Physics &operator=( const Physics &rigidBody ) = delete;

		// cant move
		Physics &operator=( Physics &&rigidBody ) = delete;
		Physics( Physics &&rigidBody ) = delete;

		void Update( double dt );

		~Physics( ) noexcept = default;

	private:
		const Entity *m_pPlayer{ };
		ChunkManager *m_pChunkManager{ };
		Transform	 *m_pTransform{ };
		RigidBody	 *m_pRigidBody{ };

		void ProcessCollision( ) const noexcept;
		static bool CheckColliding( const Transform& transform1, const AABB& box1, const Transform& transform2, const AABB &box2 ) noexcept;
		NODISCARD CollisionResult GetCollisionFace( const Transform &transform1, const AABB &box1, const Transform &transform2, const AABB &box2 ) const noexcept;
	};

} // namespace Nocturn

#endif