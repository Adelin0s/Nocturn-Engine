#include "Context/Components/CameraComponent.h"

#include "TransformComponent.h"
#include "Context/GameFramework/Actor.h"

namespace Nocturn
{
	NCameraComponent::NCameraComponent(NActor* Actor)
		:
	{
		
	}

	void NCameraComponent::Initialize()
	{
		NActorComponent::Initialize();
	}

	void NCameraComponent::OnComponenentActivated(NActor* OwnedActor)
	{
		NActorComponent::OnComponenentActivated(OwnedActor);
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
		// TODO: Assert here?
		const auto* RootComponent = Owner->GetRootComponent();
		if (RootComponent == nullptr)
		{
			LogError("Failed to get RootComponent from Owner!");
		}

		return glm::lookAt(Transform->Position, Transform->Position + Transform->Forward, Transform->Up);
	}

	mat4 NCameraComponent::GetProjectionMatrix() const noexcept
	{
		return glm::perspective(glm::radians(Config::CFov), Application::GetWindow().GetAspectRatio(), Config::CNear, Config::CFar);
	}
}
