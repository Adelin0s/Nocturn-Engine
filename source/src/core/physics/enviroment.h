// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin                                                                                      
//   @ Create Time: 09-03-2022 11:23 AM                                                                                                                                                
//   @ Contact: cucorianu.adelin@protonmail.com                                                                                                                          
//   @ Modified time: 22-08-2022 10:22 PM                                                                                                                                    
//   @ Description:                                                                                                                                                                                
// =====================================================================

#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include <glm/glm.hpp>

namespace Nocturn::core
{
	struct Environment
	{
		static const glm::vec3 worldUp;
		static const glm::vec3 gravitationalAcceleration;
	};
}
#endif
