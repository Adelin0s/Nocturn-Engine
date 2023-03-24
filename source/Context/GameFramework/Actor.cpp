#include "Context/GameFramework/Actor.h"

#include "Context/Components/TransformComponent.h"

namespace Nocturn
{
	void NActor::Initialize()
	{
		RootComponent = std::make_unique<NTransformComponent>();
		AssertInfo(RootComponent != nullptr, "Failed to alloc memory for RootComponent!");

		RootComponent->OnComponenentActivated(this);
	}

	void NActor::Update(const double DeltaTime)
	{
		RootComponent->Update(DeltaTime);

		for (auto *Component : Components)
		{
			Component->Update(DeltaTime);
		}
	}

	void NActor::AddMovementInput(const vec3& Direction, const float Intensity) const noexcept
	{
		RootComponent->SetLocation(Direction * Intensity);
	}

	void NActor::SetMovementMode(const EMovementMode MovementMode)
	{
		const auto& Transform = RootComponent->GetTransform();

		float LocalSpeed = CBaseActorVelocity;

		switch (MovementMode)
		{
		case EMovementMode::MoveForward:
			Velocity.x = Transform.Forward.x * CBaseActorVelocity;
			Velocity.z = Transform.Forward.z * CBaseActorVelocity;
			break;
		case EMovementMode::MoveBackward:
			Velocity.x = -Transform.Forward.x * CBaseActorVelocity;
			Velocity.z = -Transform.Forward.z * CBaseActorVelocity;
			break;
		case EMovementMode::MoveLeft:
			Velocity.x = -Transform.Right.x * CBaseActorVelocity;
			Velocity.z = -Transform.Right.z * CBaseActorVelocity;
			break;
		case EMovementMode::MoveRight:
			Velocity.x = Transform.Right.x * CBaseActorVelocity;
			Velocity.z = Transform.Right.z * CBaseActorVelocity;
			break;
		case EMovementMode::MoveFast:
			LocalSpeed += CBaseActorVelocity + 5.0f;
			break;
		}
	}

	void NActor::AddComponent(NActorComponent* Component)
	{
		if (Component == nullptr)
		{
			LogError("Failed to add component because Component is nullptr!");
			return;
		}

		if (Components.size() == CMaxActorComponents)
		{
			LogError("Failed to add new component because it reached the maximum limit!");
			return;
		}

		Components.insert(Component);

		Component->OnComponenentActivated(this);
	}

	void NActor::RemoveComponent(NActorComponent* Component)
	{
		if (Component == nullptr)
		{
			LogError("Failed to add component because Component is nullptr!");
			return;
		}

		Components.erase(Component);

		Component->OnComponenentDeactivated();
	}

	NTransformComponent* NActor::GetRootComponent() const noexcept
	{
		return RootComponent.get();
	}
} // namespace Nocturn
