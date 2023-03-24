#pragma once

#include "Core/core.h"

namespace Nocturn
{
	// Forward declares
	class NActor;

	/** This class will be the base class for all components. */
	class NActorComponent
	{
	public:
		/** Default ActorComponent constructor. */
		NActorComponent() noexcept;

		/** Get the  NActor  that 'Owns' this component. */
		NODISCARD NActor* GetActor() const noexcept;

		/** Initializes the component. */
		virtual void Initialize() = 0;

		/** Function called when the component is activated. It is called when it is attached to the current Actor.
		 *@param OwnedActor Pointer to the Actor that owned the component.
		 */
		virtual void OnComponenentActivated(NActor* OwnedActor) = 0;

		/** Function called when the component is deactivated.*/
		virtual void OnComponenentDeactivated() = 0;

		/** Method that is called every frame. */
		virtual void Update(double DeltaTime) = 0;

		virtual ~NActorComponent() noexcept = default;

	protected:
		/** A reference to the actor that owns the component. This allows the component to access information about the actor as well as communicate with other components of the actor. */
		NActor* Owner;

		/** Flag indicating whether the component is active or not. */
		bool bIsActive:1;

		/** TODO: Not implemented yet. Unique id assigned to the component. */
		static uint32 ComponentId;
	};
} // namespace Nocturn