#include "rendering/world/world.h"

#include "core/async/threadpool.h"

namespace Nocturn
{
	void World::Init( )
	{
		m_taskSystem   = std::make_unique< TaskSystem >( 7 );
		m_skyboxRender = std::make_unique< SkyboxRendering >( );
		m_camera	   = std::make_unique< Camera >( );
		m_chunk		   = std::make_unique< ChunkManager >( *m_taskSystem );

		m_skyboxRender->init( );
		m_chunkRender.init( );
	}

	void World::Update( const double dt )
	{
		m_camera->processInput( dt );

		const auto currentPosition = static_cast< ivec3 >( m_camera->getCameraPosition( ) );

		m_chunk->Update( currentPosition );

		m_skyboxRender->render( *m_camera );

		m_chunk->Render( *m_camera, m_chunkRender );
	}

	void World::Free( )
	{
	}
} // namespace Nocturn