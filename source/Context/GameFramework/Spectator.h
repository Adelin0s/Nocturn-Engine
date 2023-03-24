#pragma once

#include "Context/GameFramework/Actor.h"

namespace Nocturn
{
	class NSpectator : public NActor
	{
	public:
		NSpectator() noexcept = default;

		/** Cant copy */
		NSpectator(const NSpectator& Spectator) = delete;
		NSpectator& operator=(const NSpectator& Spectator) = delete;

		/** Cant move */
		NSpectator(NSpectator&& Spectator) = delete;
		NSpectator& operator=(NSpectator&& Spectator) = delete;

		void Initialize() override;

		void Update(double DeltaTime) override;

		void SetMovementMode(EMovementMode MovementMode) override;

		~NSpectator() noexcept override = default;

		friend void NController::HandleKeyboardInput() const noexcept;
	};
	
} // namespace Nocturn
