#include "blocksection.h"

#include "block.h"
#include "core/GL/GLFunctions.h"
#include "rendering/world/worldconstants.h"

namespace Nocturn::rendering
{
	const std::vector< float > Cvertices = {
		-1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,

		-1.0f,
		-1.0f,
		1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		1.0f,
		-1.0f,
		-1.0f,
		1.0f,
		-1.0f,
		-1.0f,
		1.0f,
		1.0f,
		-1.0f,
		-1.0f,
		1.0f,

		1.0f,
		-1.0f,
		-1.0f,
		1.0f,
		-1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		-1.0f,
		1.0f,
		-1.0f,
		-1.0f,

		-1.0f,
		-1.0f,
		1.0f,
		-1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		-1.0f,
		1.0f,
		-1.0f,
		-1.0f,
		1.0f,

		-1.0f,
		1.0f,
		-1.0f,
		1.0f,
		1.0f,
		-1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		-1.0f,
		1.0f,
		1.0f,
		-1.0f,
		1.0f,
		-1.0f,

		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		1.0f,
		1.0f,
		-1.0f,
		-1.0f,
		1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		-1.0f,
		1.0f,
		1.0f,
		-1.0f,
		1.0f
	};

	BlockSection::BlockSection( ) noexcept :
		m_chunkShader( std::make_unique< BlockShader >( Config::CRayVertexShader, Config::CRayFragmentShader ) )
	{
		m_chunkShader->init( );

		p.x = 0;
		p.y = 60;
		p.z = 0;

		MakeMesh( );
	}

	void BlockSection::Render( const Camera &camera )
	{
		m_chunkShader->activate( );
		m_chunkShader->setProjectionMatrix( camera );
		m_chunkShader->setViewMatrix( camera );

		m_model.bindVAO( );

		glDrawElements( GL_LINES, 36, GL_UNSIGNED_INT, nullptr );
		// GL::drawElements( 36 );
	}

	void BlockSection::MakeMesh( )
	{
		auto &indices  = m_mesh.indices;
		auto &vertices = m_mesh.vertices;

		for( uint32 i = 0, m_index = 0; i < 6; i++, m_index += 4 )
		{
			indices.insert( indices.end( ), { m_index, m_index + 1, m_index + 2, m_index + 2, m_index + 3, m_index } );
		}

		/* we have 4 set of vertices with 3 coords x, y, z  */
		for( uint32_t i = 0, index = 0; i < 4; i++ )
		{
			vertices.push_back( topFace[ index++ ] + p.x );
			vertices.push_back( topFace[ index++ ] + p.y );
			vertices.push_back( topFace[ index++ ] + p.z );
		}
		for( uint32_t i = 0, index = 0; i < 4; i++ )
		{
			vertices.push_back( bottomFace[ index++ ] + p.x );
			vertices.push_back( bottomFace[ index++ ] + p.y );
			vertices.push_back( bottomFace[ index++ ] + p.z );
		}
		for( uint32_t i = 0, index = 0; i < 4; i++ )
		{
			vertices.push_back( frontFace[ index++ ] + p.x );
			vertices.push_back( frontFace[ index++ ] + p.y );
			vertices.push_back( frontFace[ index++ ] + p.z );
		}
		for( uint32_t i = 0, index = 0; i < 4; i++ )
		{
			vertices.push_back( backFace[ index++ ] + p.x );
			vertices.push_back( backFace[ index++ ] + p.y );
			vertices.push_back( backFace[ index++ ] + p.z );
		}
		for( uint32_t i = 0, index = 0; i < 4; i++ )
		{
			vertices.push_back( frontFace[ index++ ] + p.x );
			vertices.push_back( frontFace[ index++ ] + p.y );
			vertices.push_back( frontFace[ index++ ] + p.z );
		}
		for( uint32_t i = 0, index = 0; i < 4; i++ )
		{
			vertices.push_back( leftFace[ index++ ] + p.x );
			vertices.push_back( leftFace[ index++ ] + p.y );
			vertices.push_back( leftFace[ index++ ] + p.z );
		}
		for( uint32_t i = 0, index = 0; i < 4; i++ )
		{
			vertices.push_back( rightFace[ index++ ] + p.x );
			vertices.push_back( rightFace[ index++ ] + p.y );
			vertices.push_back( rightFace[ index++ ] + p.z );
		}

		m_model.generateVAO( );
		m_model.addVBO( 3, vertices );
		m_model.addEBO( indices );
	}

} // namespace Nocturn::rendering