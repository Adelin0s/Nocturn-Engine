#include "Context/GameFramework/Controller.h"

#include "Spectator.h"
#include "Context/GameFramework/Actor.h"
#include "Context/GameFramework/Character.h"

#include "Application/Input/mouse.h"
#include "Application/Input/keyboard.h"
#include "Context/Components/TransformComponent.h"

namespace Nocturn
{
	NController::NController() noexcept
	:		OwnedActor(nullptr)
	,		bHasCharacter(false)
	,		bHasSpectator(false)
	{}

	NController::NController(NActor* Actor)
	:		OwnedActor(Actor)
	,		bHasCharacter(false)
	,		bHasSpectator(false)
	{
		UpdateOwnedActorFlag();
	}

	void NController::Initialize()
	{

	}

	void NController::ToggleActor(NActor* NewActor)
	{
		AssertInfo(OwnedActor != nullptr, "Invalid nullptr argument!");

		OwnedActor = NewActor;

		UpdateOwnedActorFlag();
	}

	bool NController::HasValidCharacter() const noexcept
	{
		AssertInfo(OwnedActor != nullptr, "Failed to check beacuse OwnedActor is nullptr!");

		const auto Result = dynamic_cast<NCharacter*>(OwnedActor);
		if (Result == nullptr) UNLIKELY
		{
			return false;
		}
		return true;
	}

	bool NController::HasValidSpectator() const noexcept
	{
		AssertInfo(OwnedActor != nullptr, "Failed to check beacuse OwnedActor is nullptr!");

		const auto Result = dynamic_cast<NSpectator*>(OwnedActor);
		if (Result == nullptr) UNLIKELY
		{
			return false;
		}
		return true;
	}

	void NController::UpdateOwnedActorFlag() noexcept
	{
		bHasCharacter = HasValidCharacter();
		bHasSpectator = HasValidSpectator();
	}

	NActor* NController::GetActor() const noexcept
	{
		return OwnedActor;
	}

	bool NController::HasCharacter() const noexcept
	{
		return bHasCharacter;
	}

	bool NController::HasSpectator() const noexcept
	{
		return bHasSpectator;
	}

	void NController::Update()
	{
		HandleMouseInput();
		HandleKeyboardInput();
	}

	void NController::HandleMouseInput() const noexcept
	{
		double dx = Mouse::getDx();
		double dy = Mouse::getDy();

		if (dx > 0.0 || dy > 0.0)
		{
			auto Rotation = OwnedActor->GetRootComponent()->GetRotation();

			dx *= Mouse::CMouseSensitivity;
			dy *= Mouse::CMouseSensitivity;

			Rotation.x += dx;
			Rotation.y += dy;

			if (Rotation.y > 89.0f)
				Rotation.y = 89.0f;
			if (Rotation.y < -89.0f)
				Rotation.y = -89.0f;
		}
	}

	void NController::HandleKeyboardInput() const noexcept
	{
		Assert(OwnedActor != nullptr, "Invalid Actor nullptr!");

		if (bHasCharacter)
		{
			const auto Character = reinterpret_cast<NCharacter*>(OwnedActor);
			if (Keyboard::key(GLFW_KEY_SPACE))
			{
				Character->Jump();
			}
		}

		if (bHasSpectator)
		{
			const auto Spectator = reinterpret_cast<NSpectator*>(OwnedActor);
			if (Keyboard::key(GLFW_KEY_Q))
			{
				Spectator->SetMovementMode(EMovementMode::ClimbDown);
			}
			if (Keyboard::key(GLFW_KEY_E))
			{
				Spectator->SetMovementMode(EMovementMode::ClimbUp);
			}
		}

		if (Keyboard::key(GLFW_KEY_LEFT_SHIFT))
		{
			OwnedActor->SetMovementMode(EMovementMode::MoveFast);
		}
		if (Keyboard::key(GLFW_KEY_UP))
		{
			OwnedActor->SetMovementMode(EMovementMode::MoveForward);
		}
		if (Keyboard::key(GLFW_KEY_DOWN))
		{
			OwnedActor->SetMovementMode(EMovementMode::MoveBackward);
		}
		if (Keyboard::key(GLFW_KEY_LEFT))
		{
			OwnedActor->SetMovementMode(EMovementMode::MoveLeft);
		}
		if (Keyboard::key(GLFW_KEY_RIGHT))
		{
			OwnedActor->SetMovementMode(EMovementMode::MoveRight);
		}
	}
}
