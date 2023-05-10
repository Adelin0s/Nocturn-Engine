#include "application/window/window.h"

namespace Nocturn
{
	uint32_t NWindow::Width = 1280;

	uint32_t NWindow::Height = 720;

	void NWindow::ResizeCallback(GLFWwindow* window, const int width, const int height)
	{
		Width  = width;
		Height = height;
		glViewport(0, 0, width, height);
	}

	NWindow::NWindow() noexcept :
		m_pTitle("Nocturn @ Cucorianu E. Adelin"), m_pWindow(nullptr)
	{}

	NWindow::NWindow(const char* Title, const uint32_t Width, const uint32_t Height) :
		m_pTitle(Title), m_pWindow(nullptr)
	{
		NWindow::Width	= Width;
		NWindow::Height = Height;
	}

	void NWindow::SetCursorMode(ECursorMode CursorMode) const
	{
		const int glfwCursorMode =
			CursorMode == ECursorMode::Locked ? GLFW_CURSOR_DISABLED :
			CursorMode == ECursorMode::Normal ? GLFW_CURSOR_NORMAL :
			CursorMode == ECursorMode::Hidden ? GLFW_CURSOR_HIDDEN :
												GLFW_CURSOR_HIDDEN;
		glfwSetInputMode(m_pWindow, GLFW_CURSOR, glfwCursorMode);
	}

	void NWindow::SetTitle(const char* title) const
	{
		glfwSetWindowTitle(m_pWindow, title);
	}

	void NWindow::SetSize(const uint32_t width, const uint32_t height) const
	{
		Width  = width;
		Height = height;
	}

	void NWindow::SetWindowSize(const uint32_t width, const uint32_t height) const
	{
		glfwSetWindowSize(m_pWindow, width, height);
	}

	float NWindow::GetAspectRatio() const
	{
		return static_cast< float >(Width) / static_cast< float >(Height);
	}

	void NWindow::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void NWindow::Create()
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		if( !monitor )
		{
			////LogError("Failed to get primary monitor!");
			return;
		}

		m_pWindow = glfwCreateWindow(Width, Height, m_pTitle, /* monitor */ nullptr, nullptr);
		if( nullptr == m_pWindow )
		{
			////LogError("Failed to create window!");
			return;
		}

		MakeContextCurrent();

		if( !gladLoadGLLoader(( GLADloadproc )glfwGetProcAddress) )
		{
			////LogError("Failed to initialize GLAD!");
			glfwTerminate();
			return;
		}

		glfwSetFramebufferSizeCallback(m_pWindow, ResizeCallback);
		glfwSetKeyCallback(m_pWindow, Keyboard::keyCallback);
		glfwSetCursorPosCallback(m_pWindow, Mouse::CursorPosCallback);
		glfwSetScrollCallback(m_pWindow, Mouse::MouseWheelCallback);

		SetCursorMode(ECursorMode::Locked);
	}

	void NWindow::MakeContextCurrent()
	{
		glfwMakeContextCurrent(m_pWindow);
	}

	void NWindow::PollInput()
	{
		glfwPollEvents();
	}

	void NWindow::SwapBuffers()
	{
		glfwSwapBuffers(m_pWindow);
	}

	bool NWindow::ShouldClose()
	{
		return glfwWindowShouldClose(m_pWindow);
	}

	void NWindow::Close()
	{
		glfwSetWindowShouldClose(m_pWindow, true);
	}

	void NWindow::Destroy()
	{
		glfwTerminate();
	}

	GLFWwindow* NWindow::GetWindow() const
	{
		return m_pWindow;
	}

	void NWindow::Free()
	{
		glfwTerminate();
	}
} // namespace Nocturn