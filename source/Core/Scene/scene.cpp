#include "scene.h"

#include "Context/Components/BoxComponent.h"
#include "Context/GameFramework/Character.h"
#include "Context/GameFramework/Controller.h"
#include "rendering/renderer/renderer.h"
#include "rendering/world/world.h"

namespace Nocturn
{
	void NScene::Init()
	{
		World = std::make_shared< NWorld >();
		AssertInfo(World != nullptr, "Failed to allocate memory for World!");

		Character = std::make_shared< NCharacter >();
		Character->Initialize(World);

		// TODO: Move to inner scope
		BoxComponent = std::make_shared< NBoxComponent >();
		Character->AddComponent(BoxComponent.get());

		Controller = std::make_shared< NController >();
		Controller->SetActor(Character.get());

		World->AttachController(Controller);
		World->AttachMainCharacter(Character);
		const auto Status = World->Initialize(Controller, Character);
		if( RSucces == Status )
		{
			Log("World init succesfully!");
		}
	}

	void NScene::Update(const double DeltaTime)
	{
		Controller->Update();

		Character->Update(DeltaTime);

		World->Update(DeltaTime);
	}

	void NScene::Free()
	{
		World->Free();
	}

} // namespace Nocturn
