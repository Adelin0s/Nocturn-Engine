#pragma once

#include "Rendering/Renderer/IRenderer.h"
#include "Core/core.h"

namespace Nocturn
{
	namespace Concepts
	{
		template<typename TCurrentClass>
		concept DerivedFromRenderer = requires(TCurrentClass CurrentClass)
		{
			std::is_base_of_v<INRenderer, TCurrentClass>;
		};
	}

	class NMasterRenderer
	{
	public:
		NMasterRenderer() noexcept = default;

		/** Cant copy. */
		NMasterRenderer(const NMasterRenderer& MasterRenderer) = delete;
		NMasterRenderer(NMasterRenderer&& MasterRenderer) = delete;

		/** Cant move. */
		NMasterRenderer& operator=(const NMasterRenderer& MasterRenderer) = delete;
		NMasterRenderer& operator=(NMasterRenderer&& MasterRenderer) = delete;

		~NMasterRenderer() noexcept = default;

		/** Initialize MasterRender. */
		bool Initialize(const class NWorld* World);

		/** Render MasterRender. */
		void Render(const NCameraComponent* CameraComponent) const;

		/** Get the RendererComponent with the RendererTag.
		 * @param RendererTag The name of the RendererComponent that MasterRenderer owns
		 * @return Component of the Actor for succes and nullptr in case of failure
		 */
		template< Concepts::DerivedFromRenderer TRendererComponent >
		SharedPtr< TRendererComponent > GetRendererComponentByTag(const std::string& RendererTag) const noexcept
		{
			for( auto& Component : RendererComponents )
			{
				if( Component->HasRendererTag(RendererTag) )
				{
					return std::dynamic_pointer_cast< TRendererComponent >(Component);
				}
			}

			return nullptr;
		}

	private:
		/** Add a new RendererComponent to MasterRenderer. */
		void AddRendererComponent(const SharedPtr< INRenderer >& NewRendererComponent) noexcept;

	public:
		/** Vector with all renderer components from MasterRenderer. */
		std::vector< SharedPtr< INRenderer > > RendererComponents;

		/** Pointer to the ChunkManager. */
		class NChunkManager* ChunkManager;
	};
}
