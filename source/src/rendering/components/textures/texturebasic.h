/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 22-04-2021 11:32:39                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 01-11-2021 22:46:17                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef TEXTURE_BASIC_H
#define TEXTURE_BASIC_H

#include <glad/glad.h>

#include <iostream>
#include <string>

#include <stb_image.h>
#include "application/config/config.hpp"

namespace Nocturn::rendering
{
	class TextureBasic
	{
	public:
		TextureBasic( ) noexcept = default;
		TextureBasic( const std::string &path );
		TextureBasic( const TextureBasic &smth ) = delete;
		TextureBasic( TextureBasic &&smth )		 = delete;

		TextureBasic &operator=( const TextureBasic &smth ) = delete;
		TextureBasic &operator=( TextureBasic &&smth ) = delete;

		void load( );
		void setPath( const std::string &path ) noexcept;
		void bind( ) const noexcept;
		void unbind( ) const noexcept;

		~TextureBasic( ) noexcept;

	protected:
		uint32_t	m_id;
		std::string m_path;

	private:
		void generate( );
		void cleanup( );
	};
} // namespace Nocturn::rendering
#endif