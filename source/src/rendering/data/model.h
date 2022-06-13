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

#include "core/platform/platform.h"
#include "rendering/data/mesh.hpp"

#include "rendering/renderer/renderinfo.hpp"

namespace Nocturn::rendering
{
	class Model
	{
	public:
		Model( ) noexcept			= default;
		Model( const Model &model ) = default;
		Model( Model &&model )		= delete;
		Model &operator=( const Model &model ) = delete;
		Model &operator=( Model &&model ) = delete;

		void generateVAO( );
		void bindVAO( ) const noexcept;
		void addData( const Mesh &mesh );
		void addVBO( const int size, const std::vector< float > &data );
		void addEBO( const std::vector< uint32_t > &indices );

		NODISCARD uint32_t			getIndicesCount( ) const noexcept;
		NODISCARD const RenderInfo &getRenderInfo( ) const;

		void deleteData( );

		~Model( ) noexcept;

	private:
		RenderInfo				m_renderInfo;
		uint32_t				m_vboIndex = 0;
		std::vector< uint32_t > m_buffers;
	};
} // namespace Nocturn::rendering
#endif
