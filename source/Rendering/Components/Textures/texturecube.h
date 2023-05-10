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

#include <glad/glad.h>

#include <stb_image.h>
#include <vector>
#include "application/config/config.hpp"
#include "Core/core.h"

namespace Nocturn
{
	enum class ETextureType : uint8
	{
		Skybox = 0
	};

	class NTextureCube
	{
	public:
		void Generate( );
		void Bind( ) const;
		void Unbind( ) const;

		void LoadCubemap( ETextureType TextureType );

		void SetFaces( const std::vector< std::string > &Faces ) noexcept;
		void SetFace( const std::string &Face ) noexcept;

		void Cleanup( ) const;

		~NTextureCube( ) noexcept;
	private:
		uint32_t				   m_id;
		std::vector< std::string > m_faces;
	};
} // namespace Nocturn

#endif