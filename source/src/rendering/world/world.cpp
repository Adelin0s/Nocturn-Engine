#include "rendering/world/world.h"

#include "rendering/world/block/blocksection.h"

namespace Nocturn
{
	void World::Init( )
	{
		m_taskSystem   = std::make_unique< TaskSystem >( 1 );
		m_skyboxRender = std::make_unique< SkyboxRendering >( );
		m_chunkManager = std::make_unique< ChunkManager >( *m_taskSystem );
		m_camera	   = std::make_unique< Camera >( );
		m_block		   = std::make_unique< BlockSection >( );

		m_chunkRender.init( );
	}

	void World::Update( const double dt )
	{
		m_camera->Update( dt );

		m_block->Render( *m_camera );

		const auto currentPosition = static_cast< ivec3 >( m_camera->getCameraPosition( ) );

		m_chunkManager->Update( currentPosition );
		m_chunkManager->Render( *m_camera, m_chunkRender );
		// m_skyboxRender->render( *m_camera );
	}

	void World::Free( )
	{
	}
} // namespace Nocturn