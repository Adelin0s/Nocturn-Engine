/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 11-10-2021 14:28:46                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 18-02-2022 19:52:55                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <unordered_map>
#include <vector>

#include "core/async/threadpool.h"
#include "core/math/noise.h"
#include "core/types/constants.h"
#include "core/types/typedef.hpp"

#include "rendering/data/camera.h"
#include "rendering/renderer/chunkrenderer.h"
#include "rendering/world/chunk/chunksection.h"

namespace Nocturn::rendering
{
	using ChunkMap = std::unordered_map< vec2, ChunkSection >;

	enum class ThreadCommand : uint8
	{
		GenerateTerrain = 0
	};

	class ChunkManager
	{
	public:
		ChunkManager( ) noexcept = delete;
		ChunkManager( const Camera &camera ) noexcept;
		ChunkManager( const ChunkManager &chunk ) = delete;
		ChunkManager( ChunkManager &&chunk )	  = delete;

		ChunkManager operator=( const ChunkManager &chunk ) = delete;
		ChunkManager operator=( ChunkManager &&chunk ) = delete;

		void InitInitialChunks( ) noexcept;
		void LoadPendingChunks( const ivec3 &currentPosition );
		void ThreadUpdate( const ivec3 &currentPosition );
		void Render( const Camera &camera, ChunkRendering &chunkRender );

		~ChunkManager( ) noexcept = default;

	private:
		void GenerateNewChunk( ChunkSection &chunk ) const noexcept;

		NoiseParams			 m_noiseParams{ };
		ivec3				 m_lastPosition{ };
		ThreadPool			 m_pool;
		ChunkMap			 m_mapChunks;
		std::vector< ivec2 > m_pendingChunks;
		const uint32		 m_renderDistance;
	};
} // namespace Nocturn::rendering
#endif