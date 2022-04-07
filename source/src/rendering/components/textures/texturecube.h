/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 17-10-2021 17:17:20                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 26-10-2021 14:19:09                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef TEXTURE_CUBE_H
#define TEXTURE_CUBE_H

#include <iostream>

#include <stb_image.h>

#include "application/config/config.hpp"

#include "rendering/data/vertexarray.h"

namespace Nocturn::rendering
{
	class TextureCube
	{
	public:
		~TextureCube( ) noexcept;

		void generate( );
		void bind( );
		void unbind( );

		void loadCubemap( const std::string &textureType );

		void setFaces( const std::vector< std::string > &faces ) noexcept;
		void setFace( const std::string &face ) noexcept;
		void printFaces( const uint32_t index ) const;

		void cleanup( );

	private:
		uint32_t				   m_id;
		std::vector< std::string > m_faces;
	};
} // namespace Nocturn::rendering

#endif