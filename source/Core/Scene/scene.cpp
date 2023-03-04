#include "scene.h"

#include "core/components/transform.h"

#include "rendering/renderer/renderer.h"
#include "rendering/world/world.h"

namespace Nocturn
{
	void NScene::Init( )
	{
		const auto Status = World.Init( );
		if (RSucces == Status)
		{
			Log("World init succesfully!");
		}
	}

	void NScene::Update( const double DeltaTime )
	{
		World.Update( DeltaTime );
	}

	void NScene::Free( )
	{
		World.Free( );
	}

} // namespace Nocturn::Scene
