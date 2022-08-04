#include "physics.h"

#include "application/input/keyboard.h"
#include "core/components/constants.hpp"
#include "rendering/components/entity/player.h"

namespace Nocturn
{
	// will be change later
	static vec3 normal = vec3(0,0,0);

	template< typename... Args >
	static void print(Args... args)
	{
		((std::cout << args << ' '), ...) << '\n';
	}

	static void printVec(const vec3& vec)
	{
		std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << '\n';
	}

	Physics::Physics( const Entity &player, ChunkManager &chunkManager, Transform &transform, RigidBody &rigidBody )
		:		m_pPlayer (&player)
		,		m_pChunkManager( &chunkManager )
		,		m_pTransform( &transform )
		,		m_pRigidBody( &rigidBody )
	{ }

	void Physics::Update( const double dt )
	{
		const auto dtf = static_cast< float >( dt );
		static float accumulatedDeltaTime = 0.0f;
		accumulatedDeltaTime += dtf;

		while( accumulatedDeltaTime >= CPhysicsUpdateRate )
		{
			accumulatedDeltaTime -= CPhysicsUpdateRate;
			normal = vec3(0.f);

			auto &velocity	   = m_pRigidBody->velocity;
			auto &acceleration = m_pRigidBody->acceleration;
			auto &position = m_pTransform->position;

			float minTime = 1.0f;

			if( Keyboard::keyWentDown( GLFW_KEY_SPACE ) )
			{
				m_pRigidBody->velocity.y += 8.0f;
			}

			position += velocity * CPhysicsUpdateRate;
			velocity += acceleration * CPhysicsUpdateRate;
			velocity += CGravity * CPhysicsUpdateRate;
			velocity = glm::clamp(velocity, -CEndVelocity, CEndVelocity);

			ProcessCollision( minTime );
		}
	}

	void Physics::ProcessCollision( float &minTime ) const noexcept
	{
		auto &velocity = m_pRigidBody->velocity;
		auto &acceleration = m_pRigidBody->acceleration;
		auto &position = m_pTransform->position;

		vec3 real = position;
        const auto minI = GetMinInterval( real );
        const auto maxI = GetMaxInterval( real );

		real += velocity * normal;

		const vec3 min = real - Player::CPlayerBound * 0.5f;
        const vec3 max = real + Player::CPlayerBound * 0.5f;

        const auto minX = static_cast< int32 >( glm::floor( glm::min( min.x, minI.x ) ) ) % Constants::CChunkX;
		const auto minY = static_cast< int32 >( glm::floor( glm::min( min.y, minI.y ) ) ) % Constants::CChunkY;
		const auto minZ = static_cast< int32 >( glm::floor( glm::min( min.z, minI.z ) ) ) % Constants::CChunkZ;
		const auto maxX = static_cast< int32 >( glm::floor( glm::max( max.x, maxI.x ) ) ) % Constants::CChunkX;
		const auto maxY = static_cast< int32 >( glm::floor( glm::max( max.y, maxI.y ) ) ) % Constants::CChunkY;
		const auto maxZ = static_cast< int32 >( glm::floor( glm::max( max.z, maxI.z ) ) ) % Constants::CChunkZ;

        minTime = 1.0f;
		const auto &chunk = m_pChunkManager->GetChunk( {
				position.x / Constants::CChunkX,
				position.z / Constants::CChunkZ
		} );

		for( int32 x = minX; x <= maxX; x++ )
        for( int32 y = minY; y <= maxY; y++ )
		for( int32 z = minZ; z <= maxZ; z++ )
		{
			printVec(position);
			if( y >= 0 && y < Constants::CChunkY && chunk.getBlock( x, y, z ) != BlockId::Air )
			{
				if( const float collisionTime = SweptCollision( velocity, x, y, z ); collisionTime < minTime )
				{
					minTime = collisionTime;
					if( minTime < 1.0f )
					{
						position += normal * minTime;
						if( abs( normal.x ) == 1.0f )
						{
							acceleration.x = 0.0f;
							velocity.x	   = 0.0f;
						}
						if( abs( normal.y ) == 1.0f )
						{
							acceleration.y = 0.0f;
							velocity.y	   = 0.0f;
						}
						if( abs( normal.z ) == 1.0f )
						{
							acceleration.z = 0.0f;
							velocity.z	   = 0.0f;
						}
					}
				}
			}
		}
	}

