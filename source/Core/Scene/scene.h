#ifndef SCENE_H
#define SCENE_H

#include "core/types/rstatus.h"
#include "Rendering/World/world.h"

namespace Nocturn
{
	class NScene
	{
	public:
		NScene() noexcept = default;

		void Init( );

		void Update( double DeltaTime );

		void Free( );

	private:
		SharedPtr< NWorld > World;

		SharedPtr< NCharacter > Character;

		SharedPtr< NController > Controller;

		SharedPtr< class NBoxComponent > BoxComponent;
	};
} // namespace Nocturn::Scene

#endif