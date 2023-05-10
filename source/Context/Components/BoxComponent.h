#pragma once

#include "Context/Components/ActorComponent.h"
#include "Core/core.h"

namespace Nocturn
{
	static constexpr vec3 CDefaultCharacterSize{0.55, 1.8, 0.55};

	class NBoxComponent : public NActorComponent
	{
	public:
		NBoxComponent() noexcept;

		/** Cant copy. */
		NBoxComponent(const NBoxComponent& BoxComponent) = delete;
		NBoxComponent& operator=(const NBoxComponent& BoxComponent) = delete;

		/** Cant move. */
		NBoxComponent(NBoxComponent&& BoxComponent) = delete;
		NBoxComponent& operator=(NBoxComponent&& BoxComponent) = delete;

		void OnComponenentActivated(NActor* OwnedActor) override;

		void OnComponenentDeactivated() override;

		void Update(double DeltaTime) override;

		void SetSize(const vec3& SizeIn) noexcept;

		/** Get min of AABB. */
		NODISCARD vec3 GetMin() const noexcept;

		/** Get max of AABB. */
		NODISCARD vec3 GetMax() const noexcept;

		~NBoxComponent() noexcept override = default;

	private:
		vec3 Size;
	};
}
