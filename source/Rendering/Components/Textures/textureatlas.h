#ifndef TEXTURE_ATLAS
#define TEXTURE_ATLAS

#include <array>

#include <glm/glm.hpp>

#include "rendering/components/textures/texture.h"

namespace Nocturn
{
	class NTextureAtlas: public NTexture
	{
	public:
		NTextureAtlas( ) noexcept;
		NTextureAtlas( const std::string &TexturePath );

		static std::array< float, 8 > GetTexture( const glm::vec2 &Coords );
		void Init( );
		void Init( const std::string& TexturePath );

	private:
		static uint32_t ImageSize;
		static uint32_t IndividualImageSize;
	};
} // namespace Nocturn::rendering
#endif