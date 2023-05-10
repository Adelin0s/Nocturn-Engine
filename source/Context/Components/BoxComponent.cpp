#include "Context/Components/BoxComponent.h"

#include "TransformComponent.h"
#include "application/application.h"
#include "application/config/config.hpp"
#include "Context/GameFramework/Actor.h"

namespace Nocturn
{
	NBoxComponent::NBoxComponent() noexcept
	:
		Size(CDefaultCharacterSize)
	{
	}

	void NBoxComponent::OnComponenentActivated(NActor* OwnedActor)
	{
		NActorComponent::OnComponenentActivated(OwnedActor);

		const auto Result = NActorComponent::InitializeBaseComponent("BoxComponent");
		if (Result == false)
		{
			LogError("Failed to Initialize BoxComponent!");
			return;
		}
	}

	void NBoxComponent::OnComponenentDeactivated()
	{
		NActorComponent::OnComponenentDeactivated();
	}

	void NBoxComponent::Update(const double DeltaTime)
	{
		NActorComponent::Update(DeltaTime);
	}

	void NBoxComponent::SetSize(const vec3& SizeIn) noexcept
	{
		Size = SizeIn;
	}

	vec3 NBoxComponent::GetMin() const noexcept
	{
		AssertInfo(Owner != nullptr, "Failed to GetMin because Owner is nullptr!");

		const auto Transform = Owner->GetTransformComponent();

		return (Transform->GetLocation() - 0.5f) - Size * 0.5f;
	}

	vec3 NBoxComponent::GetMax() const noexcept
	{
		AssertInfo(Owner != nullptr, "Failed to GetMin because Owner is nullptr!");

		const auto Transform = Owner->GetTransformComponent();

		return (Transform->GetLocation() - 0.5f) + Size * 0.5f;
	}
}
