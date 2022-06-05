#include "rendering/data/camera.h"

#include "application/application.h"
#include "core/physics/enviroment.h"

namespace Nocturn
{
	Camera::Camera( ) noexcept
		:
		m_cameraPosition( glm::vec3( 0.0f, 260.0f, 2.0f ) ), m_cameraFront( glm::vec3( 0.0f, 0.0f, -1.0f ) ), m_cameraUp( glm::vec3( 0.0f, 1.0f, 0.0f ) ), m_yaw( 30.0f ), m_pitch( -20.0f ), m_sensitivity( 0.1f ), m_speed( 10.0f )
	{
		updateCameraVectors( );
	}

	void Camera::processInput( const double dt )
	{
		double dx = Mouse::getDx( );
		double dy = Mouse::getDy( );
		if( dx || dy )
		{
			updateCameraDirection( dx, dy );
		}
		if( Keyboard::key( GLFW_KEY_W ) )
			updateCameraPosition( CameraDirection::Forward, dt );
		if( Keyboard::key( GLFW_KEY_S ) )
			updateCameraPosition( CameraDirection::Backward, dt );
		if( Keyboard::key( GLFW_KEY_A ) )
			updateCameraPosition( CameraDirection::Left, dt );
		if( Keyboard::key( GLFW_KEY_D ) )
			updateCameraPosition( CameraDirection::Right, dt );
		if( Keyboard::key( GLFW_KEY_E ) )
			updateCameraPosition( CameraDirection::Up, dt );
		if( Keyboard::key( GLFW_KEY_Q ) )
			updateCameraPosition( CameraDirection::Down, dt );
	}

	void Camera::updateCameraDirection( double dx, double dy ) noexcept
	{
		dx *= m_sensitivity;
		dy *= m_sensitivity;

		m_yaw += dx;
		m_pitch += dy;

		if( m_pitch > 89.0f )
			m_pitch = 89.0f;
		if( m_pitch < -89.0f )
			m_pitch = -89.0f;

		updateCameraVectors( );
	}

	void Camera::updateCameraVectors( ) noexcept
	{
		glm::vec3 direction;
		direction.x = cos( glm::radians( m_yaw ) ) * cos( glm::radians( m_pitch ) );
		direction.y = sin( glm::radians( m_pitch ) );
		direction.z = sin( glm::radians( m_yaw ) ) * cos( glm::radians( m_pitch ) );

		m_cameraFront = glm::normalize( direction );
		m_cameraRight = glm::normalize( glm::cross( m_cameraFront, core::Environment::worldUp ) );
		m_cameraUp	  = glm::normalize( glm::cross( m_cameraRight, m_cameraFront ) );
	}

	void Camera::updateCameraPosition( const CameraDirection movement, const double deltaTime ) noexcept
	{
		float speed = 2.5f;
		if( Keyboard::key( GLFW_KEY_LEFT_SHIFT ) )
			speed = 10.0f;
		const float velocity = m_speed * float( deltaTime ) * speed;

		if( movement == CameraDirection::Forward )
		{
			m_cameraPosition += m_cameraFront * velocity;
		}
		if( movement == CameraDirection::Backward )
		{
			m_cameraPosition -= m_cameraFront * velocity;
		}
		if( movement == CameraDirection::Left )
		{
			m_cameraPosition -= m_cameraRight * velocity;
		}
		if( movement == CameraDirection::Right )
		{
			m_cameraPosition += m_cameraRight * velocity;
		}
		if( movement == CameraDirection::Down )
		{
			m_cameraPosition.y -= 1.0f * velocity;
		}
		if( movement == CameraDirection::Up )
		{
			m_cameraPosition.y += 1.0f * velocity;
		}
	}

	void Camera::updateCameraPosition( const glm::vec3 &cameraPosition ) noexcept
	{
		m_cameraPosition = cameraPosition;
	}

	glm::mat4 Camera::getViewMatrix( ) const noexcept
	{
		return glm::lookAt( m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp );
	}

	glm::mat4 Camera::getProjectionMatrix( ) const noexcept
	{
		return glm::perspective( glm::radians( Config::fov ), Application::getWindow( ).getAspectRatio( ), Config::near, Config::far );
	}

	glm::vec3 Camera::getCameraPosition( ) const noexcept
	{
		return m_cameraPosition;
	}
} // namespace Nocturn