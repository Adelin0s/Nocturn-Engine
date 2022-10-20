#include "physics.h"

#include "application/input/keyboard.h"
#include "application/input/mouse.h"
#include "core/components/constants.hpp"
#include "rendering/components/entity/player.h"
#include "core/math/math.hpp"

#include "core/logging/logging.h"

namespace Nocturn
{
	static void printVec( const vec3 &vec )
	{
		std::cout << vec.x << ' ' << vec.y << ' ' << vec.z << '\n';
	}

	Physics::Physics( const Entity &player, ChunkManager &chunkManager, Transform &transform, RigidBody &rigidBody ) :
		m_pPlayer( &player ), m_pChunkManager( &chunkManager ), m_pTransform( &transform ), m_pRigidBody( &rigidBody )
	{}

	void Physics::Update( const double dt )
	{
		auto &velocity = m_pRigidBody->velocity;
		auto &position = m_pTransform->position;

		if( Keyboard::keyWentDown( GLFW_KEY_SPACE ) )
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

			if( minTime < 1.0f )
			{
				position += normal * std::numeric_limits< float >::epsilon( );
			}
			remainingTime = 1.0f - minTime;

			if( remainingTime <= 0 )
				break;
		}

		if( normal.y == 1.0f )
			velocity.y = 0;
		else
			velocity += CGravity * CPhysicsUpdateRate;
	}

	void Physics::ProcessCollision( float &minTime, const vec3 &velocity ) noexcept
	{
		const auto &position = m_pTransform->position;
		const auto &bound	 = m_pPlayer->GetBound( );

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

		minTime = 1.0f;
		const auto &chunk = m_pChunkManager->GetChunk( { position.x / Constants::CChunkX,
														 position.z / Constants::CChunkZ } );
		for( int32 x = minX; x <= maxX; x++ )
			for( int32 y = minY; y <= maxY; y++ )
				for( int32 z = minZ; z <= maxZ; z++ )
				{
					if( y >= 0 && y < Constants::CChunkY && chunk.getBlock( x, y, z ) != BlockId::Air )
					{
						const float collisionTime = SweptCollision( velocity, min, max, minI, maxI, minTime, x, y, z );
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

		if( entryTime >= minTime )
			return 1.0f;
		if( entryTime < 0 )
			return 1.0f;

		const float exitTime = glm::min( glm::min( exit.x, exit.z ), exit.y );

		if( entryTime > exitTime )
			return 1.0f;

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

	RaycastResult Physics::RaycastStatic( const vec3 &origin, const vec3 &normalDirection, const float maxDistance, const bool draw ) const noexcept
	{
		RaycastResult result{};
		const Style style = { Colors::offWhite, 0.1f };
		auto currentOrigin = origin;
		auto pointOnRay = origin;
		//Renderer::DrawBox( origin, {1.0f, 1.0f, 1.0f}, style );
		bool hit = false;
		for( float i = 0.0f; i < maxDistance; i += 0.1f )
		{
			if( glm::ceil( pointOnRay ) != currentOrigin )
			{
				currentOrigin = glm::ceil( pointOnRay );
				const auto size = vec3( 1.0f, 1.0f, 1.0f );
				Transform transform{};
				transform.position = currentOrigin;

				const auto block = m_pChunkManager->GetBlock( transform.position );
				if( draw && block != BlockId::Air && !hit )
				{
					hit = true;
					DrawBox( transform.position + 1.0f, size, style );
					Render( );
				}
			}
			pointOnRay += normalDirection * 0.1f;
		}
		return result;
		//std::cout << "here\n";
		//RaycastResult result{ };
		//result.hit = false;
		//if( Math::Compare< vec3 >( normalDirection, vec3( 0, 0, 0 ) ) )
		//{
		//	return result;
		//}
		//const Style style = { Colors::algaeGreen, 0.25f };
		//if( draw )
		//{
		//	Renderer::DrawLine( origin, origin + normalDirection * maxDistance, style );
		//}
		//// NOTE: Thank God for this paper http://www.cse.yorku.ca/~amana/research/grid.pdf which outlines what I'm doing here
		//vec3 rayEnd = origin + normalDirection * maxDistance;
		//// Do some fancy math to figure out which voxel is the next voxel
		//vec3 blockCenter = glm::ceil( origin );
		//vec3 step = glm::sign( normalDirection );
		//// Max amount we can step in any direction of the ray, and remain in the voxel
		//vec3 blockCenterToOriginSign = glm::sign( blockCenter - origin );
		//vec3 goodNormalDirection = vec3(
		//	normalDirection.x == 0.0f ? 1e-10 * blockCenterToOriginSign.x : normalDirection.x,
		//	normalDirection.y == 0.0f ? 1e-10 * blockCenterToOriginSign.y : normalDirection.y,
		//	normalDirection.z == 0.0f ? 1e-10 * blockCenterToOriginSign.z : normalDirection.z );
		//vec3 tDelta = ( ( blockCenter + step ) - origin ) / goodNormalDirection;
		//// If any number is 0, then we max the delta so we don't get a false positive
		//if( tDelta.x == 0.0f )
		//	tDelta.x = 1e10;
		//if( tDelta.y == 0.0f )
		//	tDelta.y = 1e10;
		//if( tDelta.z == 0.0f )
		//	tDelta.z = 1e10;
		//vec3 tMax = tDelta;
		//float minTValue;
		//do
		//{
		//	// TODO: This shouldn't have to be calculated every step
		//	tDelta	  = ( blockCenter - origin ) / goodNormalDirection;
		//	tMax	  = tDelta;
		//	minTValue = FLT_MAX;
		//	if( tMax.x < tMax.y )
		//	{
		//		if( tMax.x < tMax.z )
		//		{
		//			blockCenter.x += step.x;
		//			// Check if we actually hit the block
		//			if( DoRaycast( origin, normalDirection, maxDistance, draw, blockCenter, step, &result ) )
		//			{
		//				return result;
		//			}
		//			// tMax.x += tDelta.x;
		//			minTValue = tMax.x;
		//		}
		//		else
		//		{
		//			blockCenter.z += step.z;
		//			if( DoRaycast( origin, normalDirection, maxDistance, draw, blockCenter, step, &result ) )
		//			{
		//				return result;
		//			}
		//			// tMax.z += tDelta.z;
		//			minTValue = tMax.z;
		//		}
		//	}
		//	else
		//	{
		//		if( tMax.y < tMax.z )
		//		{
		//			blockCenter.y += step.y;
		//			if( DoRaycast( origin, normalDirection, maxDistance, draw, blockCenter, step, &result ) )
		//			{
		//				return result;
		//			}
		//			// tMax.y += tDelta.y;
		//			minTValue = tMax.y;
		//		}
		//		else
		//		{
		//			blockCenter.z += step.z;
		//			if( DoRaycast( origin, normalDirection, maxDistance, draw, blockCenter, step, &result ) )
		//			{
		//				return result;
		//			}
		//			// tMax.z += tDelta.z;
		//			minTValue = tMax.z;
		//		}
		//	}
		//} while( minTValue < maxDistance );

		//return result;
	}

	bool Physics::DoRaycast( const vec3 &origin, const vec3 &normalDirection, float maxDistance, bool draw, const vec3 &blockCorner, const vec3 &step, RaycastResult *out ) const noexcept
	{
		glm::vec3 blockCenter = blockCorner - (glm::vec3(0.5f) * step);
		const Style style = { Colors::offWhite, 0.15f };
		if( draw )
		{
			DrawBox(blockCenter, glm::vec3(1.0f, 1.0f, 1.0f), style);
		}

		//int blockId = ChunkManager::getBlock(blockCenter).id;
		//BlockFormat block = BlockMap::getBlock(blockId);
		const auto block = m_pChunkManager->GetBlock( blockCenter );
		if ( block != BlockId::Air )
		{
			auto blockOffset = glm::vec3();
			auto blockSize = glm::vec3(1.0f, 1.0f, 1.0f);

			Transform currentTransform;
			currentTransform.position = blockCenter;

			glm::vec3 min = currentTransform.position - (blockSize * 0.5f) + blockOffset;
			glm::vec3 max = currentTransform.position + (blockSize * 0.5f) + blockOffset;
			float t1 = (min.x - origin.x) / (Math::Compare(normalDirection.x, 0.0f) ? 0.00001f : normalDirection.x);
			float t2 = (max.x - origin.x) / (Math::Compare(normalDirection.x, 0.0f) ? 0.00001f : normalDirection.x);
			float t3 = (min.y - origin.y) / (Math::Compare(normalDirection.y, 0.0f) ? 0.00001f : normalDirection.y);
			float t4 = (max.y - origin.y) / (Math::Compare(normalDirection.y, 0.0f) ? 0.00001f : normalDirection.y);
			float t5 = (min.z - origin.z) / (Math::Compare(normalDirection.z, 0.0f) ? 0.00001f : normalDirection.z);
			float t6 = (max.z - origin.z) / (Math::Compare(normalDirection.z, 0.0f) ? 0.00001f : normalDirection.z);

			float tmin = glm::max(glm::max(glm::min(t1, t2), glm::min(t3, t4)), glm::min(t5, t6));
			float tmax = glm::min(glm::min(glm::max(t1, t2), glm::max(t3, t4)), glm::max(t5, t6));
			if (tmax < 0 || tmin > tmax)
			{
				// No intersection
				return false;
			}

			float depth = 0.0f;
			if (tmin < 0.0f)
			{
				// The ray's origin is inside the AABB
				depth = tmax;
			}
			else
			{
				depth = tmin;
			}

			out->point = origin + normalDirection * depth;
			out->hit = true;
			out->blockCenter = currentTransform.position + blockOffset;
			out->blockSize = blockSize;
			out->hitNormal = out->point - out->blockCenter;
			float maxComponent = glm::max(glm::abs(out->hitNormal.x), glm::max(glm::abs(out->hitNormal.y), glm::abs(out->hitNormal.z)));
			out->hitNormal = glm::abs(out->hitNormal.x) == maxComponent
				? glm::vec3(1, 0, 0) * glm::sign(out->hitNormal.x)
				: glm::abs(out->hitNormal.y) == maxComponent
				? glm::vec3(0, 1, 0) * glm::sign(out->hitNormal.y)
				: glm::vec3(0, 0, 1) * glm::sign(out->hitNormal.z);
			return true;
		}

		return false;
	}

} // namespace Nocturn