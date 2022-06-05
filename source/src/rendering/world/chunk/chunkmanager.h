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

#include "core/async/task.h"
#include "core/math/noise.h"
#include "core/types/constants.h"
#include "core/types/typedef.hpp"

#include "rendering/data/camera.h"
#include "rendering/renderer/chunkrenderer.h"
#include "rendering/world/chunk/chunksection.h"

namespace Nocturn::rendering
{
	using ChunkMap = std::unordered_map< vec2, ChunkSection >;

	struct AdjacentChunk
	{
		AdjacentChunk( const int32 x, const int32 z ) noexcept;
		AdjacentChunk( const ivec2 &vec ) noexcept;

		ivec2 top;
		ivec2 bottom;
		ivec2 left;
		ivec2 right;
	};

	class ChunkManager
	{
	public:
		ChunkManager( ) noexcept = delete;
		explicit ChunkManager( TaskSystem &taskSystem ) noexcept;
		ChunkManager( const ChunkManager &chunk ) = delete;
		ChunkManager( ChunkManager &&chunk )	  = delete;

		ChunkManager operator=( const ChunkManager &chunk ) = delete;
		ChunkManager operator=( ChunkManager &&chunk ) = delete;

		void LoadPendingChunks( const ivec3 &currentPosition );
		void LoadChunkNeighbors( const ivec2 &chunkPosition ) noexcept;
		void Update( const ivec3 &currentPosition );
		void Render( const Camera &camera, ChunkRendering &chunkRender );

		~ChunkManager( ) noexcept = default;

	private:
		void GenerateNewChunk( ChunkSection &chunk ) const noexcept;

		TaskSystem					   *m_pTaskSystem;
		NoiseParams						  m_noiseParams{ };
		ivec3							  m_lastPosition{ };
		ChunkMap						  m_mapChunks;
		std::unordered_map< ivec2, bool > m_hasLoaded;
		std::vector< ivec2 >			  m_pendingChunks;
		const uint32					  m_renderDistance;
	};
} // namespace Nocturn::rendering
#endif