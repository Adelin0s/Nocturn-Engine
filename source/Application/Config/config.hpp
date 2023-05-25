// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin                                                                                      
//   @ Create Time: 22-08-2021 13:41:09                                                                                                                                                
//   @ Contact: cucorianu.adelin@protonmail.com                                                                                                                          
//   @ Modified time: 04-03-2023 9:22 PM                                                                                                                                    
//   @ Description:                                                                                                                                                                                
// =====================================================================

#pragma once

#include <string>
#include <glm/vec3.hpp>

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
	constexpr inline glm::vec3 CDefaultPlayerPosition{10.f, 80.f, 10.f};
} // namespace Nocturn::Config
