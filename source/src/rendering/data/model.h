/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 03-08-2021 16:36:33                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 08-12-2021 16:48:07                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef MODEL_H
#define MODEL_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include "core/platform/platform.h"
#include "core/types/typedef.hpp"
#include "rendering/data/mesh.hpp"

namespace Nocturn::rendering
{
	struct RenderInfo
	{
		uint32_t indicesCount = 0;
		uint32_t vao		  = 0;
	};

	struct RenderVertexLine
	{
		vec3 start;
		vec3 end;
		float	  isStart;
		float	  direction;
		float	  strokeWidth;
		vec4 color;
	};

	enum class AttributeType : uint8
	{
		 Float
		,Int
		,Uint
	};

	struct AttributeVertex
	{
		int			  attributeSlot;
		int			  numElements;
		AttributeType type;
		uint32		  offset;
	};

	constexpr uint32 CMaxLineModelSize = 501;

	class ChunkModel
	{
	public:
		ChunkModel( ) noexcept			= default;
		ChunkModel( const ChunkModel &model ) = default;
		ChunkModel( ChunkModel &&model )		= delete;
		ChunkModel &operator=( const ChunkModel &model ) = delete;
		ChunkModel &operator=( ChunkModel &&model ) = delete;

		void generateVAO( );
		void bindVAO( ) const noexcept;
		void addData( const Mesh &mesh );
		void addVBO( const int size, const std::vector< float > &data );
		void addEBO( const std::vector< uint32_t > &indices );

		NODISCARD uint32_t			getIndicesCount( ) const noexcept;
		NODISCARD const RenderInfo &getRenderInfo( ) const;

		void deleteData( );

		~ChunkModel( ) noexcept;

	private:
		std::vector< uint32_t > m_buffers;
		RenderInfo				m_renderInfo;
		uint32_t				m_vboIndex = 0;
	};

	class LineModel
	{
	public:
		void Init( std::initializer_list< AttributeVertex > vertexAttributes );
		void AddVertex( const RenderVertexLine &vertex );
		void Flush( );

		FORCE_INLINE int32 GetNumVertices( ) const noexcept
		{
			return m_numVertices;
		}
		FORCE_INLINE void  SetNumVertices( const int32 numVertices ) noexcept
		{
			m_numVertices = numVertices;
		}

		NODISCARD GLenum AttributeTypeToGl( AttributeType type ) const;

	private:
		std::vector< RenderVertexLine > m_data;

		uint32							m_vao = 0;
		uint32							m_vbo = 0;
		int32							m_numVertices = 0;
		uint32							m_dataSize = 0;
	};
} // namespace Nocturn::rendering
#endif
