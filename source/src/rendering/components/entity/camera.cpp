#include "rendering/components/entity/camera.h"

#include "application/application.h"
#include "core/physics/enviroment.h"

namespace Nocturn
{
	Camera::Camera( const Transform &transform ) noexcept
		:		m_pTransform( &transform )
	{ }

	mat4 Camera::getViewMatrix( ) const noexcept
	{
		assert( m_pTransform );

		return glm::lookAt( m_pTransform->position, m_pTransform->position + m_pTransform->forward, m_pTransform->up);
	}

	mat4 Camera::getProjectionMatrix( ) const noexcept
	{
		assert( m_pTransform );

		return glm::perspective( glm::radians( Config::CFov ), Application::getWindow( ).getAspectRatio( ), Config::CNear, Config::CFar );
	}

} // namespace Nocturn