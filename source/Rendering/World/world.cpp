#include "rendering/world/world.h"

#include "Context/GameFramework/Character.h"
#include "Context/Components/CameraComponent.h"

#include "application/input/keyboard.h"
#include "rendering/components/entity/spectator.h"
#include "rendering/renderer/renderer.h"
#include "rendering/renderer/style.h"

#include "Core/core.h"

namespace Nocturn
{
	static NTransform PlayerTransform;
	static NTransform SpectatorTransform;
	static NRigidBody rigidbody;

	static std::unique_ptr< NCamera >	Camera;
	static std::unique_ptr< NFrustum >	CameraFrustum;
	static std::unique_ptr< Entity >	Player;
	static std::unique_ptr< NPhysics >	physics;
	static std::unique_ptr< Spectator > spectator;

	const Style style1 = { Colors::deepBlue, 0.25f };
	const Style style2 = { Colors::offWhite, 0.05f };

	RStatus NWorld::Init( )
	{
		NCharacter Character;
		Character.Initialize();

		NCameraComponent CameraComponent;

		Character.AddComponent(&CameraComponent);

		m_taskSystem   = std::make_unique< TaskSystem >(1);
		m_skyboxRender = std::make_unique< Render::SkyboxRenderer >( );
		m_chunkManager = std::make_unique< ChunkManager >(*m_taskSystem); // wtf is here?

		PlayerTransform.Position = vec3(3.0f, 60.0f, 12.0f);
		PlayerTransform.Rotation = vec3(0.0f);

		SpectatorTransform.Position = vec3(3.0f, 40.0f, 12.0f);
		SpectatorTransform.Rotation = vec3(0.0f);

		m_skyboxRender->Init();
		Camera		  = std::make_unique< NCamera >(SpectatorTransform);
		CameraFrustum = std::make_unique< NFrustum >( );
		Player		  = std::make_unique< NPlayer >(PlayerTransform, rigidbody);
		spectator	  = std::make_unique< Spectator >(SpectatorTransform);
		physics		  = std::make_unique< NPhysics >(*Player, *m_chunkManager, PlayerTransform, rigidbody);

		Render::Init( *Camera );

		m_chunkRender.Init();

		return RSucces;
	}

	void NWorld::Update(const double DeltaTime)
	{
		const auto currentPosition = static_cast< ivec3 >(SpectatorTransform.Position);

		m_chunkManager->Update( currentPosition );

		m_skyboxRender->Render( *Camera );

		// update forward, right and up vectors
		TransformSystem::Update(&PlayerTransform);
		TransformSystem::Update(&SpectatorTransform);

		const auto projectionMatrix = Camera->GetProjectionMatrix( );
		const auto viewMatrix		= Camera->GetViewMatrix( );

		CameraFrustum->Update(projectionMatrix * viewMatrix);
		physics->Update(DeltaTime);

		const auto position = vec3{ PlayerTransform.Position.x, PlayerTransform.Position.y, PlayerTransform.Position.z };
		const auto raycastResult = physics->RaycastStatic( position, PlayerTransform.Forward + vec3( 0.1f, 0.1f, 0.1f ), 8.0f, true );

		if( Keyboard::keyWentDown(GLFW_KEY_0) )
		{
			const auto ZPosition = vec3{ position.x, position.y, position.z + 5.0f };
			m_chunkManager->SetBlock(BlockId::Stone, ZPosition);
		}

		Player->Update(DeltaTime);
		spectator->Update(DeltaTime);

		Render::Render();

		m_chunkManager->Render(*Camera, *CameraFrustum, m_chunkRender);
	}

	void NWorld::Free( )
	{
	}
} // namespace Nocturn