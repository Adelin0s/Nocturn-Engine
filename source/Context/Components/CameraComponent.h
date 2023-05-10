#pragma once

#include "Context/Components/ActorComponent.h"	

namespace Nocturn
{
	class NCameraComponent : public NActorComponent
	{
	public:
		NCameraComponent() noexcept = default;

		/** Cant copy. */
		NCameraComponent(const NCameraComponent& CameraComponent) = delete;
		NCameraComponent& operator=(const NCameraComponent& CameraComponet) = delete;

		/** Cant move. */
		NCameraComponent(NCameraComponent&& CameraComponent) = delete;
		NCameraComponent& operator=(NCameraComponent&& CameraComponet) = delete;

		void OnComponenentActivated(NActor* OwnedActor) override;

		void OnComponenentDeactivated() override;

		/** Method that is called every frame. */
		void Update(double DeltaTime) override;

		/** Get ViewMatrix from current Camera.
		 * @return ViewMatrix and in case of failure return mat4(0.0f)
		 */
		NODISCARD mat4 GetViewMatrix() const noexcept;

		/** Get ProjectionMatrix from current Camera.
		 * @return ViewMatrix and in case of failure return mat4(0.0f)
		 */
		NODISCARD mat4 GetProjectionMatrix() const noexcept;

		~NCameraComponent() noexcept override = default;
	};
}
