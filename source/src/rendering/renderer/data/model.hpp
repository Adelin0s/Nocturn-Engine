// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin                                                                                      
//   @ Create Time: 03-08-2021 16:36:33                                                                                                                                                 
//   @ Contact: cucorianu.adelin@protonmail.com                                                                                                                          
//   @ Modified time: 07-10-2022 7:01 PM                                                                                                                                    
//   @ Description:                                                                                                                                                                                
// =====================================================================

#ifndef MODEL_H
#define MODEL_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include "core/core.h"
#include "core/platform/platform.h"
#include "core/types/typedef.hpp"

namespace Nocturn::Render
{
	namespace VertexType
	{
		struct ChunkVertex
		{
			std::vector< float > vertices;
			std::vector< float > textures;
			std::vector< uint32_t > indices;

			void Clear( ) noexcept
			{
				vertices.clear( );
				textures.clear( );
				indices.clear( );
			}

			void Shrink( )
			{
				vertices.shrink_to_fit( );
				textures.shrink_to_fit( );
				indices.shrink_to_fit( );
			}
		};
		
		struct SkyboxVertex
		{
			std::vector< float > vertices;

			void Clear() noexcept
			{
				vertices.clear( );
			}

			void Shrink( )
			{
				vertices.shrink_to_fit( );
			}
		};

		struct GenericVertex
		{
			vec3 start;
			vec3 end;
			float isStart;
			float direction;
			float strokeWidth;
			vec4 color;
		};
	}

	namespace VertexDataType
	{
		using SkyboxDataType = float;
		using ChunkDataType	 = float;
		using GenericDataType = VertexType::GenericVertex;
	}

	struct RenderInfo
	{
		uint32_t indicesCount = 0;
		uint32_t vao = 0;
		uint32_t vbo = 0;
	};

	inline static constexpr uint16 CMaxGenericModelSize = 512;

	template< typename TVertexDataType >
	class Model
	{
	public:
		Model( ) noexcept = default;

		// cant copy
		Model( const Model &model ) = default;
		Model &operator=( const Model &model ) = delete;

		// cant move
		Model( Model &&model ) = delete;
		Model &operator=( Model &&model ) = delete;

		void BindVAO( ) const noexcept
		{
			glBindVertexArray( m_renderInfo.vao );
		}

		template< typename TVertexType > requires( std::is_same_v< TVertexType, VertexType::ChunkVertex > || std::is_same_v< TVertexType, VertexType::SkyboxVertex > || std::is_same_v< TVertexType, VertexType::GenericVertex > )
		void AddVertexData( const TVertexType &mesh)
		{
			if constexpr( std::is_same_v< TVertexType, VertexType::ChunkVertex > )
			{
				GenerateVAO( );

				AddVBO( 3, mesh.vertices );
				AddVBO( 2, mesh.textures );
				AddEBO( mesh.indices );
			}
			else if constexpr( std::is_same_v< TVertexType, VertexType::SkyboxVertex > )
			{
				GenerateVAO( );

				AddVBO( 3, mesh.vertices );
			}
			else if constexpr( std::is_same_v< TVertexType, VertexType::GenericVertex > )
			{
				if( !m_isInitialized )
				{
					InitializeGenericVertex( );
				}
				m_vertexData.push_back( mesh );
				m_renderInfo.indicesCount++;
			}
		}

		NODISCARD const RenderInfo &GetRenderInfo( ) const noexcept
		{
			return m_renderInfo;
		}

		void DeleteData( ) noexcept
		{
			if( m_renderInfo.vao )
				glDeleteVertexArrays( 1, &m_renderInfo.vao );
			if( !m_buffers.empty( ) )
				glDeleteBuffers( static_cast< GLsizei >( m_buffers.size( ) ), m_buffers.data( ) );

			m_buffers.clear( );

			m_vboIndex		 = 0;
			m_renderInfo.vao = 0;
		}

		friend void Render( );

