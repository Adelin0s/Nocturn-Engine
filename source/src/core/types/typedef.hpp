/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 07-09-2021 11:50:00                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 28-01-2022 15:31:16                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#include <array>

#include "core/math/glm.hpp"

namespace Nocturn
{
	class ChunkSection;

	using int8	 = int8_t;
	using uint8	 = uint8_t;
	using uint16 = uint16_t;
	using int16	 = int16_t;
	using uint32 = uint32_t;
	using int32	 = int32_t;
	using uint64 = uint64_t;
	using int64	 = int64_t;

	using BlockId_t	 = int8_t;
	using Chunk_t	 = glm::ivec3;
	using Block_t	 = glm::ivec3;
	using Vertices_t = std::array< float, 12 >;
	using Textures_t = std::array< float, 8 >;

	using vec2	= glm::vec2;
	using vec3	= glm::vec3;
	using ivec2 = glm::ivec2;
	using ivec3 = glm::ivec3;
} // namespace Nocturn