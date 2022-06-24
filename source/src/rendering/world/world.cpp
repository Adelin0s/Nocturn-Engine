#include "rendering/world/world.h"

#include "core/scene.h"
#include "rendering/renderer/renderer.h"
#include "rendering/renderer/style.h"

namespace Nocturn
{
	static Transform transform;
	static RigidBody rigidbody;

	static std::unique_ptr< Camera >  camera;
	static std::unique_ptr< Entity >  player;
	static std::unique_ptr< Physics > physics;

	const Style style1 = { Colors::deepBlue, 0.25f };
	const Style style2 = { Colors::offWhite, 0.05f };

	void World::Init( )
	{
		m_taskSystem   = std::make_unique< TaskSystem >( 1 );
		m_skyboxRender = std::make_unique< SkyboxRendering >( );
		m_chunkManager = std::make_unique< ChunkManager >( *m_taskSystem );

		TransformSystem::Init( transform );
		transform.position = vec3( 0.0f, 60.0f, 2.0f );
		transform.rotation = vec3( 0.0f );

		camera	= std::make_unique< Camera >( transform );
		player	= std::make_unique< Player >( transform, rigidbody );
		physics = std::make_unique< Physics >( *player, *m_chunkManager, transform, rigidbody );

		Renderer::Init( *camera );

		m_chunkRender.init( );
	}

	void World::Update( const double dt )
	{
		const auto currentPosition = static_cast< ivec3 >( transform.position );

		m_chunkManager->Update( currentPosition );
		m_chunkManager->Render( *camera, m_chunkRender );
		m_skyboxRender->render( *camera );

		// update forward, right and up vectors
		TransformSystem::Update( );
		player->Update( dt );
		physics->Update( dt );
	}

	void World::Free( )
	{
	}
} // namespace Nocturn