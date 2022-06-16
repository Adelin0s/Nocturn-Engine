#ifndef BLOCK_SECTION_H
#define BLOCK_SECTION_H

#include "core/types/typedef.hpp"
#include "rendering/components/shaders/chunkshader.h"
#include "rendering/components/shaders/skyboxshader.h"
#include "rendering/components/textures/texturecube.h"

#include "rendering/data/model.h"

namespace Nocturn::rendering
{
	enum class RenderType : uint8
	{
		Line = 0,
		Triangle
	};

	// Note that: In order to work thread-safe, the opengl data must be loaded on a single thread
	// See ChunkSection -> LoadBufferData()
	struct position
	{
		int32 x, y, z;
	};

	class BlockSection
	{
	public:
		BlockSection( ) noexcept;

		explicit BlockSection( const ivec3 &position );
		BlockSection( const int32 px, const int32 py, const int32 pz );

		// cant copy
		BlockSection( const BlockSection & ) = delete;
		BlockSection &operator=( const BlockSection & ) = delete;

		// cant move
		BlockSection( BlockSection && ) noexcept = delete;
		BlockSection &operator=( BlockSection && ) noexcept = delete;

		void Init( );
		void Render( const Camera &camera );

		~BlockSection( ) noexcept = default;

	private:
		Model m_model;
		Mesh  m_mesh;

		std::unique_ptr< BlockShader > m_chunkShader;
		TextureCube					   m_textureCube;

		union
		{
			position p;
			ivec3	 pvec3;
		};

		void MakeMesh( );
	};
} // namespace Nocturn::rendering
#endif
