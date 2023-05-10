// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin                                                                                      
//   @ Create Time: 05-06-2022 6:34 PM                                                                                                                                                
//   @ Contact: cucorianu.adelin@protonmail.com                                                                                                                          
//   @ Modified time: 23-08-2022 10:34 PM                                                                                                                                    
//   @ Description:                                                                                                                                                                                
// =====================================================================

#pragma once

#include <memory>

#include "Core/Core.h"
#include "Core/Async/Task.h"
#include "Core/Physics/Physics.h"
#include "Rendering/Renderer/ChunkRenderer.h"

namespace Nocturn
{
	//Forward declares
	class NController;

	class NWorldLight
	{
	public:
	    glm::vec3 Position;
	    glm::vec3 Color;
	    float Intensity;

	    NWorldLight(const glm::vec3& position, const glm::vec3& color, float intensity)
		:
			Position(position), Color(color), Intensity(intensity)
		{}
	};

	class NWorld
	{
	public:
		/** Default constructor. */
		NWorld() noexcept;

		/** Cant copy. */
		NWorld(const NWorld& World) = delete;
		NWorld(NWorld&& World) = delete;

		/** Cant move. */
		NWorld& operator=(const NWorld& World) = delete;
		NWorld& operator=(NWorld&& World) = delete;

		/** Initialize world stuff. */
		RStatus Initialize(const SharedPtr< NController >& ControllerIn, const SharedPtr< NCharacter >& MainCharacterIn);

		/** Update all components from the World. */
		void Update(double DeltaTime);

		/** Attach the main character to the World instance. */
		void AttachMainCharacter(const SharedPtr< NCharacter >& MainCharacterIn) noexcept;

		/** Attach the controller to World instance. */
		void AttachController(const SharedPtr< NController >& ControllerIn) noexcept;

		/** Get a shared pointer to the ChunkManager. */
		NODISCARD SharedPtr< NChunkManager > GetChunkManager() const noexcept;

		/** Get the main Character. */
		NODISCARD NCharacter* GetMainCharacter() const noexcept;

		/** Get the main Character. */
		NODISCARD NController* GetController() const noexcept;

		/** Get the main Character. */
		NODISCARD SharedPtr< NCameraComponent > GetMainCameraComponent() const noexcept;

		/** Free all ressources from the World. */
		void Free();

		/** Default destructor. */
		~NWorld() noexcept = default;

	private:
		/** Pointer to the MainCharacter of the world. Mainly, this is the character controlled by the Controller.
		 * @todo Change with NActor* for more flow control. Main character can be a Spectator too for example
		 */
		SharedPtr< NCharacter > MainCharacter;

		/** Pointer to the Controller that acts as a owner of the Character. */
		SharedPtr< NController > Controller;

		/** Main camera component. This component contain a pointer to actor's camera that is currently activated. */
		SharedPtr< NCameraComponent > MainCameraComponent;

		/** Shared pointer from master renderer where we can manage all of things about the renderer. */
		SharedPtr< NMasterRenderer > MasterRenderer;

		/** Shared pointer from ChunkManager where we can manage all of things about the chunks. */
		SharedPtr< NChunkManager > ChunkManager;

		/** Async task system. */
		UniquePtr< NTaskSystem > TaskSystem;

		/** The physics engine that is attached to the World. */
		UniquePtr< NPhysics > Physics;

		/** World light */
		NWorldLight WorldLight;
	};
} // namespace Nocturn