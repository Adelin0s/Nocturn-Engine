#include "rendering/data/model.h"

#include "application/config/config.hpp"

#include "rendering/world/worldconstants.h"

#include <iostream>

namespace Nocturn::rendering
{
	void Model::generateVAO( )
	{
		if( m_renderInfo.vao != 0 )
			deleteData( );

		glGenVertexArrays( 1, &m_renderInfo.vao );
		glBindVertexArray( m_renderInfo.vao );
	}

	void Model::bindVAO( ) const noexcept
	{
		glBindVertexArray( m_renderInfo.vao );
	}

	void Model::addData( const Mesh &mesh )
	{
		generateVAO( );

		addVBO( 3, mesh.vertices );
		addVBO( 2, mesh.textures );
		addEBO( mesh.indices );
	}

	void Model::addVBO( const int size, const std::vector< float > &data )
	{
		uint32_t vbo;
		glGenBuffers( 1, &vbo );
		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glBufferData( GL_ARRAY_BUFFER, data.size( ) * sizeof( float ), data.data( ), GL_STATIC_DRAW );

		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glVertexAttribPointer( m_vboIndex, size, GL_FLOAT, GL_FALSE, size * sizeof( float ), ( void * )0 );

		glEnableVertexAttribArray( m_vboIndex++ );

		m_buffers.push_back( vbo );
	}

	void Model::addEBO( const std::vector< uint32_t > &indices )
	{
		m_renderInfo.indicesCount = indices.size( );
		uint32_t ebo;
		glGenBuffers( 1, &ebo );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size( ) * sizeof( uint32_t ), indices.data( ), GL_STATIC_DRAW );
	}

	NODISCARD uint32_t Model::getIndicesCount( ) const noexcept
	{
		return m_renderInfo.indicesCount;
	}

	const RenderInfo &Model::getRenderInfo( ) const
	{
		return m_renderInfo;
	}

	void Model::deleteData( )
	{
		if( m_renderInfo.vao )
			glDeleteVertexArrays( 1, &m_renderInfo.vao );
		if( !m_buffers.empty( ) )
			glDeleteBuffers( static_cast< GLsizei >( m_buffers.size( ) ), m_buffers.data( ) );

		m_buffers.clear( );

		m_vboIndex = 0;
		m_renderInfo.reset( );
	}

	Model::~Model( ) noexcept
	{
		deleteData( );
	}
} // namespace Nocturn::rendering
