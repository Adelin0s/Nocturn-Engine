#include "rendering/components/textures/texturecube.h"

namespace Nocturn::rendering
{
	TextureCube::~TextureCube( ) noexcept
	{
		cleanup( );
	}

	void TextureCube::generate( )
	{
		glGenTextures( 1, &m_id );
	}

	void TextureCube::bind( )
	{
		glBindTexture( GL_TEXTURE_CUBE_MAP, m_id );
	}

	void TextureCube::loadCubemap( const std::string &textureType )
	{
		generate( );
		bind( );

		const std::string path = Config::CDirTextures + textureType + '/';

		int width, height, nrChannels;
		for( uint32_t i = 0; i < 6; ++i )
		{
			unsigned char *data = stbi_load( ( path + m_faces[ i ] ).c_str( ), &width, &height, &nrChannels, 0 );

			if( nullptr != data )
			{
				GLenum format = 0;
				if( nrChannels == 1 )
					format = GL_RED;
				else if( nrChannels == 3 )
					format = GL_RGB;
				else if( nrChannels == 4 )
					format = GL_RGBA;

				glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data );
				stbi_image_free( data );
			}
			else
			{
				std::cerr << "ERROR-texturecube: Cubemap texture failed to load at path: " << path[ i ] << '\n';
				stbi_image_free( data );
			}
		}

		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT );

		unbind( );
	}

	void TextureCube::unbind( )
	{
		glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
	}

	void TextureCube::setFaces( const std::vector< std::string > &faces ) noexcept
	{
		m_faces = faces;
	}

	void TextureCube::setFace( const std::string &face ) noexcept
	{
		m_faces.push_back( face );
	}

	void TextureCube::printFaces( const uint32_t index ) const
	{
		std::cout << m_faces[ index ] << '\n';
	}

	void TextureCube::cleanup( )
	{
		glDeleteTextures( 1, &m_id );
	}
} // namespace Nocturn::rendering