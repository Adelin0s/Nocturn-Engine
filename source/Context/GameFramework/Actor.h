#pragma once

#include <array>
#include <set>

#include "Core/core.h"

#include "Context/Components/ActorComponent.h"
#include "Context/GameFramework/Controller.h"

namespace Nocturn
{
	constexpr uint8 CMaxActorComponents = 16;

	const auto ComponentsComparator = [](const NActorComponent* ComponentA, const NActorComponent* ComponentB) noexcept -> bool
	{
		return typeid(*ComponentA).hash_code() < typeid(*ComponentB).hash_code();
	};

	// forward declares
	class NTransformComponent;

	enum class EMovementMode : uint8
	{
		MoveForward = 0
		,	MoveBackward
		,	MoveLeft
		,	MoveRight
		,	MoveFast
		,	ClimbUp
		, ClimbDown
	};

	class NActor
	{
	public:
		/** Default constructor */
		NActor() = default;

		/** The initialization method of the actor. */
		virtual void Initialize();

		/** Method that is called every frame. */
		virtual void Update(double DeltaTime);

		/**  */
		void AddMovementInput(const vec3& Direction, float Intensity = 1.0f) const noexcept;

		/** Set Velocity of the Actor. */
		void SetVelocity(const vec3& InVelocity) noexcept
		{
			Velocity = InVelocity;
		}

		/** Get the Velocity of the Actor. */
		NODISCARD vec3& GetVelocity() noexcept
		{
			return Velocity;
		}

		/** Add a new Component to the current Actor. */
		void AddComponent(NActorComponent* Component);

		/** Remove a Component to the current Actor. */
		void RemoveComponent(NActorComponent* Component);

		/** Default destructor. */
		virtual ~NActor() noexcept = default;

		friend void NController::HandleKeyboardInput() const noexcept;

	protected:
		/** Set movement type of the Actor. */
		virtual void SetMovementMode(EMovementMode MovementMode);

	protected:
		/** Array with the all components that are attached. */
		std::set< NActorComponent*, decltype(ComponentsComparator) > Components;

		// TODO: Must to exclude the TransformComponent from here!

		/** Current Velocity of the Actor. */
		vec3 Velocity;

		/** This is the base actor speed that is multiplied in MovementMode. */
		static constexpr float CBaseActorVelocity = 1.5f;
	};
} // namespace Nocturn
