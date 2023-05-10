#include "Rendering/Renderer/MasterRenderer.h"
#include "Rendering/Renderer/ChunkRenderer.h"
#include "Rendering/Renderer/SkyboxRenderer.h"
#include "Rendering/world/world.h"

namespace Nocturn
{
	bool NMasterRenderer::Initialize(const NWorld* World)
	{
		if( World == nullptr )
		{
			LogError("Invalid World nullptr param!");
			return false;
		}

		const auto SkyboxRenderer = std::make_shared< NSkyboxRenderer >();
		AssertInfo(SkyboxRenderer != nullptr, "Failed to allocate memory for ChunkRenderer");
		SkyboxRenderer->Initialize();
		AddRendererComponent(SkyboxRenderer);

		const auto ChunkRenderer = std::make_shared< NChunkRenderer >();
		AssertInfo(ChunkRenderer != nullptr, "Failed to allocate memory for ChunkRenderer");
		ChunkRenderer->Initialize();
		AddRendererComponent(ChunkRenderer);

		ChunkRenderer->ChunkManager = World->GetChunkManager().get();

		ChunkRenderer->AttachRenderContext(ChunkRenderer->ChunkManager);

		return true;
	}

	void NMasterRenderer::Render(const NCameraComponent* CameraComponent) const
	{
		AssertInfo(CameraComponent != nullptr, "Failed nullptr CameraComponent!")

		bool bShouldLogWarning = true;
		for( const auto& RendererComponent : RendererComponents )
		{
			if( RendererComponent == nullptr ) UNLIKELY
			{
				if( bShouldLogWarning )
				{
					LogWarning("Invalid current Renderer nullptr component!");
					bShouldLogWarning = false;
				}
			}

			RendererComponent->Render(CameraComponent);
		}
	}

	void NMasterRenderer::AddRendererComponent(const SharedPtr< INRenderer >& NewRendererComponent) noexcept
	{
		if( NewRendererComponent == nullptr )
		{
			LogError("Invalid nullptr Component!");
			return;
		}

		RendererComponents.push_back(NewRendererComponent);
	}
} // namespace Nocturn
