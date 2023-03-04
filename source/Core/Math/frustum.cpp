#include "frustum.h"

namespace Nocturn
{
	Frustum::Frustum( ) noexcept
	{ }


	Frustum::Frustum( const mat4 &m )
	{
		Update( m );
	}

	void Frustum::Update( const mat4 &m ) noexcept
	{
		const mat4 transposedM = glm::transpose( m );
		m_planes[ Left ]	  = transposedM[ 3 ] + transposedM[ 0 ];
		m_planes[ Right ]	  = transposedM[ 3 ] - transposedM[ 0 ];
		m_planes[ Bottom ]	  = transposedM[ 3 ] + transposedM[ 1 ];
		m_planes[ Top ]		  = transposedM[ 3 ] - transposedM[ 1 ];
		m_planes[ Near ]	  = transposedM[ 3 ] + transposedM[ 2 ];
		m_planes[ Far ]		  = transposedM[ 3 ] - transposedM[ 2 ];

		const vec3 crosses[ Combinations ] = {
			glm::cross( vec3( m_planes[ Left ] ), vec3( m_planes[ Right ] ) ),
			glm::cross( vec3( m_planes[ Left ] ), vec3( m_planes[ Bottom ] ) ),
			glm::cross( vec3( m_planes[ Left ] ), vec3( m_planes[ Top ] ) ),
			glm::cross( vec3( m_planes[ Left ] ), vec3( m_planes[ Near ] ) ),
			glm::cross( vec3( m_planes[ Left ] ), vec3( m_planes[ Far ] ) ),
			glm::cross( vec3( m_planes[ Right ] ), vec3( m_planes[ Bottom ] ) ),
			glm::cross( vec3( m_planes[ Right ] ), vec3( m_planes[ Top ] ) ),
			glm::cross( vec3( m_planes[ Right ] ), vec3( m_planes[ Near ] ) ),
			glm::cross( vec3( m_planes[ Right ] ), vec3( m_planes[ Far ] ) ),
			glm::cross( vec3( m_planes[ Bottom ] ), vec3( m_planes[ Top ] ) ),
			glm::cross( vec3( m_planes[ Bottom ] ), vec3( m_planes[ Near ] ) ),
			glm::cross( vec3( m_planes[ Bottom ] ), vec3( m_planes[ Far ] ) ),
			glm::cross( vec3( m_planes[ Top ] ), vec3( m_planes[ Near ] ) ),
			glm::cross( vec3( m_planes[ Top ] ), vec3( m_planes[ Far ] ) ),
			glm::cross( vec3( m_planes[ Near ] ), vec3( m_planes[ Far ] ) )
		};

		m_points[ 0 ] = Intersection< Left, Bottom, Near >( crosses );
		m_points[ 1 ] = Intersection< Left, Top, Near >( crosses );
		m_points[ 2 ] = Intersection< Right, Bottom, Near >( crosses );
		m_points[ 3 ] = Intersection< Right, Top, Near >( crosses );
		m_points[ 4 ] = Intersection< Left, Bottom, Far >( crosses );
		m_points[ 5 ] = Intersection< Left, Top, Far >( crosses );
		m_points[ 6 ] = Intersection< Right, Bottom, Far >( crosses );
		m_points[ 7 ] = Intersection< Right, Top, Far >( crosses );
	}

	// http://iquilezles.org/www/articles/frustumcorrect/frustumcorrect.htm
	bool Frustum::IsBoxVisible( const vec3 &minp, const vec3 &maxp ) noexcept
	{
		// check box outside/inside of frustum
		for( int i = 0; i < Count; i++ )
		{
			if( ( glm::dot( m_planes[ i ], vec4( minp.x, minp.y, minp.z, 1.0f ) ) < 0.0 ) &&
				( glm::dot( m_planes[ i ], vec4( maxp.x, minp.y, minp.z, 1.0f ) ) < 0.0 ) &&
				( glm::dot( m_planes[ i ], vec4( minp.x, maxp.y, minp.z, 1.0f ) ) < 0.0 ) &&
				( glm::dot( m_planes[ i ], vec4( maxp.x, maxp.y, minp.z, 1.0f ) ) < 0.0 ) &&
				( glm::dot( m_planes[ i ], vec4( minp.x, minp.y, maxp.z, 1.0f ) ) < 0.0 ) &&
				( glm::dot( m_planes[ i ], vec4( maxp.x, minp.y, maxp.z, 1.0f ) ) < 0.0 ) &&
				( glm::dot( m_planes[ i ], vec4( minp.x, maxp.y, maxp.z, 1.0f ) ) < 0.0 ) &&
				( glm::dot( m_planes[ i ], vec4( maxp.x, maxp.y, maxp.z, 1.0f ) ) < 0.0 ) )
			{
				return false;
			}
		}

		// check frustum outside/inside box
		int32 out;
		out = 0;
		for( int i = 0; i < 8; i++ )
			out += ( ( m_points[ i ].x > maxp.x ) ? 1 : 0 );
		if( out == 8 )
			return false;
		out = 0;
		for( int i = 0; i < 8; i++ )
			out += ( ( m_points[ i ].x < minp.x ) ? 1 : 0 );
		if( out == 8 )
			return false;
		out = 0;
		for( int i = 0; i < 8; i++ )
			out += ( ( m_points[ i ].y > maxp.y ) ? 1 : 0 );
		if( out == 8 )
			return false;
		out = 0;
		for( int i = 0; i < 8; i++ )
			out += ( ( m_points[ i ].y < minp.y ) ? 1 : 0 );
		if( out == 8 )
			return false;
		out = 0;
		for( int i = 0; i < 8; i++ )
			out += ( ( m_points[ i ].z > maxp.z ) ? 1 : 0 );
		if( out == 8 )
			return false;
		out = 0;
		for( int i = 0; i < 8; i++ )
			out += ( ( m_points[ i ].z < minp.z ) ? 1 : 0 );
		if( out == 8 )
			return false;

		return true;
	}
} // namespace Nocturn::rendering
