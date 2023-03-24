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

		void Initialize() override;

		void OnComponenentActivated(NActor* OwnedActor) override;

		void OnComponenentDeactivated() override;

		/** Method that is called every frame. */
		void Update(double DeltaTime) override;

		void SetLocation(const vec3& NewLocation) noexcept;

		void SetScale(const vec3& NewScale) noexcept;

		void SetRotation(const vec3& NewRotation) noexcept;

		void SetTransform(const FTransform& NewTransform) noexcept;

		vec3& GetLocation() noexcept;

		vec3& GetScale() noexcept;

		vec3& GetRotation() noexcept;

		FTransform& GetTransform() noexcept;

		~NTransformComponent() noexcept override = default;

	private:
		vec3 Position;
		vec3 Scale;
		vec3 Rotation;

		FTransform Transform;
	};
} // namespace Nocturn
