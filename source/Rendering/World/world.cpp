#include "Rendering/World/World.h"
#include "Application/Input/Keyboard.h"
#include "Context/Components/BoxComponent.h"
#include "Context/Components/CameraComponent.h"
#include "Context/Components/TransformComponent.h"
#include "Context/GameFramework/Character.h"
#include "Core/Core.h"
#include "Application/Config/Config.hpp"
#include "Core/Physics/rigidbody.h"
#include "Rendering/Renderer/MasterRenderer.h"
#include "Rendering/Renderer/Renderer.h"
#include "Rendering/Renderer/Skyboxrenderer.h"
#include "Rendering/Renderer/Style.h"

namespace Nocturn
{
	static UniquePtr< NFrustum > CameraFrustum;
	//static UniquePtr< NPhysics > Physics;

	const Style style1 = { Colors::deepBlue, 0.25f };
	const Style style2 = { Colors::offWhite, 0.05f };

	NWorld::NWorld() noexcept
	:
			MainCharacter(nullptr),
			Controller(nullptr),
			WorldLight(glm::vec3(10.0f, 15.0f, 10.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.8f)
	{}

	RStatus NWorld::Initialize(const SharedPtr< NController >& ControllerIn, const SharedPtr< NCharacter >& MainCharacterIn)
	{
		AssertInfo(MainCharacter != nullptr, "MainCameraComponent nullptr!");

		MasterRenderer = std::make_shared< NMasterRenderer >();

		MainCameraComponent = MainCharacter->GetCameraComponent();

		// RigidBody = std::make_shared<NRigidBody>();
		TaskSystem   = std::make_unique< NTaskSystem >(1);
		ChunkManager = std::make_unique< NChunkManager >(*TaskSystem); // wtf is here?

		auto &Position = MainCharacter->GetTransformComponent()->GetLocation();
		Position = Config::CDefaultPlayerPosition;

		//CameraFrustum = std::make_unique< NFrustum >();
		Physics = std::make_unique< NPhysics >(MainCharacter.get(), *ChunkManager);

		MasterRenderer->Initialize(this);

		Render::Init(MainCameraComponent.get());

		Controller = ControllerIn;
		MainCharacter = MainCharacterIn;

		return RSucces;
	}

	void NWorld::Update(const double DeltaTime)
	{
		ChunkManager->Update(DeltaTime);

		Physics->Update(DeltaTime);

		const auto& Position = MainCharacter->GetTransformComponent()->GetLocation();
		const auto& Forward = MainCharacter->GetTransformComponent()->GetTransform().Forward;

		//Render::DrawBox(vec3(Position.x + 0.5f, Position.y, Position.z + 0.5f), vec3(1.0f), style1);
		const auto RaycastResult = Physics->RaycastStatic(Position, Forward + vec3(0.1f, 0.1f, 0.1f), 8.0f, true);

		//const auto ChunkRenderer = MasterRenderer->GetRendererComponentByTag< NChunkRenderer >("ChunkRenderer");

		MasterRenderer->Render(MainCameraComponent.get());
		//Render::Render();
	}

	void NWorld::Free()
	{
	}

	void NWorld::AttachMainCharacter(const SharedPtr< NCharacter >& MainCharacterIn) noexcept
	{
		if(MainCharacterIn == nullptr)
		{
			LogError("Invalid nullptr MainCharacterIn param!");
			return;
		}

		MainCharacter = MainCharacterIn;
	}

	void NWorld::AttachController(const SharedPtr< NController >& ControllerIn) noexcept
	{
		if(ControllerIn == nullptr)
		{
			LogError("Invalid nullptr ControllerIn param!");
			return;
		}

		Controller = ControllerIn;
	}

	SharedPtr<NChunkManager> NWorld::GetChunkManager() const noexcept
	{
		return ChunkManager;
	}

	NCharacter* NWorld::GetMainCharacter() const noexcept
	{
		return MainCharacter.get();
	}

	NController* NWorld::GetController() const noexcept
	{
		return Controller.get();
	}

	SharedPtr<NCameraComponent> NWorld::GetMainCameraComponent() const noexcept
	{
		return MainCameraComponent;
	}
} // namespace Nocturn