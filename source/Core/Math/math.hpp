#ifndef MATH_H
#define MATH_H

#include <cstdlib>

#include "core/types/typedef.hpp"
#include "core/components/constants.hpp"

namespace Nocturn::Math
{
	template< typename T >
	constexpr uint32 GetRandom( ) noexcept
	{
		return std::rand( );
	}

	template< typename T >
	constexpr T GetRandom( const T min, const T max ) noexcept
	{
		return std::rand( ) % ( max - min + 1 ) + min;
	}

	template< typename TType > requires( std::is_same_v< TType, float > || std::is_same_v< TType, vec2 > || std::is_same_v< TType, vec3 > || std::is_same_v< TType, vec4 > )
	static constexpr bool Compare( const TType v1, TType v2 )
	{
		constexpr float epsilon = std::numeric_limits< float >::epsilon( );
		if constexpr( std::is_same_v< TType, float > )
		{
			return abs( v1 - v2 ) <= epsilon * std::max( 1.0f, std::max( abs( v1 ), abs( v2 ) ) );
		}
		if constexpr( std::is_same_v< TType, vec2 > )
		{
			return Compare( v1.x, v2.x ) && Compare( v1.y, v2.y );
		}
		if constexpr( std::is_same_v< TType, vec3 > )
		{
			return Compare( v1.x, v2.x ) && Compare( v1.y, v2.y ) && Compare( v1.z, v2.z );
		}
		if constexpr( std::is_same_v< TType, vec4 > )
		{
			return Compare( v1.x, v2.x ) && Compare( v1.y, v2.y ) && Compare( v1.z, v2.z ) && Compare( v1.w, v2.w );
		}
	}

	static ivec2 ToChunkCoords( const vec3 &WorldCoords )
	{
		ivec2 chunkCoords = {WorldCoords.x, WorldCoords.z};
		chunkCoords[ 0 ]  = chunkCoords[ 0 ] / CChunkX;
		chunkCoords[ 1 ]  = chunkCoords[ 1 ] / CChunkZ;

		return chunkCoords;
	}

	static vec3 WorldCoordsToChunkCoords(const vec3& WorldCoords)
	{
		return ivec3(WorldCoords) % ivec3(CChunkX, CChunkY, CChunkZ);
	}

	// TODO: Review here -- need it?
	static ivec3 ToBlockCoords( const vec3 &worldCoords )
	{
		ivec3 chunkCoords = glm::round( worldCoords );
		chunkCoords[ 0 ]  = chunkCoords[ 0 ] % CChunkX;
		chunkCoords[ 1 ]  = chunkCoords[ 1 ] % CChunkY;
		chunkCoords[ 2 ]  = chunkCoords[ 2 ] % CChunkZ;

		return chunkCoords;
	}

	// TODO: Review here -- need it?
	static ivec3 ToBlockCoords( const int x, const int y, const int z )
	{
		ivec3 chunkCoords = { x, y, z };
		return ToBlockCoords( { x, y, z } );
	}
} // namespace Nocturn::Math
#endif