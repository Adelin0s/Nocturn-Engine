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
	const std::string CDirModels		 = "../../assets/models/";
	const std::string CDirShaders		 = "../../assets/shaders/";
	const std::string CDirTextures		 = "../../assets/textures/";
	const std::string CDirBlockStates	 = "../../assets/blockstates/";
	const std::string CDirTexturesSkybox = "../../assets/textures/skybox/";
	const std::string CDirTexturesBlock	 = "../../assets/textures/block/";

	/* Entity Constants */
	constexpr float CFov  = 45.0f;
	constexpr float CNear = 0.1f;
	constexpr float CFar  = 500.0f;

	/* World Constants */
	constexpr uint32_t CLoadDistance = 10;
} // namespace Nocturn::Config

#endif