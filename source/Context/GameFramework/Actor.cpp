#include "Context/GameFramework/Actor.h"

#include "Context/Components/TransformComponent.h"

namespace Nocturn
{
	NActor::NActor() noexcept
	:
		Velocity(0.0f)
	{}

	void NActor::Initialize(const SharedPtr< NWorld >& WorldIn)
	{
		World = WorldIn;

		TransformComponent = std::make_shared<NTransformComponent>();
		AssertInfo(TransformComponent != nullptr, "Failed to alloc memory for TransformComponent!");

		TransformComponent->OnComponenentActivated(this);
	}

	void NActor::Update(const double DeltaTime)
	{
		TransformComponent->Update(DeltaTime);

		for (const auto Component : Components)
		{
			Component->Update(DeltaTime);
		}
	}

	void NActor::AddMovementInput(const vec3& Direction, const float Intensity) const noexcept
	{
		AssertInfo(TransformComponent != nullptr, "Invalid nullptr TransformComponent!");

		TransformComponent->SetLocation(Direction * Intensity);
	}

	NTransformComponent* NActor::GetTransformComponent() const noexcept
	{
		AssertInfo(TransformComponent != nullptr, "Failed TransformComponent nullptr member!");

		return TransformComponent.get();
	}

	vec3& NActor::GetVelocity() noexcept
	{
		return Velocity;
	}

	NWorld* NActor::GetWorld() const noexcept
	{
		return World.get();
	}

	void NActor::SetMovementMode(const EMovementMode MovementMode)
	{
		AssertInfo(TransformComponent != nullptr, "Invalid nullptr TransformComponent!");

		const auto& Transform = TransformComponent->GetTransform();
		float LocalVelocity = CBaseActorVelocity;

		if (MovementMode == EMovementMode::MoveFast)
		{
			std::cout << "Move fast\n!";
			LocalVelocity += 35.0f;
		}

		switch (MovementMode)
		{
		case EMovementMode::MoveForward:
			Velocity.x = Transform.Forward.x * LocalVelocity;
			Velocity.z = Transform.Forward.z * LocalVelocity;
			break;
		case EMovementMode::MoveBackward:
			Velocity.x = -Transform.Forward.x * LocalVelocity;
			Velocity.z = -Transform.Forward.z * LocalVelocity;
			break;
		case EMovementMode::MoveLeft:
			Velocity.x = -Transform.Right.x * LocalVelocity;
			Velocity.z = -Transform.Right.z * LocalVelocity;
			break;
		case EMovementMode::MoveRight:
			Velocity.x = Transform.Right.x * LocalVelocity;
			Velocity.z = Transform.Right.z * LocalVelocity;
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
} // namespace Nocturn
