#include "Context/GameFramework/Character.h"

#include "Context/Components/BoxComponent.h"
#include "Context/GameFramework/Actor.h"
#include "Context/Components/CameraComponent.h"
#include "Context/Components/TransformComponent.h"

namespace Nocturn
{
	NCharacter::NCharacter() noexcept
	:
		NActor()
	{}

	void NCharacter::Initialize(const SharedPtr< NWorld >& WorldIn)
	{
		NActor::Initialize(WorldIn);

		CameraComponent = std::make_shared< NCameraComponent >();
		AssertInfo(CameraComponent != nullptr, "Failed to alloc memory for CameraComponent!");
		CameraComponent->OnComponenentActivated(this);

		//BoxComponent = std::make_shared< NBoxComponent >();
		//AssertInfo(BoxComponent != nullptr, "Failed to alloc memory for CameraComponent!");
		//BoxComponent->OnComponenentActivated(this);
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

	SharedPtr<NCameraComponent> NCharacter::GetCameraComponent() const noexcept
	{
		return CameraComponent;
	}
} 
