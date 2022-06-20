#include "rendering/components/entity/entity.h"

namespace Nocturn
{
	Entity::Entity( ) noexcept
		:	position( glm::vec3( 0.f ) )
		,	rotation( glm::vec3( 0.f ) )
		,	velocity( glm::vec3( 0.f ) )
		,	box( { 0.f, 0.f, 0.f } )
	{ }

	Entity::Entity( const glm::vec3 &pos, const glm::vec3 &rot )
		:	position( pos )
		,	rotation( rot )
		,	velocity( glm::vec3( 0.f ) )
		,	box( { 0, 0, 0 } )
	{}

	Entity::Entity( const glm::vec3 &pos, const glm::vec3 &rot, const glm::vec3 &box )
		:	position( pos )
		,	rotation( rot )
		,	velocity( glm::vec3( 0.f ) )
		,	box( box )
	{}
} // namespace Nocturn