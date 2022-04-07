#ifndef MATH_H
#define MATH_H

#include <cstdlib>

#include "core/types/typedef.hpp"

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
} // namespace Nocturn::Math
#endif