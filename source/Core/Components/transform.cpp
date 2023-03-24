#include "transform.h"

#include <iostream>

namespace Nocturn
{
	void TransformSystem::Update( NTransform *Transform )
	{
		assert( Transform );

		Transform->Direction.x = cos( glm::radians( Transform->Rotation.x ) ) * cos( glm::radians( Transform->Rotation.y ) );
		Transform->Direction.y = sin( glm::radians( Transform->Rotation.y ) );
		Transform->Direction.z = sin( glm::radians( Transform->Rotation.x ) ) * cos( glm::radians( Transform->Rotation.y ) );

		Transform->Forward	= glm::normalize( Transform->Direction );
		Transform->Right	= glm::normalize( glm::cross( Transform->Forward, glm::vec3( 0, 1, 0 ) ) );
		Transform->Up		= glm::normalize( glm::cross( Transform->Right, Transform->Forward ) );
	}
} // namespace Nocturn