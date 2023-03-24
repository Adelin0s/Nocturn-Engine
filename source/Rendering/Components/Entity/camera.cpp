#include "rendering/components/entity/camera.h"

#include "application/application.h"
#include "core/physics/enviroment.h"

namespace Nocturn
{
	NCamera::NCamera( const NTransform& Transform ) noexcept
	:
		CameraTransform( &Transform )
	{}

	RStatus NCamera::ToggleTransform( const NTransform* NewTransform )
	{
		if( NewTransform == nullptr )
		{
			LogError( "Invalid Transform nullptr!" );
			return RInvalidArguments;
		}

		CameraTransform = NewTransform;

		return RSucces;
	}

	mat4 NCamera::GetViewMatrix( ) const noexcept
	{
		assert( CameraTransform );

		return glm::lookAt( CameraTransform->Position, CameraTransform->Position + CameraTransform->Forward, CameraTransform->Up );
	}

	mat4 NCamera::GetProjectionMatrix( ) const noexcept
	{
		assert( CameraTransform );

		return glm::perspective( glm::radians( Config::CFov ), Application::GetWindow( ).GetAspectRatio( ), Config::CNear, Config::CFar );
	}

} // namespace Nocturn