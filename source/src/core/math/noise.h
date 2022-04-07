/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 15-12-2021 21:27:19                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 15-02-2022 21:58:12                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef NOISE_H
#define NOISE_H

#include "core/types/typedef.hpp"

#include "rendering/world/worldconstants.h"

namespace Nocturn
{
	struct NoiseParams
	{
		int32  octaves;
		int32  amplitude;
		int32  smoothness;
		uint32 offset;
		double roughness;
	};

	class Noise
	{
	public:
		Noise( ) noexcept = default;
		Noise( const uint32 seed );
		Noise( const NoiseParams &params, const uint32 seed );
		Noise( const Noise & ) = delete;
		Noise( Noise && )	   = delete;

		Noise &operator=( const Noise & ) = delete;
		Noise &operator=( Noise && ) = delete;

		double getHeight( const int32 x, const int32 z, const int32 chunkX, const int32 chunkZ ) const noexcept;

		~Noise( ) noexcept = default;

	private:
		double getNoise( double x, double y ) const noexcept;
		double interpolate( double a, double b, double x ) const noexcept;
		double noise( double x, double y ) const noexcept;

		uint32		m_seed;
		NoiseParams m_noiseParams;
	};
} // namespace Nocturn

/** DOCS:
 * Rules:
 * Can you imagine what it’s like generating a chunk of these? Follow me:
Generate a Perlin noise (remember, you generate a two-dimensional array of values between 0 and 1), this noise will be used for the entire world (not really but just go with it for now). We’ll call it noise A.
Select a biome based on a new Perlin noise generated, (for example, below 0.5 is meadows and above 0.6 is mountains), let’s call it noise B.
Split A in chunks of 16×16, select the values for your current chunk
Split B in chunks of 16×16, select the values for your current chunk
For each of the values in A (horizontal and vertical, or X and Y) :
Find the altitude, using the previous formula (maximum x value + baseline), or your own
Determine the tile type based on the current biome of B, (if you are generating the tile x = 10, y = 15 of the noise A, you will read the type of biome from B from the tile x = 10, y = 15)
After the tile is filled with either grass, sand or whatever, we need to fill all the way down to Y = 0, using the following rules:
If Y = 0, we create bedrock
If Y < 6, there is a 70% chance of putting bedrock, and 30% of stone
If the distance to top tile is > 10, put stone, otherwise, put dirt.
 */

#endif