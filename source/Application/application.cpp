#include "application/application.h"
#include "application/window/window.h"

#include "Core/Scene/scene.h"

#include "GUI/HUD.h"

#include "rendering/world/chunk/chunkmanager.h"
#include "rendering/world/world.h"

namespace Nocturn::Application
{
	std::unique_ptr< NWindow > Window;
	std::unique_ptr< NScene >  Scene;
	std::unique_ptr< NHUD >	   HUD;

	void Init( )
	{
		Window = std::make_unique< NWindow >( );
		Window->Init( );

		// Deprecated from now
		//Core::Init( );
		Scene = std::make_unique< NScene >( );

		HUD = std::make_unique< NHUD >( );
	}

	void Run( )
	{
		Window->Create( );

		double DeltaTime = 0.0;
		double LastFrame = 0.0;

		Scene->Init( );

		HUD->Initialize( );

		while( !Window->ShouldClose( ) )
		{
			if( Keyboard::keyWentDown( GLFW_KEY_ESCAPE ) )
				Window->Close( );

			const double CurrentFrame = glfwGetTime( );
			DeltaTime				  = CurrentFrame - LastFrame;
			LastFrame				  = CurrentFrame;

			glEnable( GL_DEPTH_TEST );

			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			Scene->Update( DeltaTime );

			HUD->Update( );

			Window->SwapBuffers( );
			Window->PollInput( );
		}
	}

	void Free( )
	{
		// Deprecated from now
		//Core::Free( );
		Window->Free( );
	}

	NWindow& GetWindow( )
	{
		return *Window.get( );
	}
} // namespace Nocturn::Application
