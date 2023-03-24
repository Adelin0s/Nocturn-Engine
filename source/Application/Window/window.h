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

#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "application/input/keyboard.h"
#include "application/input/mouse.h"

#include "Core/core.h"

namespace Nocturn
{
	enum class ECursorMode : uint8_t
	{
		Locked,
		Normal,
		Hidden
	};

	class NWindow
	{
	public:
		NWindow( ) noexcept;
		NWindow( const char *Title, uint32_t Width, uint32_t Height );
		NWindow( const NWindow & ) = delete;
		NWindow( NWindow && ) = delete;

		NWindow &operator=( const NWindow & ) = delete;
		NWindow &operator=( NWindow && ) = delete;

		void SetCursorMode( ECursorMode CursorMode ) const;
		void SetTitle( const char *Title ) const;
		void SetSize( uint32_t Width, uint32_t Height ) const;
		void SetWindowSize( uint32_t Width, uint32_t Height ) const;
		NODISCARD float GetAspectRatio( ) const;

		void Init( );
		void Create( );
		void Close( );
		void Destroy( );

		GLFWwindow* GetWindow() const;
		void MakeContextCurrent( );
		void PollInput( );
		void SwapBuffers( );
		bool ShouldClose( );

		static void ResizeCallback( GLFWwindow *Window, int Width, int Height );
		static void Free( );

		~NWindow( ) noexcept = default;

	public:
		static uint32_t Width;
		static uint32_t Height;
		const char *m_pTitle;
		GLFWwindow *m_pWindow;
	};
} // namespace Nocturn

#endif