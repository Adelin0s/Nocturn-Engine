// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin                                                                                      
//   @ Create Time: 25-10-2021 6:34 PM                                                                                                                                                
//   @ Contact: cucorianu.adelin@protonmail.com                                                                                                                          
//   @ Modified time: 23-08-2022 9:49 PM                                                                                                                                    
//   @ Description:                                                                                                                                                                                
// =====================================================================

#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include "MasterRenderer.h"
#include "core/GL/GLFunctions.h"
#include "core/math/frustum.h"

#include "rendering/components/shaders/shader.h"
#include "rendering/world/block/blockdatabase.h"
#include "rendering/renderer/IRenderer.h"
#include "rendering/world/chunk/chunkmanager.h"

namespace Nocturn
{
	/** Forward declares. */
	struct RenderInfo;
	struct FChunkManagerRenderContext;

	class NChunkRenderer : public INRenderer
	{
	public:
		/** Default constructor. */
		NChunkRenderer() noexcept = default;

		/** Cant copy. */
		NChunkRenderer(const NChunkRenderer& ChunkRendererComponent) = delete;
		NChunkRenderer& operator=(const NChunkRenderer& ChunkRendererComponent) = delete;

		/** Cant move. */
		NChunkRenderer(NChunkRenderer&& ChunkRendererComponent) = delete;
		NChunkRenderer& operator=(NChunkRenderer&& ChunkRendererComponent) = delete;

		/**
		 * @brief Initializes the chunk renderer.
		 * @return True if initialization is successful, false otherwise.
		 */
		bool Initialize() override;

		/**
		 * @brief Checks if the renderer has a specific renderer tag.
		 * @param RendererTagIn The renderer tag to check.
		 * @return True if the renderer has the specified tag, false otherwise.
		 */
		bool HasRendererTag(const std::string& RendererTagIn) override;

		/**
		 * @brief Reloads the shaders used by the chunk renderer.
		 */
		void ReloadShaders() override;

		/**
		 * @brief Renders the scene using the specified camera component.
		 * @param CameraComponent The camera component to use for rendering.
		 * @param bShouldReloadShaders Flag indicating whether the shaders should be reloaded before rendering.
		 */
		void Render(const NCameraComponent* CameraComponent, bool bShouldReloadShaders = false) override;

		/**
		 * @brief Adds a chunk to the chunk renderer's render list.
		 * @param RenderInfo The render information of the chunk to add.
		 */
		void Add(const RenderInfo& RenderInfo);

		/**
		 * @brief Returns the size of the chunk renderer's render list.
		 * @return The size of the render list.
		 */
		NODISCARD size_t Size() const noexcept;

		/** Default destructor. */
		~NChunkRenderer() noexcept override = default;

		friend class NMasterRenderer;

	private:
		/** Attach ChunkManager to be able to communicate. */
		void AttachRenderContext(const NChunkManager* ChunkManager) noexcept;

	private:
		/** Pointer to the chunk manager for communication */
		NChunkManager* ChunkManager;

		/** Render information of the chunks to be rendered */
		std::vector<RenderInfo> ChunksRenderInfo;

		/** Shader used for chunk rendering */
		UniquePtr<NShader> Shader;

		/** Phong shader used for chunk rendering */
		UniquePtr<NShader> PhongShader;

		/** Texture atlas used for chunk rendering */
		UniquePtr<NTextureAtlas> Texture;

		/** Render context for the chunk manager */
		UniquePtr<FChunkManagerRenderContext> ChunkManagerRenderContext;
	};
} // namespace Nocturn
#endif