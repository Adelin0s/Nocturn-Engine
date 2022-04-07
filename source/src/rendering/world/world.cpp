#include "rendering/world/world.h"

#include "core/threads/threadpool.h"

#include "core/math/noise.h"
#include "core/util/time.hpp"

namespace Nocturn
{
	void World::Init( )
	{
		m_skyboxRender = std::make_unique< SkyboxRendering >( );
		m_camera	   = std::make_unique< Camera >( );
		m_chunk		   = std::make_unique< ChunkManager >( *m_camera );

		m_skyboxRender->init( );
		m_chunkRender.init( );

		m_chunk->InitTasks( );
	}

	void World::Update( const float dt )
	{
		m_camera->processInput( dt );

		m_skyboxRender->render( *m_camera );

		m_chunk->LoadFutureChunks( *m_camera );

		m_chunk->ThreadUpdate( );

		m_chunk->Render( *m_camera, m_chunkRender );
	}

	void World::Free( )
	{
	}
} // namespace Nocturn