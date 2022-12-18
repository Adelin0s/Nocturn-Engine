#ifndef LOGGING_H
#define LOGGING_H

#include <format>

#include "core/types/typedef.hpp"

namespace Nocturn
{
	/**\brief Function that outputs the formatted input.
	 * \tparam Args type of Args
	 * \param fmt _Fmt_string format
	 * \param args input args
	**/
	template< typename... Args >
	void Log( std::_Fmt_string< Args... > fmt, Args &&...args )
	{
		std::cout << std::format( "[{} : {}]: ", __FILE__, __LINE__ );
		std::cout << std::format( fmt, std::forward< Args >( args )... );
		std::cout << '\n';
	}

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