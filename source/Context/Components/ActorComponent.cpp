#include "Context/Components/ActorComponent.h"

namespace Nocturn
{
	uint32 NActorComponent::ComponentId = 0;

	NActorComponent::NActorComponent() noexcept
	:		Owner(nullptr)
	,		bIsActive(false)
	{
	}

	NActor* NActorComponent::GetActor() const noexcept
	{
		return Owner;
	}

	void NActorComponent::OnComponenentActivated(NActor* OwnedActor)
	{
		Owner = OwnedActor;

		bIsActive = true;
	}

	void NActorComponent::OnComponenentDeactivated()
	{
		Owner = nullptr;

		bIsActive = false;
	}
} // namespace Nocturn
