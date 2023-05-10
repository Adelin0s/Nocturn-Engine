#include "Context/GameFramework/Spectator.h"

#include "Context/GameFramework/Actor.h"

namespace Nocturn
{
	void NSpectator::Initialize(const SharedPtr<NWorld>& WorldIn)
	{
		NActor::Initialize(WorldIn);
	}

	void NSpectator::Update(const double DeltaTime)
	{
		NActor::Update(DeltaTime);
	}

	void NSpectator::SetMovementMode(const EMovementMode MovementMode)
	{
		NActor::SetMovementMode(MovementMode);
	}
}
