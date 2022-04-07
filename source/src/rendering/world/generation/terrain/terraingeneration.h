/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 17-12-2021 12:00:15                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 28-01-2022 20:12:51                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef TERRAIN_GENERATION_H
#define TERRAIN_GENERATION_H

#include "core/math/noise.h"
#include "core/types/typedef.hpp"

#include "rendering/world/chunk/chunkmanager.h"

namespace Nocturn::rendering
{
    class TerrainGeneration
    {
    public:
        TerrainGeneration() noexcept = default;
        TerrainGeneration(const int seed);
        TerrainGeneration(const TerrainGeneration&) = delete;
        TerrainGeneration(const TerrainGeneration &&) = delete;

        TerrainGeneration operator=(const TerrainGeneration &) = delete;
        TerrainGeneration operator=(TerrainGeneration &&) = delete;

        void initLocalArea();
        void generateTerrain();

        ~TerrainGeneration() noexcept = default;

    private:
        int32 m_seed;
        NoiseParams m_noiseParams;
        // ChunkManager m_chunk;
    };
}
#endif