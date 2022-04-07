#include "application/window/window.h"

namespace Nocturn
{
	uint32_t Window::m_width = 1280;

	uint32_t Window::m_height = 720;

	void Window::resizeCallback( GLFWwindow *window, const int width, const int height )
	{
		m_width	 = width;
		m_height = height;
		glViewport( 0, 0, width, height );
	}

	Window::Window( ) noexcept :
		m_pTitle( "Minecraft @ Cucorianu E. Adelin" ), m_pWindow( nullptr )
	{}

	Window::Window( const char *title, const uint32_t width, const uint32_t height ) :
		m_pTitle( title ), m_pWindow( nullptr )
	{}

	void Window::setCursorMode( CursorMode cursorMode ) const
	{
		int glfwCursorMode =
			cursorMode == CursorMode::Locked ? GLFW_CURSOR_DISABLED :
			cursorMode == CursorMode::Normal ? GLFW_CURSOR_NORMAL :
			cursorMode == CursorMode::Hidden ? GLFW_CURSOR_HIDDEN :
												 GLFW_CURSOR_HIDDEN;
		glfwSetInputMode( m_pWindow, GLFW_CURSOR, glfwCursorMode );
	}

	void Window::setTitle( const char *title ) const
	{
		glfwSetWindowTitle( m_pWindow, title );
	}

	void Window::setSize( const uint32_t width, const uint32_t height ) const
	{
		m_width	 = width;
		m_height = height;
	}

	void Window::setWindowSize( const uint32_t width, const uint32_t height ) const
	{
		glfwSetWindowSize( m_pWindow, width, height );
	}

	float Window::getAspectRatio( ) const
	{
		return static_cast< float >( m_width ) / static_cast< float >( m_height );
	}

	void Window::init( )
	{
		glfwInit( );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	}

	void Window::create( )
	{
		GLFWmonitor *monitor = glfwGetPrimaryMonitor( );
		if( !monitor )
		{
			std::cerr << "Error: Failed to get primary monitor\n";
			return;
		}

		m_pWindow = glfwCreateWindow( m_width, m_height, m_pTitle, /* monitor */ nullptr, nullptr );
		if( nullptr == m_pWindow )
		{
			std::cerr << "Error: Failed to create window.\n";
			return;
		}

		makeContextCurrent( );

		if( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) )
		{
			std::cerr << "ERROR: Failed to initialize GLAD." << std::endl;
			glfwTerminate( );
			return;
		}

		glfwSetFramebufferSizeCallback( m_pWindow, resizeCallback );
		glfwSetKeyCallback( m_pWindow, Keyboard::keyCallback );
		glfwSetCursorPosCallback( m_pWindow, Mouse::cursorPosCallback );
		glfwSetScrollCallback( m_pWindow, Mouse::mouseWheelCallback );

		setCursorMode( CursorMode::Locked );
	}

	void Window::makeContextCurrent( )
	{
		glfwMakeContextCurrent( m_pWindow );
	}

	void Window::pollInput( )
	{
		glfwPollEvents( );
	}

	void Window::swapBuffers( )
	{
		glfwSwapBuffers( m_pWindow );
	}

	bool Window::shouldClose( )
	{
		return glfwWindowShouldClose( m_pWindow );
	}

	void Window::close( )
	{
		glfwSetWindowShouldClose( m_pWindow, true );
	}

	void Window::destroy( )
	{
		glfwTerminate( );
	}

	void Window::free( )
	{
		glfwTerminate( );
	}
} // namespace Nocturn