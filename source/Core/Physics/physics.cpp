#include "physics.h"

#include "Application/Input/keyboard.h"
#include "Application/Input/mouse.h"
#include "Context/Components/BoxComponent.h"
#include "Context/Components/TransformComponent.h"
#include "Context/GameFramework/Character.h"
#include "Core/Components/constants.hpp"
#include "Core/Math/math.hpp"
#include "Core/Physics/rigidbody.h"
#include "Rendering/Renderer/renderer.h"
#include "Rendering/Renderer/style.h"

namespace Nocturn
{
	class NBoxComponent;

	NPhysics::NPhysics(NCharacter* CharacterIn, NChunkManager& chunkManager)
	:
		Character(CharacterIn), m_pChunkManager(&chunkManager)
	{
		 m_pTransform = Character->GetTransformComponent();
	}

	void NPhysics::Update(const double DeltaTime)
	{
		auto& velocity = Character->GetVelocity();
		auto& position = m_pTransform->GetLocation();

		if( Keyboard::keyWentDown(GLFW_KEY_SPACE) )
		{
			velocity.y += 8.0f;
			//m_pRigidBody->onGround = false;
		}

		float remainingTime = 1.0f;
		float MinTime;

		vec3 localVelocity = velocity * static_cast< float >(DeltaTime);

		constexpr float hDrag = glm::max(1.0f - CHorizontalDrag * CPhysicsUpdateRate, 0.0f);
		constexpr float vDrag = glm::max(1.0f - CVerticalDrag * CPhysicsUpdateRate, 0.0f);
		velocity *= vec3(hDrag, vDrag, hDrag);

		for( uint8 i = 0; i < 3; i++ )
		{
			localVelocity = vec3(
				localVelocity.x * (1 - glm::abs(normal.x)) * remainingTime,
				localVelocity.y * (1 - glm::abs(normal.y)) * remainingTime,
				localVelocity.z * (1 - glm::abs(normal.z)) * remainingTime);
			normal = vec3(0.0f);

			ProcessCollision(MinTime, localVelocity);

			position += localVelocity * MinTime;

			if( MinTime < 1.0f )
			{
				position += normal * std::numeric_limits< float >::epsilon();
			}
			remainingTime = 1.0f - MinTime;

			if( remainingTime <= 0 )
				break;
		}

		if( normal.y == 1.0f )
			velocity.y = 0;
		else
			velocity += CGravity * static_cast< float >(DeltaTime);
	}

	void NPhysics::ProcessCollision( float &MinTime, const vec3 &Velocity ) noexcept
	{
		const auto &Position = m_pTransform->GetLocation();

		const auto BoxComponent = Character->GetComponentByTag<NBoxComponent>("BoxComponent");
		if (BoxComponent == nullptr)
		{
			LogError("BoxComponent nullptr!");
		}

		const auto MinBound = BoxComponent->GetMin();
		const auto MaxBound = BoxComponent->GetMax();

		const auto MinBoundVelocity = MinBound + Velocity;
		const auto MaxBoundVelocity = MaxBound + Velocity;

		const auto MinX = static_cast< int32 >(glm::floor(glm::min(MinBoundVelocity.x, MinBound.x)));
		const auto MinY = static_cast< int32 >(glm::floor(glm::min(MinBoundVelocity.y, MinBound.y)));
		const auto MinZ = static_cast< int32 >(glm::floor(glm::min(MinBoundVelocity.z, MinBound.z)));
		const auto MaxX = static_cast< int32 >(glm::floor(glm::max(MaxBoundVelocity.x, MaxBound.x)));
		const auto MaxY = static_cast< int32 >(glm::floor(glm::max(MaxBoundVelocity.y, MaxBound.y)));
		const auto MaxZ = static_cast< int32 >(glm::floor(glm::max(MaxBoundVelocity.z, MaxBound.z)));

		MinTime = 1.0f;
		std::cout << Position.x << ' ' << Position.y << ' ' << Position.z << '\n';

		const auto ChunkX		= static_cast< int32 >(Position.x / Constants::CChunkX);
		const auto ChunkZ		= static_cast< int32 >(Position.z / Constants::CChunkZ);
		const auto CurrentChunk = m_pChunkManager->GetChunk({ ChunkX, ChunkZ });
		if (CurrentChunk == nullptr)
		{
			LogWarning("Failed to get chunk from chunk position (%.2f, %.2f)", ChunkX, ChunkZ);
			return;
		}
		std::cout << ChunkX << ' ' << ChunkZ << '\n';

		for( int32 x = MinX; x <= MaxX; x++ )
		{
			for( int32 y = MinY; y <= MaxY; y++ )
			{
				for( int32 z = MinZ; z <= MaxZ; z++ )
				{
					const auto ChunkCoords = Math::WorldCoordsToChunkCoords({x, y, z});
					if( y >= 0 && y < Constants::CChunkY && CurrentChunk->GetBlock( ChunkCoords ) != EBlockId::Air )
					{
						const float collisionTime = SweptCollision( Velocity, MinBound, MaxBound, MinBoundVelocity, MaxBoundVelocity, MinTime, x, y, z );
						if( collisionTime < MinTime )
						{
							MinTime = collisionTime;
						}
					}
				}
			}
		}
	}

