#pragma once

#include "Context/GameFramework/Actor.h"

namespace Nocturn
{
	// Forward declares
	class NRigidbody;
	class NCameraComponent;

	class NCharacter : public NActor
	{
	public:
		/** Default constructor */
		NCharacter() noexcept = default;

		/** Cant copy. */
		NCharacter(const NCharacter& Character) = delete;
		NCharacter& operator=(const NCharacter& Character) = delete;

		/** Cant move. */
		NCharacter(NCharacter&& Character) = delete;
		NCharacter& operator=(NCharacter&& Character) = delete;

		/** The initialization method of the Character. */
		void Initialize() override;

		/** Method that is called every frame. */
		void Update(double DeltaTime) override;

		void SetMovementMode(EMovementMode MovementMode) override;

		/** Get current camera component from the Character. */
		NODISCARD NCameraComponent* GetCameraComponent() const noexcept;

		NODISCARD NTransformComponent* GetRootComponent() const noexcept;

		void Jump();

		void StopJump();

		/** Default destructor */
		~NCharacter() noexcept override = default;

	private:
		/** Default camera component from Character. */
		std::unique_ptr<NCameraComponent> CameraComponent;

		/** Root component that keeps the transform of the current Actor. */
		std::unique_ptr< NTransformComponent > TransformComponent;

		/** TODO: Not implemented yet. */
		std::unique_ptr<NRigidbody> Rigidbody;
	};
} // namespace Nocturn
