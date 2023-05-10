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

#include "Core/Core.h"
#include "Core/Async/Task.h"
#include "Core/Math/Noise.h"
#include "Core/Types/Typedef.hpp"
#include "rendering/renderer/chunkrenderer.h"
#include "Rendering/World/Chunk/ChunkSection.h"

namespace Nocturn
{
	// Forward declares
	// TODO: Review here
	class NChunkRenderer;

	using ChunkMap = std::unordered_map< vec2, ChunkSection >;

	class NChunkManager
	{
	public:
		NChunkManager() noexcept = delete;
		explicit NChunkManager(NTaskSystem& taskSystem) noexcept;

		NChunkManager(const NChunkManager& chunk) = delete;
		NChunkManager(NChunkManager&& chunk) = delete;

		NChunkManager operator=(const NChunkManager& chunk) = delete;
		NChunkManager operator=(NChunkManager&& chunk) = delete;

		/** Get chunk from a specific Index.
		 * @param Index Chunk coord for the wanted chunk.
		 */
		const ChunkSection& operator[](const ivec2& Index) const noexcept;

		NODISCARD ChunkSection* GetChunk(const vec3& WorldPosition) noexcept;
		NODISCARD ChunkSection* GetChunk(const ivec2& ChunkPosition) noexcept;
		NODISCARD NBlock GetBlock(const vec3& WorldPosition) noexcept;

		/**
		 * @brief This function set a block depending on BlockId & WorldPosition.
		 * @warning This function is not thread safe!
		 * @param BlockId the id of the block to be set
		 * @param WorldPosition the world position block
		 */
		void SetBlock(EBlockId BlockId, const vec3& WorldPosition) noexcept;

		/**
		 * @brief This function generates the current chunk and its 4 neighbors(left, right, top and bottom). 
		 * The main idea was to generate the current chunk and its neighbors then render only the current chunk.
		 * Whether the current chunk was generated or not(it already exists) it is marked as a renderable chunk.
		 * @TODO Need to update!!! Really? :))
		 * @param ChunkPosition The current chunk's position
		 */
		void GenerateChunkMesh(const ivec2& ChunkPosition) noexcept;

		/** Update function that is called every frame. */
		void Update(double DeltaTime);

		/**
		 * Propagates light from light sources to neighboring blocks.
		 * Uses a breadth-first search algorithm to update the light levels of adjacent blocks,
		 * taking into account block opacity and light attenuation.
		 * 
		 * This function should be called every frame to update the light state of the world.
		 */
		void UpdateBlockLight();

		/** Basic way to generate trees on the world. */
		void GenerateTree(ChunkSection& chunk, int32 px, int32 pymax, int32 pz);

		~NChunkManager() noexcept = default;

		friend struct FChunkManagerRenderContext;
		//friend void NChunkRenderer::Render(const NCameraComponent* CameraComponent);
		// TODO: Decrease the acces of the class
		friend class NChunkRenderer;
	private:
		void GenerateNewChunk(ChunkSection& chunk, bool shouldToCreateMesh = false) noexcept;

		NTaskSystem*						   m_pTaskSystem;
		NoiseParams							   m_noiseParams{};
		ivec3								   m_lastPosition{};
		ChunkMap							   Chunks;
		std::vector< std::function< void() > > m_pendingChunks;
		const uint32						   m_renderDistance;
	};

	struct FChunkManagerRenderContext
	{
	public:
		FChunkManagerRenderContext() noexcept = default;

		explicit FChunkManagerRenderContext(const NChunkManager* ChunkManagerIn) noexcept;

		const ChunkMap& GetChunkMap() const noexcept;

		~FChunkManagerRenderContext() noexcept = default;
	//private:
		const NChunkManager* ChunkManager;
	};
} // namespace Nocturn
#endif
