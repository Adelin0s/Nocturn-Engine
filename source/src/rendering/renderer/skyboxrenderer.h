/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 17-10-2021 17:26:54                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 08-12-2021 23:40:54                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef SKYBOX_RENDERER_H
#define SKYBOX_RENDERER_H

#include "core/GL/GLFunctions.h"

#include "rendering/components/shaders/skyboxshader.h"
#include "rendering/components/textures/texturecube.h"
#include "rendering/data/model.h"

namespace Nocturn::rendering
{
	class SkyboxRendering
	{
	public:
		SkyboxRendering( );
		SkyboxRendering( const SkyboxRendering & ) = delete;
		SkyboxRendering( SkyboxRendering && )	   = delete;

		SkyboxRendering &operator=( const SkyboxRendering & ) = delete;
		SkyboxRendering &operator=( SkyboxRendering && ) = delete;

		void render( const Camera &camera );

		~SkyboxRendering( ) noexcept = default;

	private:
		ChunkModel   m_model;
		SkyboxShader m_skyboxShader;
		TextureCube	 m_textureCube;
	};
} // namespace Nocturn::rendering

#endif