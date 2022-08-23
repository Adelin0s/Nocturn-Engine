#include "physics.h"

#include "application/input/keyboard.h"
#include "core/components/constants.hpp"
#include "rendering/components/entity/player.h"

namespace Nocturn
{
	template< typename... TArgs >
	static void print( TArgs... args )
	{
		( ( std::cout << args << ' ' ), ... ) << '\n';
	}

	static void printVec( const vec3 &vec )
	{
		std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << '\n';
	}

	Physics::Physics( const Entity &player, ChunkManager &chunkManager, Transform &transform, RigidBody &rigidBody )
		:		m_pPlayer( &player )
		,		m_pChunkManager( &chunkManager )
		,		m_pTransform( &transform )
		,		m_pRigidBody( &rigidBody )
	{ }

	void Physics::Update( const double dt )
	{
		auto &velocity	   = m_pRigidBody->velocity;
		auto &position	   = m_pTransform->position;

		if (Keyboard::keyWentDown( GLFW_KEY_SPACE ))
		{
			velocity.y += 8.0f;
			m_pRigidBody->onGround = false;
		}

        float remainingTime = 1.0f;
		float minTime;

		vec3 localVelocity = velocity * CPhysicsUpdateRate;

		constexpr float hDrag = glm::max( 1.0f - CHorizontalDrag * CPhysicsUpdateRate, 0.0f );
		constexpr float vDrag = glm::max( 1.0f - CVerticalDrag * CPhysicsUpdateRate, 0.0f );
		velocity *= vec3( hDrag, vDrag, hDrag );

		for( uint8 i = 0; i < 3; i++ )
		{
			localVelocity = vec3(
				localVelocity.x * ( 1 - glm::abs( normal.x ) ) * remainingTime,
				localVelocity.y * ( 1 - glm::abs( normal.y ) ) * remainingTime,
				localVelocity.z * ( 1 - glm::abs( normal.z ) ) * remainingTime );
			normal = vec3( 0.0f );

            ProcessCollision( minTime, localVelocity );

			position += localVelocity * minTime;

            if(minTime < 1.0f)
			{
				std::cout << minTime << ' ';
				printVec( normal );
				position += normal * std::numeric_limits< float >::epsilon( );
            }
            remainingTime = 1.0f - minTime;

            if(remainingTime <= 0) break;
        }

		if( normal.y == 1.0f )
			velocity.y = 0;
		else
			velocity += CGravity * CPhysicsUpdateRate;
	}

	void Physics::ProcessCollision( float &minTime, const vec3 &velocity ) noexcept
	{
		const auto &position	= m_pTransform->position; 
		const auto &bound = m_pPlayer->GetBound( );

		const auto minI = bound.min;
		const auto maxI = bound.max;

		const auto min = bound.min + velocity;
		const auto max = bound.max + velocity;

		const auto minX = static_cast< int32 >( glm::floor( glm::min( min.x, minI.x ) ) );
		const auto minY = static_cast< int32 >( glm::floor( glm::min( min.y, minI.y ) ) );
		const auto minZ = static_cast< int32 >( glm::floor( glm::min( min.z, minI.z ) ) );
		const auto maxX = static_cast< int32 >( glm::floor( glm::max( max.x, maxI.x ) ) );
		const auto maxY = static_cast< int32 >( glm::floor( glm::max( max.y, maxI.y ) ) );
		const auto maxZ = static_cast< int32 >( glm::floor( glm::max( max.z, maxI.z ) ) );

		minTime	= 1.0f;
		const auto &chunk = m_pChunkManager->GetChunk( { position.z / Constants::CChunkX,
														 position.x / Constants::CChunkZ } );
		for( int32 x = minX; x <= maxX; x++ )
		for( int32 y = minY; y <= maxY; y++ )
		for( int32 z = minZ; z <= maxZ; z++ )
		{
			if( y >= 0 && y < Constants::CChunkY && chunk.getBlock( x, y, z ) != BlockId::Air )
			{
				const float collisionTime = SweptCollision( velocity, min, max, minI, maxI, minTime, x, y, z);
				if( collisionTime < minTime )
				{
					minTime = collisionTime;
				}
			}
		}
	}

	float Physics::SweptCollision( const vec3 &velocity, const vec3 &min, const vec3 &max, const vec3 &minI, const vec3 &maxI, const float minTime, const float x, const float y, const float z ) noexcept
	{
		vec3 invEntry, invExit;
		vec3 entry, exit;

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
		const float entryTime = glm::max( glm::max( entry.x, entry.z ), entry.y );

		if( entryTime >= minTime ) return 1.0f;
		if( entryTime < 0 ) return 1.0f;

		const float exitTime = glm::min( glm::min( exit.x, exit.z ), exit.y );

		if( entryTime > exitTime ) return 1.0f;

		if( entry.x > 1.0f )
		{
			if( max.x < x || min.x > x + 1.0f )
				return 1.0f;
		}

		if( entry.y > 1.0f )
		{
			if( max.y < y || min.y > y + 1.0f )
				return 1.0f;
		}

		if( entry.z > 1.0f )
		{
			if( max.z < z || min.z > z + 1.0f )
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
} // namespace Nocturn
