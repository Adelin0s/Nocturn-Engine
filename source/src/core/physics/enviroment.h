/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 30-07-2021 02:15:45                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 02-12-2021 18:24:02                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include <glm/glm.hpp>

namespace Nocturn::core
{

    struct Environment
    {
    public:
        static const glm::vec3 worldUp;
        static const glm::vec3 gravitationalAcceleration;
    };
}
#endif