	float Physics::SweptCollision( const vec3 &velocity, const float x, const float y, const float z ) const noexcept
	{
		vec3 invEntry, invExit;
		vec3 entry, exit;

		const auto minI = GetMinInterval( m_pTransform->position );
        const auto maxI = GetMaxInterval( m_pTransform->position );

		if( velocity.x > 0.0f )
		{
			invEntry.x = x - maxI.x;
			entry.x	   = invEntry.x / velocity.x;
			invExit.x  = x + 1 - minI.x;
			exit.x	   = invExit.x / velocity.x;
		}
		else if( velocity.x < 0.0f )
		{
			invEntry.x = x + 1 - minI.x;
			entry.x	   = invEntry.x / velocity.x;
			invExit.x  = x - maxI.x;
			exit.x	   = invExit.x / velocity.x;
		}
		else
		{
			invEntry.x = x + 1 - minI.x;
			invExit.x  = x - maxI.x;
			entry.x	   = -std::numeric_limits< float >::infinity( );
			exit.x	   = std::numeric_limits< float >::infinity( );
		}

		if( velocity.y > 0.0f )
		{
			invEntry.y = y - maxI.y;
			entry.y	   = invEntry.y / velocity.y;
			invExit.y  = y + 1 - minI.y;
			exit.y	   = invExit.y / velocity.y;
		}
		else if( velocity.y < 0.0f )
		{
			invEntry.y = y + 1 - minI.y;
			entry.y	   = invEntry.y / velocity.y;
			invExit.y  = y - maxI.y;
			exit.y	   = invExit.y / velocity.y;
		}
		else
		{
			invEntry.y = y + 1 - minI.y;
			invExit.y  = y - maxI.y;
			entry.y	   = -std::numeric_limits< float >::infinity( );
			exit.y	   = std::numeric_limits< float >::infinity( );
		}

		if( velocity.z > 0.0f )
		{
			invEntry.z = z - maxI.z;
			entry.z	   = invEntry.z / velocity.z;
			invExit.z  = z + 1 - minI.z;
			exit.z	   = invExit.z / velocity.z;
		}
		else if( velocity.z < 0.0f )
		{
			invEntry.z = z + 1 - minI.z;
			entry.z	   = invEntry.z / velocity.z;
			invExit.z  = z - maxI.z;
			exit.z	   = invExit.z / velocity.z;
		}
		else
		{
			invEntry.z = z + 1 - minI.z;
			invExit.z  = z - maxI.z;
			entry.z	   = -std::numeric_limits< float >::infinity( );
			exit.z	   = std::numeric_limits< float >::infinity( );
		}

		// TODO: Inspect why entryTime is negative
		const float entryTime = std::max(std::max(entry.x,entry.z),entry.y) * -1;

		// If there was no collision
		if( entryTime >= 1.0f || entryTime < 0 )
		{
			return 1.0f;
		}

		const float exitTime = std::min( std::min( exit.x, exit.z ), exit.y );
		if( entryTime > exitTime )
		{
			return 1.0f;
		}

		if( entry.x > 1.0f || entry.y > 1.0f || entry.z > 1.0f)
		{
			return 1.0f;
		}

        if( entry.x > entry.z )
		{
			if( entry.x > entry.y )
			{
				normal.x = -glm::sign( velocity.x );
				normal.y = 0.0f;
				normal.z = 0.0f;
			}
			else
			{
				normal.x = 0.0f;
				normal.y = -glm::sign( velocity.y );
				normal.z = 0.0f;
			}
		}
		else
		{
			if( entry.z > entry.y )
			{
				normal.x = 0.0f;
				normal.y = 0.0f;
				normal.z = -glm::sign( velocity.z );
			}
			else
			{
				normal.x = 0.0f;
				normal.y = -glm::sign( velocity.y );
				normal.z = 0.0f;
			}
		}
        return entryTime;
	}

	bool Physics::AABBtoAABB( const Transform& transform1, const AABB& box1, const Transform& transform2, const AABB &box2 ) noexcept
	{
		const vec3 min1 = transform1.position - ( box1.size * 0.5f );
		const vec3 max1 = transform1.position + ( box1.size * 0.5f );
		const vec3 min2 = transform2.position - ( box2.size * 0.5f );
		const vec3 max2 = transform2.position + ( box2.size * 0.5f );

		return ( min1.x <= max2.x && max1.x >= min2.x ) &&
			( min1.y <= max2.y && max1.y >= min2.y ) &&
			( min1.z <= max2.z && max1.z >= min2.z );
	}

} // namespace Nocturn
