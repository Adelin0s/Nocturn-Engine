// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin                                                                                      
//   @ Create Time: 23-08-2022 7:39 PM                                                                                                                                                
//   @ Contact: cucorianu.adelin@protonmail.com                                                                                                                          
//   @ Modified time: 23-08-2022 7:49 PM                                                                                                                                    
//   @ Description:                                                                                                                                                                                
// =====================================================================

#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "core/types/typedef.hpp"

namespace Nocturn
{
	// I got it from here https://gist.github.com/podgorskiy/e698d18879588ada9014768e3e82a644
	class Frustum
	{
	public:
		Frustum( ) noexcept;
		Frustum( const mat4 &m );

		void Update( const mat4 &m ) noexcept;
		bool IsBoxVisible( const vec3 &minp, const vec3 &maxp ) noexcept;

	private:
		enum Planes
		{
			Left = 0
			,	Right
			,	Bottom
			,	Top
			,	Near
			,	Far
			,	Count
			,	Combinations = Count * ( Count - 1 ) / 2
		};

		template<Planes i, Planes j>
		struct ij2k
		{
			enum { k = i * ( 9 - i ) / 2 + j - 1 };
		};

		template<Planes a, Planes b, Planes c>
		vec3 Intersection( const vec3 *const crosses ) const
		{
			const float D = glm::dot( vec3( m_planes[ a ] ), crosses[ ij2k< b, c >::k ] );
			const vec3  res = mat3( crosses[ ij2k< b, c >::k ], -crosses[ ij2k< a, c >::k ], crosses[ ij2k< a, b >::k ] ) * vec3( m_planes[ a ].w, m_planes[ b ].w, m_planes[ c ].w );
			return res * ( -1.0f / D );
		}

		vec4 m_planes[ Count ];
		vec3 m_points[ 8 ];
	};
}

#endif
