#include "scene.h"

#include "core/components/transform.h"

#include "rendering/renderer/renderer.h"
#include "rendering/world/world.h"

namespace Nocturn::Scene
{
	static World world;

	void Init( )
	{
		world.Init(  );
	}

	void Update( const double dt )
	{
		world.Update( dt );
	}

	void Free( )
	{
		world.Free( );
	}

} // namespace Nocturn::Scene
