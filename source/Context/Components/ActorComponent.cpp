#include "Context/Components/ActorComponent.h"

#include "Context/GameFramework/Actor.h"

namespace Nocturn
{
	NActorComponent::NActorComponent() noexcept
	:		Owner(nullptr)
	,		ComponentTag("None")
	,		bIsActive(false)
	{
	}

	void NActorComponent::OnComponenentActivated(NActor* OwnedActor)
	{
		Owner = OwnedActor;

		bIsActive = true;
	}

	void NActorComponent::OnComponenentDeactivated()
	{
		Owner = nullptr;
		ComponentTag = "None";
		bIsActive = false;
	}

	void NActorComponent::Update(double DeltaTime)
	{
	}

	bool NActorComponent::InitializeBaseComponent(const std::string& TagName) noexcept
	{
		if (!TagName.ends_with("Component") || TagName.empty())
		{
			LogError("Failed to Initialize TagName of the ActorComponent!");
			return false;
		}

		ComponentTag = TagName;
		return true;
	}

	NActor* NActorComponent::GetActor() const noexcept
	{
		return Owner;
	}

	bool NActorComponent::ComponentHasTag(const std::string& ComponentTagIn) const noexcept
	{
		return ComponentTag == ComponentTagIn;
	}

	void NActorComponent::SetComponentTag(const char* ComponentTagIn)
	{
		if (ComponentTagIn == nullptr)
		{
			LogError("Failed to SetComponentTag because ComponentTagIn is nullptr!");
			return;
		}

		ComponentTag = ComponentTagIn;
	}

} // namespace Nocturn
