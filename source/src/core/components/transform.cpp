#include "transform.h"

#include <iostream>

namespace Nocturn
{
	void TransformSystem::Update( Transform *transform )
	{
		assert( transform );

		transform->direction.x = cos( glm::radians( transform->rotation.x ) ) * cos( glm::radians( transform->rotation.y ) );
		transform->direction.y = sin( glm::radians( transform->rotation.y ) );
		transform->direction.z = sin( glm::radians( transform->rotation.x ) ) * cos( glm::radians( transform->rotation.y ) );

		transform->forward	= glm::normalize( transform->direction );
		transform->right	= glm::normalize( glm::cross( transform->forward, glm::vec3( 0, 1, 0 ) ) );
		transform->up		= glm::normalize( glm::cross( transform->right, transform->forward ) );
	}
} // namespace Nocturn