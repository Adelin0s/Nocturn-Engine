#ifndef BLOCK_SECTION_H
#define BLOCK_SECTION_H

#include "core/types/typedef.hpp"

#include "rendering/data/mesh.hpp"
#include "rendering/data/model.h"

namespace Nocturn::rendering
{
	enum class RenderType : uint8
	{
		Line = 0,
		Triangle
	};

	class BlockSection
	{
	public:
		BlockSection( ) noexcept = default;

		BlockSection( ivec3 &position );
		BlockSection( const int32 px, const int32 py, const int32 pz );

		// cant copy
		BlockSection( const BlockSection & ) = delete;
		BlockSection &operator=( const BlockSection & ) = delete;

		// cant move
		BlockSection( BlockSection && ) noexcept = delete;
		BlockSection &operator=( BlockSection && ) noexcept = delete;

		void Update( );
		void Render( );
		void LoadBufferData( );

		~BlockSection( ) noexcept = default;

	private:
		Mesh  m_mesh;
		Model m_model;

		union u
		{
			int32 px, py, pz;
			ivec3 m_pos;
		};
	};
} // namespace Nocturn::rendering
#endif
