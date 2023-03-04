#include "rendering/components/entity/camera.h"

#include "application/application.h"
#include "core/physics/enviroment.h"

namespace Nocturn
{
	NCamera::NCamera( const Transform &transform ) noexcept
		:		m_pTransform( &transform )
	{ }

	mat4 NCamera::GetViewMatrix( ) const noexcept
	{
		assert( m_pTransform );

		return glm::lookAt( m_pTransform->position, m_pTransform->position + m_pTransform->forward, m_pTransform->up);
	}

	mat4 NCamera::GetProjectionMatrix( ) const noexcept
	{
		assert( m_pTransform );

		return glm::perspective( glm::radians( Config::CFov ), Application::GetWindow( ).GetAspectRatio( ), Config::CNear, Config::CFar );
	}

} // namespace Nocturn