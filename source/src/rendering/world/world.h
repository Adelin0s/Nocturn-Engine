// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin                                                                                      
//   @ Create Time: 05-06-2022 6:34 PM                                                                                                                                                
//   @ Contact: cucorianu.adelin@protonmail.com                                                                                                                          
//   @ Modified time: 23-08-2022 10:34 PM                                                                                                                                    
//   @ Description:                                                                                                                                                                                
// =====================================================================

#ifndef WORLD_H
#define WORLD_H

#include <memory>

#include "application/config/config.hpp"
#include "rendering/components/entity/player.h"

#include "core/async/task.h"
#include "core/physics/physics.h"

#include "rendering/components/entity/camera.h"
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

		// cant copy
		World( const World & ) = delete;
		World( World && )      = delete;

		// cant move
		World &operator=( const World & ) = delete;
		World &operator=( World && )      = delete;

		void Init( );
		void Update( double dt );
		void Free( );

		~World( ) noexcept = default;

	private:
		ChunkRendering                     m_chunkRender;
		std::unique_ptr< SkyboxRendering > m_skyboxRender;
		std::unique_ptr< ChunkManager >    m_chunkManager;
		std::unique_ptr< TaskSystem >      m_taskSystem;
	};
} // namespace Nocturn

#endif
