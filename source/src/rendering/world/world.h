#ifndef WORLD_H
#define WORLD_H

#include <memory>

#include "application/config/config.hpp"

#include "rendering/data/camera.h"
#include "rendering/renderer/chunkrenderer.h"
#include "rendering/renderer/skyboxrenderer.h"

#include "rendering/components/shaders/shader.h"
#include "rendering/world/chunk/chunkmanager.h"

namespace Nocturn
{
	using namespace rendering;

	class World
	{
	public:
		World( ) noexcept = default;

		World( const World & ) = delete;
		World( World && )	   = delete;

		World &operator=( const World & ) = delete;
		World &operator=( World && ) = delete;

		void Init( );
		void Update( const float dt );
		void Free( );

		~World( ) noexcept = default;

	private:
		ChunkRendering					   m_chunkRender;
		std::unique_ptr< SkyboxRendering > m_skyboxRender;
		std::unique_ptr< Camera >		   m_camera;
		std::unique_ptr< ChunkManager >	   m_chunk;
	};
} // namespace Nocturn

#endif