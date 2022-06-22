#include "transform.h"

#include <iostream>

namespace Nocturn
{
	bool			  isInit	 = false;
	static Transform *pTransform = nullptr;

	void TransformSystem::Init( Transform &transform )
	{
		if( !isInit )
		{
			pTransform = &transform;
		}
		isInit = true;
	}

	void TransformSystem::Update( )
	{
		assert( pTransform );

		vec3 direction;
		direction.x = cos( glm::radians( pTransform->rotation.x ) ) * cos( glm::radians( pTransform->rotation.y ) );
		direction.y = sin( glm::radians( pTransform->rotation.y ) );
		direction.z = sin( glm::radians( pTransform->rotation.x ) ) * cos( glm::radians( pTransform->rotation.y ) );

		pTransform->forward = glm::normalize( direction );
		pTransform->right	= glm::normalize( glm::cross( pTransform->forward, glm::vec3( 0, 1, 0 ) ) );
		pTransform->up		= glm::normalize( glm::cross( pTransform->right, pTransform->forward ) );
	}

} // namespace Nocturn