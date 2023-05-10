#pragma once

#include <array>
#include <set>

#include "Core/core.h"

#include "Context/Components/ActorComponent.h"
#include "Context/GameFramework/Controller.h"

namespace Nocturn
{
	// Forward declares
	class NTransformComponent;
	class NWorld;

	constexpr uint8 CMaxActorComponents = 16;

	const auto ComponentsComparator = [](const NActorComponent* ComponentA, const NActorComponent* ComponentB) noexcept -> bool
	{
		return typeid(*ComponentA).hash_code() < typeid(*ComponentB).hash_code();
	};

	namespace Concepts
	{
		template<typename TCurrentClass>
		concept DerivedFromActor = requires(TCurrentClass CurrentClass)
		{
			std::is_base_of_v<NActorComponent, TCurrentClass>;
		};
	}

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
		friend void NController::HandleKeyboardInput() const noexcept;

		/** Base constructor. */
		NActor() noexcept;

		/** The initialization method of the actor. */
		virtual void Initialize(const SharedPtr< NWorld >& WorldIn) = 0;

		/** Method that is called every frame. */
		virtual void Update(double DeltaTime) = 0;

		/** Default destructor. */
		virtual ~NActor() noexcept = default;

		/** Add movement input by a specific direction and an Intensity.
		 *@param Direction Direction of the movement.
		 *@param Intensity Intensity of the movement.
		 */
		void AddMovementInput(const vec3& Direction, float Intensity = 1.0f) const noexcept;

		/** Set Velocity of the Actor. */
		void SetVelocity(const vec3& InVelocity) noexcept
		{
			Velocity = InVelocity;
		}

		/** Get the current RootComponent. */
		NODISCARD NTransformComponent* GetTransformComponent() const noexcept;

		/** Get the Velocity of the Actor. */
		NODISCARD vec3& GetVelocity() noexcept;

		/** Get the current World where the actor is. */
		NODISCARD NWorld* GetWorld() const noexcept;

		/** Add a new Component to the current Actor. */
		void AddComponent(NActorComponent* Component);

		/** Remove a Component to the current Actor. */
		void RemoveComponent(NActorComponent* Component);

		/** Get the ComponentTag from the current Actor.
		 * @param ComponentTag The name of the component that actor owns
		 * @return Component of the Actor for succes and nullptr in case of failure
		 */
		template<Concepts::DerivedFromActor TActorComponent>
		NODISCARD TActorComponent* GetComponentByTag(const std::string& ComponentTag) const noexcept
		{
			for (auto Component : Components)
			{
				if (Component->ComponentHasTag(ComponentTag))
				{
					return dynamic_cast<TActorComponent*>(Component);
				}
			}

			return nullptr;
		}

	protected:
		/** Set movement type of the Actor. */
		virtual void SetMovementMode(EMovementMode MovementMode);

	protected:
		/** Array with the all components that are attached. */
		std::set< NActorComponent*, decltype(ComponentsComparator) > Components;

		/** Root component that keeps the transform of the current Actor.
		 *@todo Maybe it could be modified as a pointer to a new RootbaseComponent, to be able to accept more types of RootComponent.
		 */
		SharedPtr< NTransformComponent > TransformComponent;

		/** The current World where the actor is alive. */
		SharedPtr< NWorld > World;

		/** Current Velocity of the Actor.
		 * @todo Change with a new RigidBodyComponent
		 */
		vec3 Velocity;

		/** This is the base actor speed that is multiplied in MovementMode. */
		static constexpr float CBaseActorVelocity = 3.5f;
	};
} // namespace Nocturn
