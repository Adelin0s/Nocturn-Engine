/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 07-09-2021 19:31:44                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 15-02-2022 20:34:33                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef CAMERA_H
#define CAMERA_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include "application/config/config.hpp"
#include "application/input/keyboard.h"
#include "application/window/window.h"

#include "application/input/mouse.h"

#include "core/types/typedef.hpp"

namespace Nocturn
{
	enum class CameraDirection
	{
		Forward,
		Backward,
		Left,
		Right,
		Up,
		Down
	};

	class Camera
	{
	public:
		Camera( ) noexcept;
		Camera( const Camera & ) = delete;
		Camera( Camera && )		 = delete;

		Camera &operator=( const Camera & ) = delete;
		Camera &operator=( Camera && ) = delete;

		void Update( const double dt );

		void updateCameraPosition( const CameraDirection movement, const double deltaTime ) noexcept;
		void updateCameraPosition( const glm::vec3 &cameraPosition ) noexcept;
		void updateCameraDirection( const double dx, const double dy ) noexcept;
		void updateCameraVectors( ) noexcept;

		NODISCARD glm::mat4 getViewMatrix( ) const noexcept;
		NODISCARD glm::mat4 getProjectionMatrix( ) const noexcept;
		NODISCARD vec3		getCameraPosition( ) const noexcept;

		~Camera( ) noexcept = default;

	private:
		double m_pitch;
		double m_yaw;
		double m_speed;
		double m_sensitivity;

		glm::vec3 m_cameraPosition;
		glm::vec3 m_cameraFront;
		glm::vec3 m_cameraUp;
		glm::vec3 m_cameraRight;

		void CheckForKeyInput( const double dt ) noexcept;
	};
} // namespace Nocturn
#endif
