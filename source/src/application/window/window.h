/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 30-09-2021 16:19:53                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 07-12-2021 19:41:17                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "application/input/keyboard.h"
#include "application/input/mouse.h"
#include "application/scene/scene.h"
#include "core/platform/platform.h"

namespace Nocturn
{
	enum class CursorMode : uint8_t
	{
		Locked,
		Normal,
		Hidden
	};

	class Window
	{
	public:
		Window( ) noexcept;
		Window( const char *title, const uint32_t width, const uint32_t height );
		Window( const Window & ) = delete;
		Window( Window && )		 = delete;

		Window &operator=( const Window & ) = delete;
		Window &operator=( Window && ) = delete;

		void			setCursorMode( CursorMode cursorMode ) const;
		void			setTitle( const char *title ) const;
		void			setSize( const uint32_t width, const uint32_t height ) const;
		void			setWindowSize( const uint32_t width, const uint32_t height ) const;
		NODISCARD float getAspectRatio( ) const;

		void init( );
		void create( );
		void close( );
		void destroy( );

		void makeContextCurrent( );
		void pollInput( );
		void swapBuffers( );
		bool shouldClose( );

		static void resizeCallback( GLFWwindow *window, const int width, const int height );
		static void free( );

		~Window( ) noexcept = default;

	public:
		static uint32_t m_width;
		static uint32_t m_height;
		const char	   *m_pTitle;
		GLFWwindow	   *m_pWindow;
	};
} // namespace Nocturn

#endif