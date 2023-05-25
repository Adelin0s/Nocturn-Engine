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
// TODO: Possible circular deps
#include "Rendering/Renderer/Renderer.h"

namespace Nocturn
{
	namespace VertexType
	{
		struct ChunkVertex
		{
			std::vector< float >  vertices;
			std::vector< float >  textures;
			std::vector< uint32 > indices;
			std::vector< int32 >  light;

			void Clear() noexcept
			{
				vertices.clear();
				textures.clear();
				indices.clear();
			}

			void Shrink()
			{
				vertices.shrink_to_fit();
				textures.shrink_to_fit();
				indices.shrink_to_fit();
			}
		};

		struct SkyboxVertex
		{
			std::vector< float > vertices;

			void Clear() noexcept
			{
				vertices.clear();
			}

			void Shrink()
			{
				vertices.shrink_to_fit();
			}
		};

		struct GenericVertex
		{
			vec3  start;
			vec3  end;
			float isStart;
			float direction;
			float strokeWidth;
			vec4  color;
		};
	} // namespace VertexType

	namespace VertexDataType
	{
		using SkyboxDataType  = float;
		using ChunkDataType	  = float;
		using GenericDataType = VertexType::GenericVertex;
	} // namespace VertexDataType

	struct RenderInfo
	{
		uint32_t indicesCount = 0;
		uint32_t vao		  = 0;
		uint32_t vbo		  = 0;
	};

	inline static constexpr uint16 CMaxGenericModelSize = 512;

	namespace Concepts
	{
		template<typename TVertexType>
		concept VertexType = requires(TVertexType VertexType)
		{
			std::is_same_v< TVertexType, VertexType::ChunkVertex > || std::is_same_v< TVertexType, VertexType::SkyboxVertex > || std::is_same_v< TVertexType, VertexType::GenericVertex >;
		};

		template<typename TVertexType>
		concept ChunkType = std::is_same_v< TVertexType, VertexType::ChunkVertex >;
	}

	template< typename TVertexDataType >
	class Model
	{
	public:
		Model() noexcept = default;

		// cant copy
		Model(const Model& Model) = default;
		Model& operator=(const Model& Model) = delete;

		// cant move
		Model(Model&& Model) = delete;
		Model& operator=(Model&& Model) = delete;

		void BindVAO() const noexcept
		{
			glBindVertexArray(m_renderInfo.vao);
		}

		void Unbind() const noexcept
		{
			glBindVertexArray(0);
		}

		template< Concepts::VertexType TVertexType >
		void AddData(const TVertexType& Mesh)
		{
			if constexpr( std::is_same_v< TVertexType, VertexType::ChunkVertex > )
			{
				GenerateVAO();

				AddVBO(3, Mesh.vertices);
				AddVBO(2, Mesh.textures);
				// Add block light data -> BlockLight, BlockSkyLight
				// AddVBO(3, Mesh.light);
				AddEBO(Mesh.indices);
			}
			else if constexpr( std::is_same_v< TVertexType, VertexType::SkyboxVertex > )
			{
				GenerateVAO();

				AddVBO(3, Mesh.vertices);
			}
			else if constexpr( std::is_same_v< TVertexType, VertexType::GenericVertex > )
			{
				if( !m_isInitialized )
				{
					InitializeGenericVertex();
				}
				m_vertexData.push_back(Mesh);
				m_renderInfo.indicesCount++;
			}
		}

		template< Concepts::ChunkType TChunkVertex >
		void ReloadData(const TChunkVertex& Mesh)
		{
			const auto VertexDataSize  = static_cast< GLsizei >(Mesh.vertices.size() * sizeof(float));
			const auto TextureDataSize = static_cast< GLsizei >(Mesh.textures.size() * sizeof(float));
			const auto IndexDataSize   = static_cast< GLsizei >(Mesh.indices.size() * sizeof(uint32));

			glBindVertexArray(m_renderInfo.vao);

			glBindBuffer(GL_ARRAY_BUFFER, m_buffers[ 0 ]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, VertexDataSize, Mesh.vertices.data());

			glBindBuffer(GL_ARRAY_BUFFER, m_buffers[ 1 ]);
			glBufferSubData(GL_ARRAY_BUFFER, VertexDataSize, TextureDataSize, Mesh.textures.data());

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[ 2 ]);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, VertexDataSize + TextureDataSize, IndexDataSize, Mesh.indices.data());

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		NODISCARD const RenderInfo& GetRenderInfo() const noexcept
		{
			return m_renderInfo;
		}

		void DeleteData() noexcept
		{
			if( m_renderInfo.vao )
				glDeleteVertexArrays(1, &m_renderInfo.vao);
			if( !m_buffers.empty() )
				glDeleteBuffers(static_cast< GLsizei >(m_buffers.size()), m_buffers.data());

			m_buffers.clear();

			m_vboIndex		 = 0;
			m_renderInfo.vao = 0;
		}

		friend void Render::Render();

		~Model() noexcept = default;

	private:
		std::vector< TVertexDataType > m_vertexData{};
		RenderInfo					   m_renderInfo{};
		std::vector< uint32_t >		   m_buffers{};
		uint32_t					   m_vboIndex = 0;
		static inline bool			   m_isInitialized{ false };

		void InitializeGenericVertex() noexcept
		{
			auto& vao		   = m_renderInfo.vao;
			auto& vbo		   = m_renderInfo.vbo;
			auto& indicesCount = m_renderInfo.indicesCount;
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, 512 * sizeof(VertexType::GenericVertex), nullptr, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexType::GenericVertex), reinterpret_cast< void* >(static_cast< int64 >(offsetof(VertexType::GenericVertex, start))));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexType::GenericVertex), reinterpret_cast< void* >(static_cast< int64 >(offsetof(VertexType::GenericVertex, end))));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(VertexType::GenericVertex), reinterpret_cast< void* >(static_cast< int64 >(offsetof(VertexType::GenericVertex, isStart))));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(VertexType::GenericVertex), reinterpret_cast< void* >(static_cast< int64 >(offsetof(VertexType::GenericVertex, direction))));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(VertexType::GenericVertex), reinterpret_cast< void* >(static_cast< int64 >(offsetof(VertexType::GenericVertex, strokeWidth))));
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(VertexType::GenericVertex), reinterpret_cast< void* >(static_cast< int64 >(offsetof(VertexType::GenericVertex, color))));
			glEnableVertexAttribArray(5);

			indicesCount = 0;

			m_isInitialized = true;
		}

		void GenerateVAO()
		{
			if( m_renderInfo.vao != 0 )
				DeleteData();

			glGenVertexArrays(1, &m_renderInfo.vao);
			glBindVertexArray(m_renderInfo.vao);
		}

		void AddVBO(const int32 Size, const std::vector< float >& Data)
		{
			uint32 vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, Data.size() * sizeof(float), Data.data(), GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glVertexAttribPointer(m_vboIndex, Size, GL_FLOAT, GL_FALSE, Size * sizeof(float), ( void* )0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glEnableVertexAttribArray(m_vboIndex++);

			m_buffers.push_back(vbo);
		}

		void AddEBO(const std::vector< uint32 >& Indices)
		{
			m_renderInfo.indicesCount = Indices.size();
			uint32 ebo;
			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(uint32), Indices.data(), GL_DYNAMIC_DRAW);

			m_buffers.push_back(ebo);
		}
	};
} // namespace Nocturn
#endif