#include "rendering/world/world.h"

#include "core/scene.h"

namespace Nocturn
{
	// internal data
	static const Camera	*camera;
	static const Transform *transform;

	World::World( const Transform &transformRef, const Camera &cameraRef ) noexcept
	{
		camera	  = &cameraRef;
		transform = &transformRef;

		m_taskSystem   = std::make_unique< TaskSystem >( 1 );
		m_skyboxRender = std::make_unique< SkyboxRendering >( );
		m_chunkManager = std::make_unique< ChunkManager >( *m_taskSystem );

		m_chunkRender.init( );
	}

	void World::Update( const double dt )
	{
		const auto currentPosition = static_cast< ivec3 >( transform->position );

		m_chunkManager->Update( currentPosition );
		m_chunkManager->Render( *camera, m_chunkRender );
		m_skyboxRender->render( *camera );
	}

	void World::Free( )
	{
	}
} // namespace Nocturn