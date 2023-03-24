#pragma once

#include "Core/core.h"

namespace Nocturn
{
	class INController
	{
	public:
		/** */
		virtual void Initialize() = 0;

		/** Method that is called every frame. */
		virtual void Update() = 0;

		/** Default destructor. */
		virtual ~INController() noexcept = default;
	};
} // namespace Nocturn