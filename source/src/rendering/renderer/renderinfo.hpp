/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 08-11-2021 22:13:59                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 08-11-2021 23:58:22                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef RENDER_INFO_HPP
#define RENDER_INFO_HPP

#include <cstdint>

namespace Nocturn::rendering
{
    struct RenderInfo
    {
        uint32_t indicesCount = 0;
        uint32_t vao = 0;

        inline void reset()
        {
            vao = 0;
        }
    };
}

#endif 