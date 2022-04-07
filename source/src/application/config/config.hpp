/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 22-08-2021 13:41:09                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 07-12-2021 20:51:44                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

namespace Nocturn::Config
{
	/* Directory Constants */
	const std::string			ROOT_DIR			 = "../../";
	const std::string			DIR_MODELS			 = ROOT_DIR + "assets/models/";
	const std::string			DIR_SHADERS			 = ROOT_DIR + "assets/shaders/";
	const std::string			DIR_TEXTURES		 = ROOT_DIR + "assets/textures/";
	const std::string			DIR_BLOCKSTATES		 = ROOT_DIR + "assets/blockstates/";
	const std::string			DIR_TEXTURES_SKYBOX	 = DIR_TEXTURES + "skybox/";
	const std::string			DIR_TEXTURES_BLOCK	 = DIR_TEXTURES + "block/";
	constexpr const char *const skyboxVertexShader	 = "../../assets/shaders/skybox_vertex.glsl";
	constexpr const char *const skyboxFragmentShader = "../../assets/shaders/skybox_fragment.glsl";
	constexpr const char *const chunkVertexShader	 = "../../assets/shaders/block_vertex.glsl";
	constexpr const char *const chunkFragmentShader	 = "../../assets/shaders/block_fragment.glsl";

	/* Entity Constants */
	constexpr float fov	 = 45.0f;
	constexpr float near = 0.1f;
	constexpr float far	 = 500.0f;

	/* World Constants */
	constexpr uint32_t loadDistance = 10;
} // namespace Nocturn::Config

#endif