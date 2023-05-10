#pragma once

#include "Context/Components/ActorComponent.h"

namespace Nocturn
{
	struct FTransform
	{
		vec3 Forward;
		vec3 Up;
		vec3 Right;
		vec3 Direction;
	};

	class NTransformComponent : public NActorComponent
	{
	public:
		NTransformComponent() noexcept = default;

		/** Function called when the component is activated. It is called when it is attached to the current Actor.
		 *@param OwnedActor Pointer to the Actor that owned the component.
		 */
		void OnComponenentActivated(NActor* OwnedActor) override;

		/** Function called when the component is deactivated.*/
		void OnComponenentDeactivated() override;

		/** Method that is called every frame. */
		void Update(double DeltaTime) override;

		/** Set the current non-const Location. */
		void SetLocation(const vec3& NewLocation) noexcept;

		/** Set the current Scale. */
		void SetScale(const vec3& NewScale) noexcept;

		/** Set the current Rotation. */
		void SetRotation(const vec3& NewRotation) noexcept;

		/** Set the current Transform. */
		void SetTransform(const FTransform& NewTransform) noexcept;

		/** Get the current non-const Location. */
		vec3& GetLocation() noexcept;

		/** Get the current non-const Scale. */
		vec3& GetScale() noexcept;

		/** Get the current non-const Rotation. */
		vec3& GetRotation() noexcept;

		/** Get the current non-const Transform. */
		FTransform& GetTransform() noexcept;

		/** Get the current const Location. */
		NODISCARD const vec3& GetLocation() const noexcept;

		/** Get the current const Scale. */
		NODISCARD const vec3& GetScale() const noexcept;

		/** Get the current const Rotation. */
		NODISCARD const vec3& GetRotation() const noexcept;

		/** Get the current const Transform. */
		NODISCARD const FTransform& GetTransform() const noexcept;

		/** Default destructor. */
		~NTransformComponent() noexcept override = default;

	private:
		vec3 Position;
		vec3 Scale;
		vec3 Rotation;

		FTransform Transform;
	};
} // namespace Nocturn
