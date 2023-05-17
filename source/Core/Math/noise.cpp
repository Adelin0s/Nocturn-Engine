#include "core/math/noise.h"

#include <cmath>

namespace Nocturn
{
	Noise::Noise( const uint32 seed ) :
		m_seed( seed )
	{
		m_noiseParams.octaves	 = 7;
		m_noiseParams.amplitude	 = 200;
		m_noiseParams.smoothness = 128;
		m_noiseParams.offset	 = 3;
		m_noiseParams.roughness	 = 0.53;
	}

	Noise::Noise( const NoiseParams &params, const uint32 seed ) :
		m_noiseParams( params ),
		m_seed( seed )
	{}

	double Noise::getHeight( const int32 x, const int32 z, const int32 chunkX, const int32 chunkZ ) const noexcept
	{
		const auto newX = ( x + ( chunkX * CChunkX ) );
		const auto newZ = ( z + ( chunkZ * CChunkZ ) );

		auto totalValue = 0.0;

		for( auto a = 0; a < m_noiseParams.octaves - 1; a++ ) // This loops through the octaves.
		{
			const auto frequency = pow( 2.0, a );					  // This increases the frequency with every loop of the octave.
			const auto amplitude = pow( m_noiseParams.roughness, a ); // This decreases the amplitude with every loop of the octave.
			totalValue += noise( ( static_cast< double >( newX ) ) * frequency / m_noiseParams.smoothness, ( static_cast< double >( newZ ) ) * frequency / m_noiseParams.smoothness ) * amplitude;
		}

		const auto val = ( ( ( totalValue / 2.1 ) + 1.2 ) * m_noiseParams.amplitude ) + m_noiseParams.offset;

		return val;
	}

	double Noise::getNoise( double x, double y ) const noexcept
	{
		uint32 n = static_cast< int32 >( x ) + static_cast< int32 >( y ) * 57;
		n += m_seed;
		n				= ( n << 13 ) ^ n;
		const uint32 nn = ( n * ( n * n * 60493 + 19990303 ) + 1376312589 ) & 0x7fffffff;

		return 1.0 - ( static_cast< double >( nn ) / 1073741824.0 );
	}

	double Noise::interpolate( double a, double b, double x ) const noexcept
	{
		const double ft = x * 3.1415927;
		const double f	= ( 1.0 - cos( ft ) ) * 0.5;

		return a * ( 1.0 - f ) + b * f;
	}

	double Noise::noise( const double x, const double y ) const noexcept
	{
		const auto floorx = static_cast< double >( static_cast< int >( x ) ); // This is kinda a cheap way to floor a double integer.
		const auto floory = static_cast< double >( static_cast< int >( y ) );
		double	   s = 0.0, t = 0.0, u = 0.0, v = 0.0; // Integer declaration

		s = getNoise( floorx, floory );
		t = getNoise( floorx + 1, floory );
		u = getNoise( floorx, floory + 1 ); // Get the surrounding pixels to calculate the transition.
		v = getNoise( floorx + 1, floory + 1 );

		const double int1 = interpolate( s, t, x - floorx ); // Interpolate between the values.
		const double int2 = interpolate( u, v, x - floorx ); // Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.

		return interpolate( int1, int2, y - floory ); // Here we use y-floory, to get the 2nd dimension.
	}
} // namespace Nocturn