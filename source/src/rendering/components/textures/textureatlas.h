#ifndef TEXTURE_ATLAS
#define TEXTURE_ATLAS

#include <array>

#include <glm/glm.hpp>

#include "rendering/components/textures/texturebasic.h"

namespace Nocturn::rendering
{
	class TextureAtlas: public TextureBasic
	{
	public:
		TextureAtlas( const std::string &path );

		std::array< float, 8 > getTexture( const glm::vec2 &coords );

	private:
		uint32_t m_imageSize;
		uint32_t m_individualImageSize;
	};
} // namespace Nocturn::rendering
#endif