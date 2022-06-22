#include "physics.h"

#include "rendering/components/entity/player.h"

namespace Nocturn
{
	Physics::Physics( rendering::ChunkManager &chunkManager, Transform &transform, RigidBody &rigidBody ) :
		m_pChunkManager( &chunkManager ), m_pTransform( &transform ), m_pRigidBody( &rigidBody )
	{}

	void Physics::Update( const double dt )
	{
		const auto dtf = static_cast<float> (dt);
		const auto dt2 = dtf * dtf;

		// TODO: Fix physics gravitation here
		m_pRigidBody->velocity += m_pRigidBody->acceleration * dtf;
		m_pTransform->position += m_pRigidBody->velocity * dtf + 0.5f * m_pRigidBody->acceleration * dt2;

		if( m_pRigidBody->useGravity )
		{
			//m_pRigidBody->velocity -= gravity * updateRate;
		}
		m_pRigidBody->velocity = glm::clamp( m_pRigidBody->velocity, -terminalVelocity, terminalVelocity );

		ProcessCollision( );
	}

	void Physics::ProcessCollision( ) const noexcept
	{
		const auto px	   = static_cast< int32 >( m_pTransform->position.x );
		const auto pz	   = static_cast< int32 >( m_pTransform->position.z );
		const auto bottomY = static_cast< int32 >( glm::ceil( m_pTransform->position.y - Player::CPlayerBound.y ) );

		const auto chunkX = px / CHUNK_X;
		const auto chunkZ = pz / CHUNK_Z;

		const auto &chunk = m_pChunkManager->GetChunk( { chunkX, chunkZ } );

		if( chunk.getBlock( px, bottomY, pz ) != BlockId::Air )
		{
			m_pRigidBody->velocity.y = 0;
		}
		else
			m_pRigidBody->velocity.y = -15.0f;
	}
} // namespace Nocturn
