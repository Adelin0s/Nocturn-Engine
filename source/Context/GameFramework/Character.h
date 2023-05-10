#pragma once

#include "Context/GameFramework/Actor.h"

//#include "Core/Physics/rigidbody.h"

namespace Nocturn
{
	// Forward declares
	//class NRigidbody;
	class NCameraComponent;

	class NCharacter: public NActor
	{
	public:
		/** Default constructor */
		NCharacter() noexcept;

		/** Cant copy. */
		NCharacter(const NCharacter& Character) = delete;
		NCharacter& operator=(const NCharacter& Character) = delete;

		/** Cant move. */
		NCharacter(NCharacter&& Character) = delete;
		NCharacter& operator=(NCharacter&& Character) = delete;

		/** The initialization method of the Character. */
		void Initialize(const SharedPtr< NWorld >& WorldIn) override;

		/** Method that is called every frame. */
		void Update(double DeltaTime) override;

		void SetMovementMode(EMovementMode MovementMode) override;

		/** Get current CameraComponent from the current Character. */
		NODISCARD SharedPtr< NCameraComponent > GetCameraComponent() const noexcept;

		void Jump();

		void StopJump();

		/** Default destructor */
		~NCharacter() noexcept override = default;

	private:
		/** Default CameraComponent from the current Character. */
		SharedPtr< NCameraComponent > CameraComponent;

		/** TODO: Not implemented yet. */
		//std::unique_ptr< NRigidBody > RigidBody;
	};
} // namespace Nocturn