	float NPhysics::SweptCollision( const vec3 &Velocity, const vec3 &MinBound, const vec3 &MaxBound, const vec3 &MinBoundVelocity, const vec3 &MaxBoundVelocity, const float MinTime, const float x, const float y, const float z ) noexcept
	{
		vec3 InvEntry, InvExit;
		vec3 Entry, Exit;

		if( Velocity.x > 0.0f )
		{
			InvEntry.x = x - MaxBound.x;
			Entry.x	   = InvEntry.x / Velocity.x;
			InvExit.x  = x + 1 - MinBound.x;
			Exit.x	   = InvExit.x / Velocity.x;
		}
		else if( Velocity.x < 0.0f )
		{
			InvEntry.x = x + 1 - MinBound.x;
			Entry.x	   = InvEntry.x / Velocity.x;
			InvExit.x  = x - MaxBound.x;
			Exit.x	   = InvExit.x / Velocity.x;
		}
		else
		{
			InvEntry.x = x + 1 - MinBound.x;
			InvExit.x  = x - MaxBound.x;
			Entry.x	   = -std::numeric_limits< float >::infinity( );
			Exit.x	   = std::numeric_limits< float >::infinity( );
		}

		if( Velocity.y > 0.0f )
		{
			InvEntry.y = y - MaxBound.y;
			Entry.y	   = InvEntry.y / Velocity.y;
			InvExit.y  = y + 1 - MinBound.y;
			Exit.y	   = InvExit.y / Velocity.y;
		}
		else if( Velocity.y < 0.0f )
		{
			InvEntry.y = y + 1 - MinBound.y;
			Entry.y	   = InvEntry.y / Velocity.y;
			InvExit.y  = y - MaxBound.y;
			Exit.y	   = InvExit.y / Velocity.y;
		}
		else
		{
			InvEntry.y = y + 1 - MinBound.y;
			InvExit.y  = y - MaxBound.y;
			Entry.y	   = -std::numeric_limits< float >::infinity( );
			Exit.y	   = std::numeric_limits< float >::infinity( );
		}

		if( Velocity.z > 0.0f )
		{
			InvEntry.z = z - MaxBound.z;
			Entry.z	   = InvEntry.z / Velocity.z;
			InvExit.z  = z + 1 - MinBound.z;
			Exit.z	   = InvExit.z / Velocity.z;
		}
		else if( Velocity.z < 0.0f )
		{
			InvEntry.z = z + 1 - MinBound.z;
			Entry.z	   = InvEntry.z / Velocity.z;
			InvExit.z  = z - MaxBound.z;
			Exit.z	   = InvExit.z / Velocity.z;
		}
		else
		{
			InvEntry.z = z + 1 - MinBound.z;
			InvExit.z  = z - MaxBound.z;
			Entry.z	   = -std::numeric_limits< float >::infinity( );
			Exit.z	   = std::numeric_limits< float >::infinity( );
		}
		const float EntryTime = glm::max( glm::max( Entry.x, Entry.z ), Entry.y );

		if( EntryTime >= MinTime )
			return 1.0f;
		if( EntryTime < 0 )
			return 1.0f;

		const float ExitTime = glm::min( glm::min( Exit.x, Exit.z ), Exit.y );

		if( EntryTime > ExitTime )
			return 1.0f;

		if( Entry.x > 1.0f )
		{
			if( MaxBoundVelocity.x < x || MinBoundVelocity.x > x + 1.0f )
				return 1.0f;
		}

		if( Entry.y > 1.0f )
		{
			if( MaxBoundVelocity.y < y || MinBoundVelocity.y > y + 1.0f )
				return 1.0f;
		}

		if( Entry.z > 1.0f )
		{
			if( MaxBoundVelocity.z < z || MinBoundVelocity.z > z + 1.0f )
				return 1.0f;
		}

		if( Entry.x > Entry.z )
		{
			if( Entry.x > Entry.y )
			{
				normal.x = -glm::sign( Velocity.x );
				normal.y = 0.0f;
				normal.z = 0.0f;
			}
			else
			{
				normal.x = 0.0f;
				normal.y = -glm::sign( Velocity.y );
				normal.z = 0.0f;
			}
		}
		else
		{
			if( Entry.z > Entry.y )
			{
				normal.x = 0.0f;
				normal.y = 0.0f;
				normal.z = -glm::sign( Velocity.z );
			}
			else
			{
				normal.x = 0.0f;
				normal.y = -glm::sign( Velocity.y );
				normal.z = 0.0f;
			}
		}
		return EntryTime;
	}