		~Model( ) noexcept = default;

	private:
		std::vector< TVertexDataType > m_vertexData{ };
		RenderInfo m_renderInfo{ };
		std::vector< uint32_t >	m_buffers{ };
		uint32_t m_vboIndex = 0;
		static inline bool m_isInitialized{ false };

	private:
		void InitializeGenericVertex( ) noexcept
		{
			auto &vao = m_renderInfo.vao;
			auto &vbo = m_renderInfo.vbo;
			auto &indicesCount = m_renderInfo.indicesCount;
			glGenVertexArrays( 1, &vao );
			glBindVertexArray( vao );

			glGenBuffers( 1, &vbo );
			glBindBuffer( GL_ARRAY_BUFFER, vbo );
			glBufferData( GL_ARRAY_BUFFER, 512 * sizeof( VertexType::GenericVertex ), nullptr, GL_DYNAMIC_DRAW );

			glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( VertexType::GenericVertex ), reinterpret_cast< void * >( static_cast< int64 >( offsetof( VertexType::GenericVertex, start ) ) ) );
			glEnableVertexAttribArray( 0 );
			glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( VertexType::GenericVertex ), reinterpret_cast< void * >( static_cast< int64 >( offsetof( VertexType::GenericVertex, end ) ) ) );
			glEnableVertexAttribArray( 1 );
			glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, sizeof( VertexType::GenericVertex ), reinterpret_cast< void * >( static_cast< int64 >( offsetof( VertexType::GenericVertex, isStart ) ) ) );
			glEnableVertexAttribArray( 2 );
			glVertexAttribPointer( 3, 1, GL_FLOAT, GL_FALSE, sizeof( VertexType::GenericVertex ), reinterpret_cast< void * >( static_cast< int64 >( offsetof( VertexType::GenericVertex, direction ) ) ) );
			glEnableVertexAttribArray( 3 );
			glVertexAttribPointer( 4, 1, GL_FLOAT, GL_FALSE, sizeof( VertexType::GenericVertex ), reinterpret_cast< void * >( static_cast< int64 >( offsetof( VertexType::GenericVertex, strokeWidth ) ) ) );
			glEnableVertexAttribArray( 4 );
			glVertexAttribPointer( 5, 4, GL_FLOAT, GL_FALSE, sizeof( VertexType::GenericVertex ), reinterpret_cast< void * >( static_cast< int64 >( offsetof( VertexType::GenericVertex, color ) ) ) );
			glEnableVertexAttribArray( 5 );
			indicesCount = 0;
			m_isInitialized = true;
		}

		void GenerateVAO( )
		{
			if( m_renderInfo.vao != 0 )
				DeleteData( );

			glGenVertexArrays( 1, &m_renderInfo.vao );
			glBindVertexArray( m_renderInfo.vao );
		}

		void AddVBO( int size, const std::vector< float > &data )
		{
			uint32_t vbo;
			glGenBuffers( 1, &vbo );
			glBindBuffer( GL_ARRAY_BUFFER, vbo );
			glBufferData( GL_ARRAY_BUFFER, data.size( ) * sizeof( float ), data.data( ), GL_DYNAMIC_DRAW );

			glBindBuffer( GL_ARRAY_BUFFER, vbo );
			glVertexAttribPointer( m_vboIndex, size, GL_FLOAT, GL_FALSE, size * sizeof( float ), ( void * )0 );
			glBindBuffer( GL_ARRAY_BUFFER, 0 );

			glEnableVertexAttribArray( m_vboIndex++ );

			m_buffers.push_back( vbo );
		}

		void AddEBO( const std::vector< uint32_t > &indices )
		{
			m_renderInfo.indicesCount = indices.size( );
			uint32_t ebo;
			glGenBuffers( 1, &ebo );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size( ) * sizeof( uint32_t ), indices.data( ), GL_DYNAMIC_DRAW );
		}
	};
} // namespace Nocturn::rendering
#endif