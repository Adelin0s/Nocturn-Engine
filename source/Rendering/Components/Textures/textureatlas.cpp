#include "rendering/components/textures/textureatlas.h"

namespace Nocturn
{
	uint32_t NTextureAtlas::ImageSize = 0;
	uint32_t NTextureAtlas::IndividualImageSize = 0;

	NTextureAtlas::NTextureAtlas( ) noexcept
	:
		NTexture( "block/default_pack.png" )
	{ }

	NTextureAtlas::NTextureAtlas( const std::string &TexturePath )
	:
		NTexture( TexturePath )
	{
		NTexture::Init( );

		ImageSize			= 256;
		IndividualImageSize = 16;
	}
	
	std::array< float, 8 > NTextureAtlas::GetTexture( const glm::vec2 &Coords )
	{
		static const float   TEX_PER_ROW     = static_cast< float >( ImageSize ) / static_cast< float >( NTextureAtlas::IndividualImageSize );
		static const float   INDIVIDUAL_SIZE = 1.0f / TEX_PER_ROW;
		static const GLfloat INDV_TEX_SIZE   = 1.0f / TEX_PER_ROW;
		static const float   PIXEL_SIZE      = 1.0f / static_cast< float >( ImageSize );

		const auto xMin = ( Coords.x * INDV_TEX_SIZE ) + 0.5f * PIXEL_SIZE;
		const auto yMin = ( Coords.y * INDV_TEX_SIZE ) + 0.5f * PIXEL_SIZE;

		const auto xMax = ( xMin + INDV_TEX_SIZE ) - PIXEL_SIZE;
		const auto yMax = ( yMin + INDV_TEX_SIZE ) - PIXEL_SIZE;

		return { xMax, yMax, xMin, yMax, xMin, yMin, xMax, yMin };
	}

	void NTextureAtlas::Init( )
	{
		ImageSize = 256;
		IndividualImageSize = 16;

		NTexture::Init( );
	}

	void NTextureAtlas::Init( const std::string &TexturePath )
	{
		Path = TexturePath;
		ImageSize = 256;
		IndividualImageSize = 16;

		NTexture::Init( );
	}
} // namespace Nocturn
