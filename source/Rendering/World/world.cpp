#include "rendering/world/world.h"

#include "application/input/keyboard.h"
#include "rendering/components/entity/spectator.h"
#include "rendering/renderer/renderer.h"
#include "rendering/renderer/style.h"

#include "Core/core.h"

namespace Nocturn
{
	static Transform playerTransform;
	static Transform spectatorTransform;
	static RigidBody rigidbody;

	static std::unique_ptr< NCamera >	camera;
	static std::unique_ptr< Frustum >	cameraFrustum;
	static std::unique_ptr< Entity >	player;
	static std::unique_ptr< Physics >	physics;
	static std::unique_ptr< Spectator > spectator;

	const Style style1 = { Colors::deepBlue, 0.25f };
	const Style style2 = { Colors::offWhite, 0.05f };

	RStatus NWorld::Init( )
	{
		m_taskSystem   = std::make_unique< TaskSystem >(1);
		m_skyboxRender = std::make_unique< Render::SkyboxRenderer >( );
		m_chunkManager = std::make_unique< ChunkManager >(*m_taskSystem); // wtf is here?

		playerTransform.position = vec3(3.0f, 60.0f, 12.0f);
		playerTransform.rotation = vec3(0.0f);

		spectatorTransform.position = vec3(3.0f, 40.0f, 12.0f);
		spectatorTransform.rotation = vec3(0.0f);

		m_skyboxRender->Init();
		camera		  = std::make_unique< NCamera >(spectatorTransform);
		cameraFrustum = std::make_unique< Frustum >( );
		player		  = std::make_unique< Player >(playerTransform, rigidbody);
		spectator	  = std::make_unique< Spectator >(spectatorTransform);
		physics		  = std::make_unique< Physics >(*player, *m_chunkManager, playerTransform, rigidbody);

		//Render::Init( *camera );

		m_chunkRender.Init();

		return RSucces;
	}

	void NWorld::Update(const double DeltaTime)
	{
		const auto currentPosition = static_cast< ivec3 >(spectatorTransform.position);

		m_chunkManager->Update( currentPosition );

		m_skyboxRender->Render( *camera );

		// update forward, right and up vectors
		TransformSystem::Update(&playerTransform);
		TransformSystem::Update(&spectatorTransform);

		const auto projectionMatrix = camera->GetProjectionMatrix( );
		const auto viewMatrix		= camera->GetViewMatrix( );

		cameraFrustum->Update(projectionMatrix * viewMatrix);
		physics->Update(DeltaTime);

		const auto position = vec3{ spectatorTransform.position.x - 0.5f, spectatorTransform.position.y, spectatorTransform.position.z - 0.5f };
		//const auto raycastResult = physics->RaycastStatic( position, spectatorTransform.forward /*+ vec3( 0.0f, 0.3f, 0.4f )*/, 5.0f, true );

		if( Keyboard::keyWentDown(GLFW_KEY_0) )
		{
			const auto ZPosition = vec3{ position.x, position.y, position.z + 5.0f };
			m_chunkManager->SetBlock(BlockId::Stone, ZPosition);
		}

		player->Update(DeltaTime);
		spectator->Update(DeltaTime);

		// Render::Render();

		m_chunkManager->Render(*camera, *cameraFrustum, m_chunkRender);
	}

	void NWorld::Free( )
	{
	}
} // namespace Nocturn