	RaycastResult NPhysics::RaycastStatic( const vec3 &Origin, const vec3 &NormalDirection, const float MaxDistance, const bool bDraw ) const noexcept
	{
		RaycastResult result{};
		const Style style = { Colors::offWhite, 0.1f };

		auto CurrentOrigin = Origin + vec3(Origin.x + 0.5f, Origin.y, Origin.z + 0.5f);
		//LogScreen( "Origin{} {} {}", CurrentOrigin.x, CurrentOrigin.y, CurrentOrigin.z);
		auto PointOnRay = Origin /*- 1.0f*/;

		// Draw player bounding box
		//Render::DrawBox( PointOnRay, {1.0f, 1.65f, 1.0f}, style );
		bool hit = false;
		for( float i = 0.0f; i < MaxDistance; i += 0.1f )
		{
			if( glm::ceil( PointOnRay ) != CurrentOrigin )
			{
				CurrentOrigin = glm::ceil( PointOnRay );
				constexpr auto Size = vec3( 1.0f, 1.0f, 1.0f );
				vec3 Position{};
				Position = CurrentOrigin;

				const auto block = m_pChunkManager->GetBlock( Position );
				if( bDraw && block != EBlockId::Air && !hit )
				{
					hit = true;
					//Render::DrawBox(Position, Size, style);
					//Render::Render();
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
			std::cout << "Origin: " << Origin << ' ';
			const auto StartPosition = Origin - vec3( 0.5f, 0.0f, 0.5f );
			//Render::DrawLine( StartPosition, Origin + NormalDirection * MaxDistance, style );
			//Render::Render( );
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
			tDelta = ( blockCenter - Origin ) / goodNormalDirection;
			tMax = tDelta;
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
		return true;
		glm::vec3 blockCenter = blockCorner * step;
		const Style style = { Colors::offWhite, 0.15f };
		if( draw )
		{
			//Render::DrawBox(blockCenter, glm::vec3(1.0f, 1.0f, 1.0f), style);
		}

		const auto block = m_pChunkManager->GetBlock( blockCenter );
		if ( block != EBlockId::Air )
		{
			auto blockOffset = glm::vec3();
			auto blockSize = glm::vec3(1.0f, 1.0f, 1.0f);

			vec3 currentTransform;
			currentTransform = blockCenter;

			glm::vec3 min = currentTransform - (blockSize * 0.5f) + blockOffset;
			glm::vec3 max = currentTransform + (blockSize * 0.5f) + blockOffset;
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
			out->blockCenter = currentTransform + blockOffset;
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