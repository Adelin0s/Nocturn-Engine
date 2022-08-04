#include "rendering/data/model.h"

#include "application/config/config.hpp"

#include "core/components/constants.hpp"

namespace Nocturn::rendering
{
	void ChunkModel::generateVAO( )
	{
		if( m_renderInfo.vao != 0 )
			deleteData( );

		glGenVertexArrays( 1, &m_renderInfo.vao );
		glBindVertexArray( m_renderInfo.vao );
	}

	void ChunkModel::bindVAO( ) const noexcept
	{
		glBindVertexArray( m_renderInfo.vao );
	}

	void ChunkModel::addData( const Mesh &mesh )
	{
		generateVAO( );

		addVBO( 3, mesh.vertices );
		addVBO( 2, mesh.textures );
		addEBO( mesh.indices );
	}

	void ChunkModel::addVBO( const int size, const std::vector< float > &data )
	{
		uint32_t vbo;
		glGenBuffers( 1, &vbo );
		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glBufferData( GL_ARRAY_BUFFER, data.size( ) * sizeof( float ), data.data( ), GL_DYNAMIC_DRAW );

		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glVertexAttribPointer( m_vboIndex, size, GL_FLOAT, GL_FALSE, size * sizeof( float ), ( void * )0 );

		glEnableVertexAttribArray( m_vboIndex++ );

		m_buffers.push_back( vbo );
	}

	void ChunkModel::addEBO( const std::vector< uint32_t > &indices )
	{
		m_renderInfo.indicesCount = indices.size( );
		uint32_t ebo;
		glGenBuffers( 1, &ebo );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size( ) * sizeof( uint32_t ), indices.data( ), GL_DYNAMIC_DRAW );
	}

	NODISCARD uint32_t ChunkModel::getIndicesCount( ) const noexcept
	{
		return m_renderInfo.indicesCount;
	}

	const RenderInfo &ChunkModel::getRenderInfo( ) const
	{
		return m_renderInfo;
	}

	void ChunkModel::deleteData( )
	{
		if( m_renderInfo.vao )
			glDeleteVertexArrays( 1, &m_renderInfo.vao );
		if( !m_buffers.empty( ) )
			glDeleteBuffers( static_cast< GLsizei >( m_buffers.size( ) ), m_buffers.data( ) );

		m_buffers.clear( );

		m_vboIndex = 0;
		m_renderInfo.vao = 0;
	}

	ChunkModel::~ChunkModel( ) noexcept
	{
		deleteData( );
	}

	void LineModel::Init( const std::initializer_list< AttributeVertex > vertexAttributes )
	{
		m_dataSize = sizeof( RenderVertexLine ) * CMaxLineModelSize;
		// Create the vao
		glGenVertexArrays( 1, &m_vao );
		glBindVertexArray( m_vao );

		glGenBuffers( 1, &m_vbo );

		// Allocate space for vbo
		glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
		glBufferData( GL_ARRAY_BUFFER, m_dataSize, nullptr, GL_DYNAMIC_DRAW );

		// Set up the screen vao2D attributes
		// The position doubles as the texture coordinates so we can use the same floats for that
		int attributeSlot = 0;
		for( const auto &attribute : vertexAttributes )
		{
			const GLenum type = AttributeTypeToGl( attribute.type );
			switch( attribute.type )
			{
				case AttributeType::Float:
					glVertexAttribPointer( attribute.attributeSlot, attribute.numElements, type, GL_FALSE, sizeof( RenderVertexLine ), ( void * )( int64 )attribute.offset );
					break;
				case AttributeType::Int:
				case AttributeType::Uint:
					glVertexAttribIPointer( attribute.attributeSlot, attribute.numElements, type, sizeof( RenderVertexLine ), ( void * )( int64 )attribute.offset );
					break;
			}
			glEnableVertexAttribArray( attribute.attributeSlot );
		}
		m_numVertices = 0;
	}

	void LineModel::AddVertex( const RenderVertexLine &vertex )
	{
		m_data.push_back( vertex );
		m_numVertices++;
	}

	void LineModel::Flush( )
	{
		if( m_numVertices <= 0 )
		{
			return;
		}

		// Draw the 3D screen space stuff
		glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
		glBufferData( GL_ARRAY_BUFFER, m_dataSize, m_data.data( ), GL_DYNAMIC_DRAW );

		glBindVertexArray( m_vao );
		glDrawArrays( GL_TRIANGLES, 0, m_numVertices );

		// Clear the batch
		m_numVertices = 0;
		m_data.clear( );
	}

	NODISCARD GLenum LineModel::AttributeTypeToGl( const AttributeType type ) const
	{
		switch( type )
		{
			case AttributeType::Float:
				return GL_FLOAT;
			case AttributeType::Int:
				return GL_INT;
			case AttributeType::Uint:
				return GL_UNSIGNED_INT;
		}
		return GL_NONE;
	}
} // namespace Nocturn::rendering
