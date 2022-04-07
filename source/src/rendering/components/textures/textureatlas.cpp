#include "rendering/components/textures/textureatlas.h"

namespace Nocturn::rendering
{
	TextureAtlas::TextureAtlas( const std::string &path ) :
		TextureBasic( path )
	{
		load( );

		m_imageSize			  = 256;
		m_individualImageSize = 16;
	}

	std::array< float, 8 > TextureAtlas::getTexture( const glm::vec2 &coords )
	{
		static const float	 TEX_PER_ROW	 = static_cast< float >( m_imageSize ) / static_cast< float >( m_individualImageSize );
		static const float	 INDIVIDUAL_SIZE = 1.0f / TEX_PER_ROW;
		static const GLfloat INDV_TEX_SIZE	 = 1.0f / TEX_PER_ROW;
		static const float	 PIXEL_SIZE		 = 1.0f / static_cast< float >( m_imageSize );

		GLfloat xMin = ( coords.x * INDV_TEX_SIZE ) + 0.5f * PIXEL_SIZE;
		GLfloat yMin = ( coords.y * INDV_TEX_SIZE ) + 0.5f * PIXEL_SIZE;

		GLfloat xMax = ( xMin + INDV_TEX_SIZE ) - PIXEL_SIZE;
		GLfloat yMax = ( yMin + INDV_TEX_SIZE ) - PIXEL_SIZE;

		return { xMax, yMax, xMin, yMax, xMin, yMin, xMax, yMin };
	}
} // namespace Nocturn::rendering
