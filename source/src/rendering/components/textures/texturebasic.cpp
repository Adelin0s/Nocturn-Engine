#include "rendering/components/textures/texturebasic.h"

namespace Nocturn::rendering
{
	TextureBasic::TextureBasic( const std::string &path ) :
		m_path( path )
	{}

	void TextureBasic::generate( )
	{
		glGenTextures( 1, &m_id );
	}

	void TextureBasic::load( )
	{
		stbi_set_flip_vertically_on_load( false );

		int width, height, nrChannels;

		const std::string path = Config::DIR_TEXTURES_BLOCK + m_path;

		unsigned char *data = stbi_load( path.c_str( ), &width, &height, &nrChannels, 0 );

		GLenum color_mode = GL_RGB;
		switch( nrChannels )
		{
			case 1:
				color_mode = GL_RED;
				break;
			case 4:
				color_mode = GL_RGBA;
				break;
		}

		if( data )
		{
			glGenTextures( 1, &m_id );
			glActiveTexture( GL_TEXTURE0 );
			glBindTexture( GL_TEXTURE_2D, m_id );

			glTexImage2D( GL_TEXTURE_2D, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, data );

			glGenerateMipmap( GL_TEXTURE_2D );

			// Configure the type of algorithm that is use to make the image smaller or bigger
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

			// Configure the way the texture repeats
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1 );

			stbi_image_free( data );
		}
		else
		{
			std::cerr << "ERROR-texturebasic: Failed to loading texture." << std::endl;
		}
	}

	void TextureBasic::bind( ) const noexcept
	{
		glBindTexture( GL_TEXTURE_2D, m_id );
	}

	void TextureBasic::unbind( ) const noexcept
	{
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	void TextureBasic::setPath( const std::string &path ) noexcept
	{
		m_path = path;
	}

	void TextureBasic::cleanup( )
	{
		glDeleteTextures( 1, &m_id );
	}

	TextureBasic::~TextureBasic( ) noexcept
	{
		cleanup( );
	}
} // namespace Nocturn::rendering
