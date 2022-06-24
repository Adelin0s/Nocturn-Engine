#include "physics.h"

#include "rendering/components/entity/player.h"

namespace Nocturn
{
	Physics::Physics( const Entity &player, ChunkManager &chunkManager, Transform &transform, RigidBody &rigidBody )
		:		m_pPlayer (&player)
		,		m_pChunkManager( &chunkManager )
		,		m_pTransform( &transform )
		,		m_pRigidBody( &rigidBody )
	{ }

	void Physics::Update( const double dt )
	{
		const auto dtf = static_cast< float >( dt );

		auto &position	   = m_pTransform->position;
		auto &acceleration = m_pRigidBody->acceleration;
		auto &velocity	   = m_pRigidBody->velocity;

		// TODO: Fix physics gravitation here
		//velocity += acceleration * dtf;
		//position += velocity * dtf + 0.5f * acceleration * dtf * dtf;
		ProcessCollision( );

		position += velocity * dtf;
	}

	void Physics::ProcessCollision( ) const noexcept
	{
		const auto	chunkX = m_pTransform->position.x / CHUNK_X;
		const auto	chunkZ = m_pTransform->position.z / CHUNK_Z;
		const auto &chunk  = m_pChunkManager->GetChunk( { chunkX, chunkZ } );

		const auto &boundSize = m_pPlayer->GetBound(  ).size;
		const auto leftX   = static_cast< int32 >( m_pTransform->position.x - boundSize.x * 0.5 );
		const auto rightX  = static_cast< int32 >( m_pTransform->position.x + boundSize.x * 0.5 );
		const auto topY	   = static_cast< int32 >( m_pTransform->position.y - boundSize.y * 0.5 );
		const auto bottomY = static_cast< int32 >( m_pTransform->position.y - boundSize.y * 0.5 );
		const auto leftZ   = static_cast< int32 >( m_pTransform->position.z - boundSize.z * 0.5 );
		const auto rightZ  = static_cast< int32 >( m_pTransform->position.z + boundSize.z * 0.5 );

		for( int32 y = topY; y >= bottomY; y-- )
		for( int32 x = leftX; x <= rightX; x++ )
		for( int32 z = leftZ; z <= rightZ; z++ )
		{
			AABB blockBound( { 1.0f, 1.0f, 1.0f } );
			Transform blockTransform;
			blockTransform.position = { x, y, z };

			if( chunk.getBlock( x, y, z ) != BlockId::Air && CheckColliding( *m_pTransform, m_pPlayer->GetBound( ), blockTransform, blockBound ) )
			{
				CollisionResult result;
				result = GetCollisionFace( *m_pTransform, m_pPlayer->GetBound( ), blockTransform, blockBound );

				switch( result.face )
				{
					case CollisionFace::Left:
					case CollisionFace::Right:
						m_pRigidBody->velocity.z = 0;
						//std::cout << "Collision left-right ";
						break;

					case CollisionFace::Front:
					case CollisionFace::Back:
						m_pRigidBody->velocity.x = 0;
						//std::cout << "Collision front-back ";
						break;

					case CollisionFace::Top:
					case CollisionFace::Bottom:
						std::cout << "Collision top-bottom ";
						m_pRigidBody->velocity.y = 0;
						break;
					default:
						std::cout << "No collision ";
				}
			}
		}
	}

	bool Physics::CheckColliding( const Transform& transform1, const AABB& box1, const Transform& transform2, const AABB &box2 ) noexcept
	{
		const vec3 min1 = transform1.position - ( box1.size * 0.5f );
		const vec3 max1 = transform1.position + ( box1.size * 0.5f );
		const vec3 min2 = transform2.position - ( box2.size * 0.5f );
		const vec3 max2 = transform2.position + ( box2.size * 0.5f );

		return ( min1.x <= max2.x && max1.x >= min2.x ) &&
			( min1.y <= max2.y && max1.y >= min2.y ) &&
			( min1.z <= max2.z && max1.z >= min2.z );
	}

	CollisionResult Physics::GetCollisionFace( const Transform &transform1, const AABB &box1, const Transform &transform2, const AABB &box2 ) const noexcept
	{
		CollisionResult result;

		const auto transformDiff = transform1.position - transform2.position;
		if( transformDiff.y >= 0 )
			result.face = CollisionFace::Bottom;
		else if( transformDiff.y < 0 )
			result.face = CollisionFace::Top;
		if (transformDiff.x >= 0)
			result.face = CollisionFace::Left;
		else if (transformDiff.x < 0 )
			result.face = CollisionFace::Right;
		else if (transformDiff.z < 0)
			result.face = CollisionFace::Front;
		else if (transformDiff.z >= 0)
			result.face = CollisionFace::Back;
		return result;
	}
} // namespace Nocturn
