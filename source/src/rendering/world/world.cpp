#include "rendering/world/world.h"

#include "core/async/threadpool.h"

namespace Nocturn
{
	void World::Init( )
	{
		m_taskSystem   = std::make_unique< TaskSystem >( 1 );
		m_skyboxRender = std::make_unique< SkyboxRendering >( );
		m_chunk		   = std::make_unique< ChunkManager >( *m_taskSystem );

		m_skyboxRender->init( );
		m_chunkRender.init( );
		m_player.Init( );
	}

	void World::Update( const double dt )
	{
		m_player.Update( dt );
		auto pos = m_player.GetPlayerPosition( );

		const auto currentPosition = static_cast< ivec3 >( m_player.GetPlayerPosition( ) );

		m_chunk->Update( currentPosition );

		m_skyboxRender->render( m_player.GetCamera( ) );

		m_chunk->Render( m_player.GetCamera( ), m_chunkRender );
	}

	void World::Free( )
	{
	}
} // namespace Nocturn