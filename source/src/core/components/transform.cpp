#include "transform.h"

#include <iostream>

namespace Nocturn
{
	void TransformSystem::Update( Transform *transform )
	{
		assert( transform );

		vec3 direction;
		direction.x = cos( glm::radians( transform->rotation.x ) ) * cos( glm::radians( transform->rotation.y ) );
		direction.y = sin( glm::radians( transform->rotation.y ) );
		direction.z = sin( glm::radians( transform->rotation.x ) ) * cos( glm::radians( transform->rotation.y ) );

		transform->forward = glm::normalize( direction );
		transform->right	= glm::normalize( glm::cross( transform->forward, glm::vec3( 0, 1, 0 ) ) );
		transform->up		= glm::normalize( glm::cross( transform->right, transform->forward ) );
	}

} // namespace Nocturn