#include "application/application.h"
#include "application/window/window.h"

#include "core/scene.h"

#include "rendering/renderer/skyboxrenderer.h"
#include "rendering/world/chunk/chunkmanager.h"
#include "rendering/world/world.h"

#include <chrono>

namespace Nocturn::Application
{
	std::unique_ptr< Window > window;

	void Init( )
	{
		window = std::make_unique< Window >( );
		window->init( );
	}

	void Run( )
	{
		window->create( );

		double lastX = 640.0;
		double lastY = 360.0;

		double dt		 = 0.0;
		double lastFrame = 0.0;

		glEnable( GL_DEPTH_TEST );

		Scene::Init( );

		while( !window->shouldClose( ) )
		{
			if( Keyboard::keyWentDown( GLFW_KEY_ESCAPE ) )
				window->close( );

			const double currentFrame = glfwGetTime( );
			dt						  = currentFrame - lastFrame;
			lastFrame				  = currentFrame;

			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			Scene::Update( dt );

			window->swapBuffers( );
			window->pollInput( );
		}
	}

	void Free( )
	{
		Scene::Free( );
		window->free( );
	}

	Window &getWindow( )
	{
		return *window.get( );
	}
} // namespace Nocturn::Application
