#include "Context/Components/CameraComponent.h"

#include "Application/application.h"
#include "Application/config/config.hpp"
#include "Context/GameFramework/Actor.h"
#include "TransformComponent.h"

namespace Nocturn
{
	void NCameraComponent::OnComponenentActivated(NActor* OwnedActor)
	{
		NActorComponent::OnComponenentActivated(OwnedActor);

		const auto Result = NActorComponent::InitializeBaseComponent("CameraComponent");
		if( Result == false )
		{
			LogError("Failed to Initialize CameraComponent!");
			return;
		}
	}

	void NCameraComponent::OnComponenentDeactivated()
	{
		NActorComponent::OnComponenentDeactivated();
	}

	void NCameraComponent::Update(const double DeltaTime)
	{
		NActorComponent::Update(DeltaTime);
	}

	mat4 NCameraComponent::GetViewMatrix() const noexcept
	{
		const auto TransformComponent = Owner->GetTransformComponent();
		if( TransformComponent == nullptr )
		{
			LogError("Failed to get RootComponent from Owner!");
			return mat4(0.0f);
		}

		const auto& Position  = TransformComponent->GetLocation();
		const auto& Transform = TransformComponent->GetTransform();

		return glm::lookAt(Position, Position + Transform.Forward, Transform.Up);
	}

	mat4 NCameraComponent::GetProjectionMatrix() const noexcept
	{
		const auto TransformComponent = Owner->GetTransformComponent();
		if( TransformComponent == nullptr )
		{
			LogError("Failed to get RootComponent from Owner!");
			return mat4(0.0f);
		}

		return glm::perspective(glm::radians(Config::CFov), Application::GetWindow().GetAspectRatio(), Config::CNear, Config::CFar);
	}
} // namespace Nocturn
