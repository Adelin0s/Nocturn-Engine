/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 31-07-2021 14:51:46                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 21-11-2021 00:02:38                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <vector>

namespace Nocturn::rendering
{
	struct Mesh
	{
		std::vector< float >	vertices;
		std::vector< float >	textures;
		std::vector< uint32_t > indices;

		void clear( )
		{
			vertices.clear( );
			textures.clear( );
			indices.clear( );
		}

		void shrink( )
		{
			vertices.shrink_to_fit( );
			textures.shrink_to_fit( );
			indices.shrink_to_fit( );
		}
	};
} // namespace Nocturn::rendering
#endif
