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
		NChunkRenderer() noexcept = default;

		/** Cant copy. */
		NChunkRenderer(const NChunkRenderer& ChunkRendererComponent) = delete;
		NChunkRenderer& operator=(const NChunkRenderer& ChunkRendererComponent) = delete;

		/** Cant move. */
		NChunkRenderer(NChunkRenderer&& ChunkRendererComponent) = delete;
		NChunkRenderer& operator=(NChunkRenderer&& ChunkRendererComponent) = delete;

		bool Initialize() override;

		void Render(const NCameraComponent* CameraComponent) override;

		bool HasRendererTag(const std::string& RendererTagIn) override;

		void Add(const RenderInfo& RenderInfo);

		NODISCARD size_t Size() const noexcept;

		~NChunkRenderer() noexcept override = default;

		friend class NMasterRenderer;

	private:
		/** Attach ChunkManager to be able to communicate. */
		void AttachRenderContext(const NChunkManager* ChunkManager) noexcept;

	private:
		NChunkManager* ChunkManager;

		std::vector< RenderInfo > ChunksRenderInfo;

		UniquePtr< NShader > Shader;

		UniquePtr< NShader > PhongShader;

		UniquePtr< NTextureAtlas > Texture;

		UniquePtr< FChunkManagerRenderContext > ChunkManagerRenderContext;
	};
} // namespace Nocturn
#endif