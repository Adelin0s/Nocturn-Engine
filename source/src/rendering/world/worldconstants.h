#ifndef WORLD_CONSTANTS
#define WORLD_CONSTANTS

namespace Nocturn
{
	constexpr int CHUNK_SIDE = 16, CHUNK_X = 16, CHUNK_Y = 256, CHUNK_Z = 16,
				  CHUNK_SIZE  = CHUNK_X * CHUNK_Y * CHUNK_Z,
				  WATER_LEVEL = 64;
}

#endif