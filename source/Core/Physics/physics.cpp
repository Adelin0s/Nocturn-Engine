#include "physics.h"

#include "application/input/keyboard.h"
#include "application/input/mouse.h"
#include "core/components/constants.hpp"
#include "rendering/components/entity/player.h"
#include "core/math/math.hpp"

namespace Nocturn
{
	NPhysics::NPhysics( const Entity &player, ChunkManager &chunkManager, NTransform &transform, NRigidBody &rigidBody )
	:
		m_pPlayer( &player ), m_pChunkManager( &chunkManager ), m_pTransform( &transform ), m_pRigidBody( &rigidBody )
	{}

	void NPhysics::Update( const double DeltaTime )
	{
		auto &velocity = m_pRigidBody->velocity;
		auto &position = m_pTransform->Position;

		if( Keyboard::keyWentDown( GLFW_KEY_SPACE ) )
		{
			velocity.y += 8.0f;
			m_pRigidBody->onGround = false;
		}

		float remainingTime = 1.0f;
		float minTime;

		vec3 localVelocity = velocity * static_cast< float >( DeltaTime );

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
			velocity += CGravity * static_cast< float >( DeltaTime );
	}

	void NPhysics::ProcessCollision( float &minTime, const vec3 &velocity ) noexcept
	{
		const auto &position = m_pTransform->Position;
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
		const auto &chunk = m_pChunkManager->GetChunk( { position.x / Constants::CChunkX, position.z / Constants::CChunkZ } );
		for( int32 x = minX; x <= maxX; x++ )
		{
			for( int32 y = minY; y <= maxY; y++ )
			{
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
		}
	}

	float NPhysics::SweptCollision( const vec3 &velocity, const vec3 &min, const vec3 &max, const vec3 &minI, const vec3 &maxI, const float minTime, const float x, const float y, const float z ) noexcept
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

	RaycastResult NPhysics::RaycastStatic( const vec3 &Origin, const vec3 &NormalDirection, const float MaxDistance, const bool bDraw ) const noexcept
	{
		RaycastResult result{};
		const Style style = { Colors::offWhite, 0.1f };

		auto CurrentOrigin = Origin;
		LogScreen( "Origin{} {} {}", CurrentOrigin.x, CurrentOrigin.y, CurrentOrigin.z);
		auto PointOnRay = Origin - 1.0f;
		//Render::DrawBox( origin, {1.0f, 1.0f, 1.0f}, style );
		bool hit = false;
		for( float i = 0.0f; i < MaxDistance; i += 0.1f )
		{
			if( glm::ceil( PointOnRay ) != CurrentOrigin )
			{
				CurrentOrigin = glm::ceil( PointOnRay );
				constexpr auto Size = vec3( 1.0f, 1.0f, 1.0f );
				NTransform transform{};
				transform.Position = CurrentOrigin;

				const auto block = m_pChunkManager->GetBlock( transform.Position );
				if( bDraw && block != BlockId::Air && !hit )
				{
					hit = true;
					Render::DrawBox( transform.Position + 1.0f, Size, style );
					Render::Render( );
				}
			}
			PointOnRay += NormalDirection * 0.1f;
		}

		//RaycastResult result{ };
		result.hit = false;
		if( Math::Compare( NormalDirection, vec3( 0, 0, 0 ) ) )
		{
			return result;
		}

		if( bDraw )
		{
			const auto StartPosition = Origin - vec3( 0.5f, 0.0f, 0.5f );
			Render::DrawLine( StartPosition, Origin + NormalDirection * MaxDistance, style );
		}
		vec3 rayEnd = Origin + NormalDirection * MaxDistance;
		vec3 blockCenter = glm::ceil( Origin );
		vec3 step = glm::sign( NormalDirection );
		vec3 blockCenterToOriginSign = glm::sign( blockCenter - Origin );
		vec3 goodNormalDirection = vec3(
			NormalDirection.x == 0.0f ? 1e-10 * blockCenterToOriginSign.x : NormalDirection.x,
			NormalDirection.y == 0.0f ? 1e-10 * blockCenterToOriginSign.y : NormalDirection.y,
			NormalDirection.z == 0.0f ? 1e-10 * blockCenterToOriginSign.z : NormalDirection.z );

		vec3 tDelta = ( ( blockCenter + step ) - Origin ) / goodNormalDirection;
		if( tDelta.x == 0.0f )
			tDelta.x = 1e10;
		if( tDelta.y == 0.0f )
			tDelta.y = 1e10;
		if( tDelta.z == 0.0f )
			tDelta.z = 1e10;
		vec3 tMax = tDelta;

		float minTValue;
		do
		{
			// TODO: This shouldn't have to be calculated every step
			tDelta	  = ( blockCenter - Origin ) / goodNormalDirection;
			tMax	  = tDelta;
			minTValue = FLT_MAX;
			if( tMax.x < tMax.y )
			{
				if( tMax.x < tMax.z )
				{
					blockCenter.x += step.x;
					// Check if we actually hit the block
					if( DoRaycast( Origin, NormalDirection, MaxDistance, bDraw, blockCenter, step, &result ) )
					{
						return result;
					}
					// tMax.x += tDelta.x;
					minTValue = tMax.x;
				}
				else
				{
					blockCenter.z += step.z;
					if( DoRaycast( Origin, NormalDirection, MaxDistance, bDraw, blockCenter, step, &result ) )
					{
						return result;
					}
					// tMax.z += tDelta.z;
					minTValue = tMax.z;
				}
			}
			else
			{
				if( tMax.y < tMax.z )
				{
					blockCenter.y += step.y;
					if( DoRaycast( Origin, NormalDirection, MaxDistance, bDraw, blockCenter, step, &result ) )
					{
						return result;
					}
					// tMax.y += tDelta.y;
					minTValue = tMax.y;
				}
				else
				{
					blockCenter.z += step.z;
					if( DoRaycast( Origin, NormalDirection, MaxDistance, bDraw, blockCenter, step, &result ) )
					{
						return result;
					}
					// tMax.z += tDelta.z;
					minTValue = tMax.z;
				}
			}
		} while( minTValue < MaxDistance );

		return result;
	}

	bool NPhysics::DoRaycast( const vec3 &origin, const vec3 &NormalDirection, float MaxDistance, bool draw, const vec3 &blockCorner, const vec3 &step, RaycastResult *out ) const noexcept
	{
		glm::vec3 blockCenter = blockCorner + (glm::vec3(0.5f) * step);
		const Style style = { Colors::offWhite, 0.15f };
		if( draw )
		{
			//Render::DrawBox(blockCenter, glm::vec3(1.0f, 1.0f, 1.0f), style);
		}

		const auto block = m_pChunkManager->GetBlock( blockCenter );
		if ( block != BlockId::Air )
		{
			auto blockOffset = glm::vec3();
			auto blockSize = glm::vec3(1.0f, 1.0f, 1.0f);

			NTransform currentTransform;
			currentTransform.Position = blockCenter;

			glm::vec3 min = currentTransform.Position - (blockSize * 0.5f) + blockOffset;
			glm::vec3 max = currentTransform.Position + (blockSize * 0.5f) + blockOffset;
			float t1 = (min.x - origin.x) / (Math::Compare(NormalDirection.x, 0.0f) ? 0.00001f : NormalDirection.x);
			float t2 = (max.x - origin.x) / (Math::Compare(NormalDirection.x, 0.0f) ? 0.00001f : NormalDirection.x);
			float t3 = (min.y - origin.y) / (Math::Compare(NormalDirection.y, 0.0f) ? 0.00001f : NormalDirection.y);
			float t4 = (max.y - origin.y) / (Math::Compare(NormalDirection.y, 0.0f) ? 0.00001f : NormalDirection.y);
			float t5 = (min.z - origin.z) / (Math::Compare(NormalDirection.z, 0.0f) ? 0.00001f : NormalDirection.z);
			float t6 = (max.z - origin.z) / (Math::Compare(NormalDirection.z, 0.0f) ? 0.00001f : NormalDirection.z);

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

			out->point = origin + NormalDirection * depth;
			out->hit = true;
			out->blockCenter = currentTransform.Position + blockOffset;
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