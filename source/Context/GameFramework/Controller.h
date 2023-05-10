#pragma once

#include "Context/GameFramework/IController.h"

namespace Nocturn
{
	// Forward declares
	class NActor;

	class NController : public INController
	{
	public:
		friend class NActor;
		friend class NSpectator;

		/** Default constructor. */
		NController() noexcept;

		explicit NController(NActor* Actor);

		/** Cant copy. */
		NController(const NController& Controller) = delete;
		NController& operator=(const NController& Controller) = delete;

		/** Cant move. */
		NController(NController&& Controller) = delete;
		NController& operator=(NController&& Controller) = delete;

		/** Initialize controller. */
		void Initialize() override;

		/** Set a new actor. */
		void SetActor(NActor* NewActor);

		/** Get the current owner actor. */
		NODISCARD NActor* GetActor() const noexcept;

		/** Get if we have a owned actor as a pointer to a Character. */
		NODISCARD bool HasCharacter() const noexcept;

		/** Get if we have a owned actor as a pointer to a Spectator. */
		NODISCARD bool HasSpectator() const noexcept;

		/** Method that is called every frame. */
		void Update() override;

		/** Default destructor. */
		~NController() noexcept override = default;

	private:
		/** Handle mouse input. */
		void HandleMouseInput() const noexcept;

		/** Handle keyboard input. */
		void HandleKeyboardInput() const noexcept;

		/** Get if we have a owned actor as a pointer to a Character.
		 * @warning This may be slow in context of frame-to-frame. Use instead the approapite HasCharacter getter!
		 */
		NODISCARD bool HasValidCharacter() const;

		/** Get if we have a owned actor as a pointer to a Spectator.
		 * @warning This may be slow in context of frame-to-frame. Use instead the approapite HasSpectator getter!
		 */
		NODISCARD bool HasValidSpectator() const noexcept;

		/** Update OwnedActor flag. */
		void UpdateOwnedActorFlag() noexcept;

	private:
		/** The actor that the controller controls. */
		NActor* OwnedActor;

		/** True if have a Character owned by Controller */
		bool bHasCharacter:1;

		/** True if have a Character owned by Controller */
		bool bHasSpectator:1;
	};
}