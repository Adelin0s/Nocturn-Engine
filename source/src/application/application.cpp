#include "application/application.h"

#include "application/scene/scene.h"
#include "application/window/window.h"

#include "rendering/renderer/skyboxrenderer.h"
#include "rendering/world/chunk/chunkmanager.h"
#include "rendering/world/world.h"

#include <chrono>

namespace Nocturn::Application
{
	std::unique_ptr< Window > window;
	std::unique_ptr< World >  world;
	// std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	void init( )
	{
		// begin = std::chrono::steady_clock::now();
		window = std::make_unique< Window >( );
		world  = std::make_unique< World >( );
		window->init( );
	}

	void run( )
	{
		window->create( );

		float lastX = 640.0f;
		float lastY = 360.0f;

		float dt		= 0.0f;
		float lastFrame = 0.0f;

		glEnable( GL_DEPTH_TEST );

		world->Init( );

		while( !window->shouldClose( ) )
		{
			if( Keyboard::keyWentDown( GLFW_KEY_ESCAPE ) )
				window->close( );

			float currentFrame = glfwGetTime( );
			dt				   = currentFrame - lastFrame;
			lastFrame		   = currentFrame;

			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			world->Update( dt );

			window->swapBuffers( );
			window->pollInput( );
		}
		world->Free( );
	}

	void free( )
	{
		window->free( );
	}

	Window &getWindow( )
	{
		return *window.get( );
	}
} // namespace Nocturn::Application
