#include "scene.h"

#include "core/components/transform.h"

#include "rendering/renderer/renderer.h"
#include "rendering/world/world.h"

namespace Nocturn::Scene
{
	Transform transform;

	std::unique_ptr< Camera > camera;
	std::unique_ptr< World >  world;
	std::unique_ptr< Player > player;

	const Style style1 = { Colors::deepBlue, 0.25f };
	const Style style2 = { Colors::offWhite, 0.05f };

	void Init( )
	{
		TransformSystem::Init( transform );
		transform.position = vec3( 0.0f, 60.0f, 2.0f );
		transform.rotation = vec3( 0.0f );

		camera = std::make_unique< Camera >( transform );
		player = std::make_unique< Player >( transform );
		world  = std::make_unique< World >( transform, *camera );

		Renderer::Init( *camera );
	}

	void Update( const double dt )
	{
		world->Update( dt );

		player->Update( dt );

		// update forward, right and up vectors
		TransformSystem::Update( );

		Renderer::DrawBox( {0, 40, 0}, vec3{1.0}, style2 );

		Renderer::Render( );
	}

	void Free( )
	{
		world->Free( );
	}

} // namespace Nocturn::Scene
