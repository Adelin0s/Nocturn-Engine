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

		/** Function called when the component is activated. It is called when it is attached to the current Actor.
		 *@param OwnedActor Pointer to the Actor that owned the component.
		 */
		virtual void OnComponenentActivated(NActor* OwnedActor) = 0;

		/** Function called when the component is deactivated.*/
		virtual void OnComponenentDeactivated() = 0;

		/** Method that is called every frame. */
		virtual void Update(double DeltaTime) = 0;

		virtual ~NActorComponent() noexcept = default;

		/** Get the Actor that Owns the current component. */
		NODISCARD NActor* GetActor() const noexcept;

		void SetComponentTag(const char* ComponentTagIn);

		NODISCARD bool ComponentHasTag(const std::string& ComponentTagIn) const noexcept;

	protected:
		/** Initializes the component with the appropiate TagName.
		 * @param TagName The appopiate name of the tag as <ComponentName>Component
		 * @return State of the initialization
		 */
		NODISCARD bool InitializeBaseComponent(const std::string& TagName) noexcept;

	protected:
		/** A reference to the actor that owns the component. This allows the component to access information about the actor as well as communicate with other components of the actor. */
		NActor* Owner;

		/** Tag that can be used for grouping and categorizing. */
		std::string ComponentTag;

		/** Flag indicating whether the component is active or not. */
		bool bIsActive:1;
	};
} // namespace Nocturn