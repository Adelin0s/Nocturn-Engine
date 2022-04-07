/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 18-04-2021 10:20:09                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 07-12-2021 19:43:13                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/
#ifndef SHADERR_H
#define SHADERR_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "core/math/glm.hpp"
#include "core/platform/platform.h"

#include "rendering/data/camera.h"

namespace Nocturn
{
	class Shader
	{
	public:
		Shader() noexcept = default;
		Shader(const char* vertexPath, const char* fragmentPath);
		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;

		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) = delete;

		void setBool(const std::string& name, const bool value) const;
		void setInt(const std::string& name, const int value) const;
		void setFloat(const std::string& name, const float value) const;
		void setVec2(const std::string& name, const float value1, const float value2);
		void setVec2(const std::string& name, const glm::vec2& value);
		void setVec3(const std::string& name, const glm::vec3& value);
		void set3Float(const std::string& name, float value1, float value2, float value3) const;
		void set4Matrix(const std::string& name, const glm::mat4& mat) const;
		uint32_t getId() const noexcept;

		void init();
		void activate();
		void cleanup() const;

		virtual void setViewMatrix(const Camera& camera) const NOCTURN_PURE;
		virtual void setProjectionMatrix(const Camera& camera) const NOCTURN_PURE;

		virtual ~Shader() noexcept = default;

	protected:
		std::string m_vertexPath;
		std::string m_fragmentPath;
		uint32_t m_id;

		void checkCompileErrors(uint32_t shader, const std::string& type);
	};
}
#endif
