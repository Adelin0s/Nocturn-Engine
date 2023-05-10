#include "rendering/renderer/chunkrenderer.h"

#include "Context/Components/CameraComponent.h"
#include "rendering/world/chunk/chunkmanager.h"

namespace Nocturn
{
	bool NChunkRenderer::Initialize()
	{
		Shader = std::make_unique< NShader >("block.vs", "block.fs");
		AssertInfo(Shader != nullptr, "Failed to allocate memory for Shader!");

		Shader->Init();
		Texture = std::make_unique< NTextureAtlas >("block/default_pack.png");
		AssertInfo(Texture != nullptr, "Failed to allocate memory for Texture!");

		PhongShader = std::make_unique< NShader >("light.vs", "light.fs");
		PhongShader->Init();

		RendererTag = "ChunkRenderer";

		return true;
	}

	void NChunkRenderer::Add(const RenderInfo& RenderInfo)
	{
		ChunksRenderInfo.emplace_back(RenderInfo);
	}

	size_t NChunkRenderer::Size() const noexcept
	{
		return ChunksRenderInfo.size();
	}

	void NChunkRenderer::AttachRenderContext(const NChunkManager* ChunkManager) noexcept
	{
		ChunkManagerRenderContext = std::make_unique< FChunkManagerRenderContext >(ChunkManager);
		AssertInfo(ChunkManagerRenderContext != nullptr, "Failed to allocate memory for ChunkManagerRenderContext");
	}

	void NChunkRenderer::Render(const NCameraComponent* CameraComponent)
	{
		auto& MapChunks = ChunkManagerRenderContext->GetChunkMap();
		if (!MapChunks.empty())
		for( const auto& [ position, chunk ] : MapChunks )
		{
			if( MapChunks.at(position).ShouldToRender() )
			{
				const auto maxy	   = chunk.GetChunkMaxY();
				const auto minView = vec3(position[ 0 ] * Constants::CChunkX, maxy, position[ 1 ] * Constants::CChunkZ);
				// if( frustum.IsBoxVisible( minView, minView + vec3( 16.0f ) ) )
				{
					// auto renderInfo = second.getRenderInfo( );
					Add(chunk.GetRenderInfo());
				}
			}
		}
		std::cout << "Size-rendered:" << Size() << '\n';

		if( ChunksRenderInfo.empty() )
		{
			LogWarning("Empty batch renderer!");
			return;
		}

		Texture->Bind();
		Shader->Bind();
		Shader->SetViewMatrix(CameraComponent->GetViewMatrix());
		Shader->SetProjectionMatrix(CameraComponent->GetProjectionMatrix());

		for( const auto& ChunkBatch : ChunksRenderInfo )
		{
			GL::BindVao(ChunkBatch.vao);
			GL::DrawElements(ChunkBatch.indicesCount);
		}
		GL::BindVao(0);
		Shader->Unbind();
		ChunksRenderInfo.clear();
	}

	bool NChunkRenderer::HasRendererTag(const std::string& RendererTagIn)
	{
		return RendererTag == RendererTagIn;
	}
} // namespace Nocturn