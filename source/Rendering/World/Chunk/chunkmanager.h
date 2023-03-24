// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin                                                                                      
//   @ Create Time: 11-10-2021 6:34 PM                                                                                                                                                
//   @ Contact: cucorianu.adelin@protonmail.com                                                                                                                          
//   @ Modified time: 24-08-2022 11:45 PM                                                                                                                                    
//   @ Description:                                                                                                                                                                                
// =====================================================================

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
#include "core/types/typedef.hpp"

#include "rendering/components/entity/camera.h"
#include "rendering/renderer/chunkrenderer.h"
#include "rendering/world/chunk/chunksection.h"

namespace Nocturn::rendering
{
	using ChunkMap = std::unordered_map< vec2, ChunkSection >;

	class ChunkManager
	{
	public:
		ChunkManager( ) noexcept = delete;
		explicit ChunkManager( TaskSystem &taskSystem ) noexcept;
		ChunkManager( const ChunkManager &chunk ) = delete;
		ChunkManager( ChunkManager &&chunk )      = delete;

		ChunkManager operator=( const ChunkManager &chunk ) = delete;
		ChunkManager operator=( ChunkManager &&chunk )      = delete;

		const ChunkSection &operator[]( const ivec2 &index ) noexcept;

		ChunkSection &GetChunk( const vec3 &worldPosition ) noexcept;
		ChunkSection &GetChunk( const ivec2 &chunkPosition ) noexcept;
		NODISCARD Block GetBlock( const vec3 &worldPosition ) noexcept;

		void SetBlock( BlockId blockId, const vec3 &worldPosition) noexcept;

		void GenerateChunkMesh( const ivec2 &chunkPosition ) noexcept;
		void Update( const ivec3 &currentPosition );
		void Render( const NCamera &camera, NFrustum &frustum, Render::ChunkRenderer &chunkRender );

		void GenerateTree( ChunkSection &chunk, int32 px, int32 pymax, int32 pz );

		~ChunkManager( ) noexcept = default;

	private:
		void GenerateNewChunk( ChunkSection &chunk, bool shouldToCreateMesh = false ) noexcept;

		TaskSystem*                             m_pTaskSystem;
		NoiseParams                             m_noiseParams{};
		ivec3                                   m_lastPosition{};
		ChunkMap                                m_mapChunks;
		std::unordered_map< ivec2, bool >       m_hasLoaded;
		std::vector< std::function< void( ) > > m_pendingChunks;
		const uint32                            m_renderDistance;
	};
} // namespace Nocturn::rendering
#endif
