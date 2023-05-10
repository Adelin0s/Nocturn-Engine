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

	void NController::SetActor(NActor* NewActor)
	{
		AssertInfo(NewActor != nullptr, "Invalid nullptr OwnedActor member!");

		OwnedActor = NewActor;

		UpdateOwnedActorFlag();
	}

	bool NController::HasValidCharacter() const
	{
		if (OwnedActor == nullptr)
		{
			return false;
		}

		const auto Result = dynamic_cast< NCharacter* >(OwnedActor);
		if (Result == nullptr)
		{
			return false;
		}
		return true;
	}

	bool NController::HasValidSpectator() const noexcept
	{
		if (OwnedActor == nullptr)
		{
			return false;
		}

		const auto Result = dynamic_cast<NSpectator*>(OwnedActor);
		if (Result == nullptr)
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

		if( dx != 0.0 || dy != 0.0 )
		{
			auto& Rotation = OwnedActor->GetTransformComponent()->GetRotation();

			dx *= Mouse::CMouseSensitivity;
			dy *= Mouse::CMouseSensitivity;

			Rotation.x += static_cast< float >(dx);
			Rotation.y += static_cast< float >(dy);

			if (Rotation.y > 89.0f)
				Rotation.y = 89.0f;
			if (Rotation.y < -89.0f)
				Rotation.y = -89.0f;
		}
	}

	void NController::HandleKeyboardInput() const noexcept
	{
		AssertInfo(OwnedActor != nullptr, "Invalid OwnedActor nullptr member!");

		if( bHasCharacter )
		{
			const auto Character = reinterpret_cast< NCharacter* >(OwnedActor);
			if( Keyboard::key(GLFW_KEY_SPACE) )
			{
				Character->Jump();
			}
		}

		if( bHasSpectator )
		{
			const auto Spectator = reinterpret_cast< NSpectator* >(OwnedActor);
			if( Keyboard::key(GLFW_KEY_Q) )
			{
				Spectator->SetMovementMode(EMovementMode::ClimbDown);
			}
			if( Keyboard::key(GLFW_KEY_E) )
			{
				Spectator->SetMovementMode(EMovementMode::ClimbUp);
			}
		}

		if( Keyboard::key(GLFW_KEY_LEFT_SHIFT) )
		{
			OwnedActor->SetMovementMode(EMovementMode::MoveFast);
		}
		if( Keyboard::key(GLFW_KEY_UP) || Keyboard::key(GLFW_KEY_W) )
		{
			OwnedActor->SetMovementMode(EMovementMode::MoveForward);
		}
		if( Keyboard::key(GLFW_KEY_DOWN) || Keyboard::key(GLFW_KEY_S) )
		{
			OwnedActor->SetMovementMode(EMovementMode::MoveBackward);
		}
		if( Keyboard::key(GLFW_KEY_LEFT) || Keyboard::key(GLFW_KEY_A) )
		{
			OwnedActor->SetMovementMode(EMovementMode::MoveLeft);
		}
		if( Keyboard::key(GLFW_KEY_RIGHT) || Keyboard::key(GLFW_KEY_D) )
		{
			OwnedActor->SetMovementMode(EMovementMode::MoveRight);
		}
	}
}
