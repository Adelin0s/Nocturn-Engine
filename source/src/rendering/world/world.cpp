#include "rendering/world/world.h"

#include "rendering/components/entity/spectator.h"
#include "rendering/renderer/renderer.h"
#include "rendering/renderer/style.h"

namespace Nocturn
{
	static Transform playerTransform;
	static Transform spectatorTransform;
	static RigidBody rigidbody;

	static std::unique_ptr< Camera >  camera;
	static std::unique_ptr< Entity >  player;
	static std::unique_ptr< Physics > physics;
	static std::unique_ptr< Spectator > spectator;

	const Style style1 = { Colors::deepBlue, 0.25f };
	const Style style2 = { Colors::offWhite, 0.05f };

	void World::Init( )
	{
		m_taskSystem   = std::make_unique< TaskSystem >( 1 );
		m_skyboxRender = std::make_unique< SkyboxRendering >( );
		m_chunkManager = std::make_unique< ChunkManager >( *m_taskSystem );

		playerTransform.position = vec3( 3.0f, 60.0f, 12.0f );
		playerTransform.rotation = vec3( 0.0f );

		spectatorTransform.position = vec3( 3.0f, 40.0f, 12.0f );
		spectatorTransform.rotation = vec3( 0.0f );

		camera	  = std::make_unique< Camera >( spectatorTransform );
		player	  = std::make_unique< Player >( playerTransform, rigidbody );
		spectator = std::make_unique< Spectator >( spectatorTransform );
		physics	  = std::make_unique< Physics >( *player, *m_chunkManager, playerTransform, rigidbody );

		Renderer::Init( *camera );

		m_chunkRender.init( );
	}

	void World::Update( const double dt )
	{
		const auto currentPosition = static_cast< ivec3 >( spectatorTransform.position );

		m_chunkManager->Update( currentPosition );
		m_chunkManager->Render( *camera, m_chunkRender );
		m_skyboxRender->render( *camera );

		// update forward, right and up vectors
		TransformSystem::Update( &playerTransform );
		TransformSystem::Update( &spectatorTransform );

		physics->Update( dt );
		player->Update( dt );
		spectator->Update( dt );

		Renderer::Render( );
	}

	void World::Free( )
	{
	}
} // namespace Nocturn