#pragma once

#include "rendering/components/shaders/shader.h"
#include "Rendering/Components/Textures/texture.h"
#include "Core/Types/rstatus.h"
#include "Rendering/renderer/data/model.hpp"

namespace Nocturn::HUD
{
	constexpr const char* CCrossHairPath = "hud/crosshair.png";
}

namespace Nocturn
{
	class INHUD
	{
	public:
		virtual void Initialize() = 0;
		virtual void Update() = 0;

		virtual ~INHUD() noexcept = default;
	};

	class NHUD: public INHUD
	{
	public:
		NHUD( );

		// cant copy
		NHUD( const NHUD& HUD ) = delete;
		NHUD& operator=( const NHUD& HUD ) = delete;

		// cant move
		NHUD( NHUD&& HUD ) = delete;
		NHUD& operator=( NHUD&& HUD ) = delete;

		/**
		 * \brief Initialize HUD system.
		 */
		void Initialize( ) override;


		/**
		 * \brief Update HUD system over each frame.
		 */
		void Update( ) override;

		~NHUD( ) noexcept override = default;

	private:
		std::unique_ptr< NShader >	Shader;
		std::unique_ptr< NTexture > Texture;
	};
}
