#include "rendering/world/generation/terrain/terraingeneration.h"

namespace Nocturn::rendering
{
    TerrainGeneration::TerrainGeneration(const int seed)
    {
        m_noiseParams.octaves = 9;
        m_noiseParams.amplitude = 85;
        m_noiseParams.smoothness = 235;
        m_noiseParams.offset = -20;
        m_noiseParams.roughness = 0.51;
    }

    void TerrainGeneration::initLocalArea()
    {
        
    }

    void TerrainGeneration::generateTerrain()
    {

    }
}