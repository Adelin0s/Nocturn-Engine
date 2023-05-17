#include "rendering/renderer/chunkrenderer.h"

#include "Application/Input/Keyboard.h"
#include "Context/Components/CameraComponent.h"
#include "Rendering/World/Chunk/chunkmanager.h"

namespace Nocturn
{
	bool NChunkRenderer::Initialize()
	{
		Shader = std::make_unique< NShader >("block.vs", "block.fs");
		AssertInfo(Shader != nullptr, "Failed to allocate memory for Shader!");

		Shader->Init();
		Texture = std::make_unique< NTextureAtlas >("block/default_pack.png");
		AssertInfo(Texture != nullptr, "Failed to allocate memory for Texture!");

		RendererTag = "ChunkRenderer";

		return true;
	}

	bool NChunkRenderer::HasRendererTag(const std::string& RendererTagIn)
	{
		return RendererTag == RendererTagIn;
	}

	void NChunkRenderer::ReloadShaders()
	{
		std::cout << "ChunkRenderer has successfully reloaded all shaders!";

		const auto Status = Shader->ReloadShader();
	}

	void NChunkRenderer::Render(const NCameraComponent* CameraComponent, const bool bShouldReloadShaders)
	{
		auto& MapChunks = ChunkManagerRenderContext->GetChunkMap();
		if( !MapChunks.empty() )
			for( const auto& [ position, chunk ] : MapChunks )
			{
				if( MapChunks.at(position).ShouldToRender() )
				{
					const auto maxy	   = chunk.GetChunkMaxY();
					const auto minView = vec3(position[ 0 ] * CChunkX, maxy, position[ 1 ] * CChunkZ);
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

		if( bShouldReloadShaders )
		{
			ReloadShaders();
		}
		
		Shader->Bind();
		Shader->SetVec3("objectColor", vec3(1.0f, 0.5f, 0.31f));
		Shader->SetVec3("lightColor", vec3(1.0f));
		Shader->SetVec3("lightPos", vec3(20.0f, 120.0f, 20.0f));
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
} // namespace Nocturn