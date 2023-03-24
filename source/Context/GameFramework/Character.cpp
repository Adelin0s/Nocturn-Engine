#include "Context/GameFramework/Character.h"

#include "Context/Components/CameraComponent.h"

namespace Nocturn
{
	void NCharacter::Initialize()
	{
		NActor::Initialize();

		CameraComponent = std::make_unique<NCameraComponent>();
		AssertInfo(CameraComponent != nullptr, "Failed to alloc memory for CameraComponent!");

		CameraComponent->OnComponenentActivated(this);
	}

	void NCharacter::Jump()
	{
	}

	void NCharacter::StopJump()
	{
	}

	void NCharacter::Update(const double DeltaTime)
	{
		NActor::Update(DeltaTime);

		CameraComponent->Update(DeltaTime);
	}

	void NCharacter::SetMovementMode(const EMovementMode MovementMode)
	{
		NActor::SetMovementMode(MovementMode);
	}

	NCameraComponent* NCharacter::GetCameraComponent() const noexcept
	{
		return CameraComponent.get();
	}

	NTransformComponent* NCharacter::GetRootComponent() const noexcept
	{
		return TransformComponent.get();
	}
} 
