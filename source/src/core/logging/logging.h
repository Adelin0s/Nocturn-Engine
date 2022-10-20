#ifndef LOGGING_H
#define LOGGING_H

#include "core/types/typedef.hpp"

namespace Nocturn
{
	template< typename... TType >
	void log( const char* format, TType... args )
	{
		if constexpr( std::is_same_v< TType..., vec1 > || std::is_same_v< TType..., ivec1 > )
		{
			printf( format, args.x... );
		}
		else if constexpr( std::is_same_v< TType..., vec2 > || std::is_same_v< TType..., ivec2 > )
		{
			printf( format, args.x..., args.y... );
		}
		else if constexpr( std::is_same_v< TType..., vec3 > || std::is_same_v< TType..., ivec3 > )
		{
			printf( format, args.x..., args.y..., args.z... );
		}
		else if constexpr( std::is_same_v< TType..., vec4 > || std::is_same_v< TType..., ivec4 > )
		{
			printf( format, args.x..., args.y..., args.z..., args.w... );
		}
		else
		{
			printf( format, args... );
		}
	}
}

#endif