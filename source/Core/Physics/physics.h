#ifndef PHYSICS_H
#define PHYSICS_H

//#include "core/physics/rigidbody.h"
#include "core/types/typedef.hpp"
#include "rendering/world/chunk/chunkmanager.h"

namespace Nocturn
{
	// Forward declares
	class NCharacter;
	class NTransformComponent;
	struct NRigidBody;

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
		static inline constexpr vec3 CPlayerBound = { 0.55f, 1.8f, 0.55 };

		NPhysics() noexcept = delete;
		NPhysics(NCharacter* CharacterIn, NChunkManager& chunkManager);

		// cant copy
		NPhysics(const NPhysics& Physics) = delete;
		NPhysics& operator=(const NPhysics& Physics) = delete;

		// cant move
		NPhysics(NPhysics&& Physics) = delete;
		NPhysics& operator=(NPhysics&& Physics) = delete;

		NODISCARD RaycastResult RaycastStatic(const vec3& Origin, const vec3& NormalDirection, float MaxDistance, bool bDraw = false) const noexcept;
		void Update(double DeltaTime);

		~NPhysics() noexcept = default;

	private:
		NCharacter*				Character;
		NChunkManager*			m_pChunkManager{};
		NTransformComponent*	m_pTransform{};
		NRigidBody*				m_pRigidBody{};
		vec3					normal{ 0.0f };

		static constexpr inline vec3  CMaxVelocity{ 5.0f };
		static constexpr inline vec3  CGravity{ 0.0f, -6.8f, 0.0f };
		static constexpr inline float CPhysicsUpdateRate = 1.0f / 120;
		static constexpr inline float CHorizontalDrag = 8.0f;
		static constexpr inline float CVerticalDrag = 1.0f;

		void ProcessCollision(float& MinTime, const vec3& Velocity) noexcept;
		NODISCARD float SweptCollision(const vec3& Velocity, const vec3& MinBound, const vec3& MaxBound, const vec3& MinBoundVelocity, const vec3& MaxBoundVelocity, float MinTime, float x, float y, float z) noexcept;

		bool DoRaycast(const vec3& Origin, const vec3& NormalDirection, float MaxDistance, bool Draw, const vec3& BlockCorner, const vec3& Step, RaycastResult* Out) const noexcept;
	};

} // namespace Nocturn

#endif