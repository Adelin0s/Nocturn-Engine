#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "core/types/typedef.hpp"

namespace Nocturn::Constants
{
	constexpr int32 CChunkSide	= 16;
	constexpr int32 CChunkX		= 16;
	constexpr int32 CChunkY		= 256;
	constexpr int32 CChunkZ		= 16;
	constexpr int32 CChunkBase	= CChunkX * CChunkZ;
	constexpr int32 CChunkSize	= CChunkX * CChunkY * CChunkZ;
	constexpr int32 CWaterLevel = 64;
}

#endif 