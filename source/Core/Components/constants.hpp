#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "core/types/typedef.hpp"

namespace Nocturn
{
	constexpr int32 CChunkSide	  = 16;
	constexpr int32 CChunkX		  = 16;
	constexpr int32 CChunkY		  = 256;
	constexpr int32 CChunkZ		  = 16;
	constexpr int32 CChunkRadius  = 8;
	constexpr ivec3 CChunkSize	  = { 16, 256, 16 };
	constexpr int32 CChunkMaxSize = CChunkX * CChunkY * CChunkZ;
	constexpr int32 CChunkBase	  = CChunkX * CChunkZ;
	constexpr int32 CWaterLevel	  = 64;

	struct FINormals2
	{
		static constexpr ivec2 Up	 = ivec2(1, 0);
		static constexpr ivec2 Down	 = ivec2(-1, 0);
		static constexpr ivec2 Left	 = ivec2(0, -1);
		static constexpr ivec2 Right = ivec2(0, 1);

		static constexpr std::array< glm::ivec2, 4 > CardinalDirections = 
		{
			Up,
			Down,
			Left,
			Right
		};
	};

	struct FFNormals2
	{
		static constexpr vec2 Up	= vec2(1.0f, 0.0f);
		static constexpr vec2 Down	= vec2(-1.0f, 0.0f);
		static constexpr vec2 Left	= vec2(0.0f, -1.0f);
		static constexpr vec2 Right = vec2(0.0f, 1.0f);

		static constexpr std::array< glm::vec2, 4 > CardinalDirections = 
		{
			Up,
			Down,
			Left,
			Right
		};
	};

	struct FINormals3
	{
		static constexpr glm::ivec3 Up	  = ivec3(0, 1, 0);
		static constexpr glm::ivec3 Down  = ivec3(0, -1, 0);
		static constexpr glm::ivec3 Left  = ivec3(0, 0, -1);
		static constexpr glm::ivec3 Right = ivec3(0, 0, 1);
		static constexpr glm::ivec3 Front = ivec3(1, 0, 0);
		static constexpr glm::ivec3 Back  = ivec3(-1, 0, 0);

		static constexpr std::array< ivec3, 6 > CardinalDirections = 
		{
			Up,
			Down,
			Left,
			Right,
			Front,
			Back
		};

		static constexpr std::array< ivec3, 4 > CardinalDirectionsXZ = 
		{
			Left,
			Right,
			Front,
			Back
		};
	};

	struct FFNormals3
	{
		static constexpr glm::vec3 Up	 = vec3(0.0f, 1.0f, 0.0f);
		static constexpr glm::vec3 Down	 = vec3(0.0f, -1.0f, 0.0f);
		static constexpr glm::vec3 Left	 = vec3(0.0f, 0.0f, -1.0f);
		static constexpr glm::vec3 Right = vec3(0.0f, 0.0f, 1.0f);
		static constexpr glm::vec3 Front = vec3(1.0f, 0.0f, 0.0f);
		static constexpr glm::vec3 Back	 = vec3(-1.0f, 0.0f, 0.0f);

		static constexpr std::array< vec3, 6 > CardinalDirections = 
		{
			Up,
			Down,
			Left,
			Right,
			Front,
			Back
		};
	};
} // namespace Nocturn

#endif