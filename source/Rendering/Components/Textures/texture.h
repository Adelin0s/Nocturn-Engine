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

namespace Nocturn
{
	class INTexture
	{
	public:
		virtual void Load( )   = 0;
		virtual void Bind( ) const = 0;
		virtual void Unbind( ) const = 0;

		virtual ~INTexture( ) noexcept = default;
	};

	class NTexture /*: public INTexture*/
	{
	public:
		NTexture( ) noexcept = default;
		NTexture( const std::string& TexturePath );
		NTexture( const NTexture& smth ) = default;
		NTexture( NTexture&& smth ) = delete;

		NTexture& operator=( const NTexture& smth ) = delete;
		NTexture& operator=( NTexture&& smth ) = delete;

		void Init( );
		void SetPath( const std::string& path ) noexcept;
		void Bind( ) const noexcept;
		void Unbind( ) const noexcept;

		~NTexture( ) noexcept;

	protected:
		uint32_t	TextureId;
		std::string Path;

	private:
		void Generate( );
		void Cleanup( );
	};
} // namespace Nocturn
#endif