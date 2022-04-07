/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 08-10-2021 15:56:36                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 19-12-2021 15:51:00                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef BLOCK_ID_HPP
#define BLOCK_ID_HPP

#include <cstdint>
#include "core/types/typedef.hpp"

namespace Nocturn::rendering
{
    enum class BlockId : BlockId_t
    {
        Air = 0,
        Grass = 1,
        Dirt = 2,
        Stone = 3,
        OakBark = 4,
        OakLeaf = 5,
        Sand = 6,
        Water = 7,
        Cactus = 8,
        Rose = 9,
        TallGrass = 10,
        DeadShrub = 11,
        END
    };
}
#endif