/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 18-04-2021 10:20:09                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 07-12-2021 19:43:13                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/
#ifndef SHADERR_H
#define SHADERR_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "core/math/glm.hpp"
#include "core/platform/platform.h"

#include "rendering/components/entity/camera.h"

namespace Nocturn
{
	class Shader
	{
	public:
		Shader( ) noexcept = default;
		Shader( const char *vertexPath, const char *fragmentPath );
		Shader( const Shader & ) = delete;
		Shader( Shader && )		 = delete;

		Shader &operator=( const Shader & ) = delete;
		Shader &operator=( Shader && ) = delete;

		void setBool( const std::string &name, const bool value ) const;
		void setInt( const std::string &name, const int value ) const;
		void setFloat( const char *const name, const float value ) const;
		void setVec2( const std::string &name, const float value1, const float value2 ) const;
		void setVec2( const std::string &name, const glm::vec2 &value ) const;
		void setVec3( const std::string &name, const glm::vec3 &value ) const;
		void set3Float( const std::string &name, float value1, float value2, float value3 ) const;
		void setMatrix4( const char *const name, const glm::mat4 &mat ) const;

		NODISCARD uint32_t getId( ) const noexcept;

		void init( );
		void bind( ) const;
		void unbind( ) const;
		void cleanup( ) const;

		virtual void setViewMatrix( const Camera &camera ) const;
		virtual void setProjectionMatrix( const Camera &camera ) const;

		virtual ~Shader( ) noexcept = default;

	protected:
		std::string m_vertexPath;
		std::string m_fragmentPath;
		uint32_t	m_id;
		bool		m_bIsInit = false;

		void checkCompileErrors( uint32_t shader, const std::string &type );
	};
} // namespace Nocturn
#endif
