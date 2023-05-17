/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 18-04-2021 10:20:09                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 07-12-2021 19:43:13                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/
#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Core/core.h"

namespace Nocturn
{
	class NShader
	{
	public:
		NShader( ) noexcept;
		NShader( const char* VertexShaderFileNameIn, const char* FragmentShaderFileNameIn );

		/* Cant copy */ 
		NShader( const NShader& ) = delete;
		NShader& operator=( const NShader& ) = delete;

		/* Cant move */
		NShader( NShader&& ) = delete;
		NShader& operator=( NShader&& ) = delete;

		/**
		 * @brief Initializes the shader with the specified shader files.
		 * @return The initialization status of the shader.
		 */
		RStatus Init();

		/**
		 * @brief Activates the shader.
		 */
		void Bind() const;

		/**
		 * @brief Deactivates the shader.
		 */
		void Unbind() const;

		/**
		 * @brief Sets a boolean value for a boolean uniform variable in the shader.
		 * @param Name The name of the uniform variable.
		 * @param Value The boolean value.
		 */
		void SetBool(const std::string& Name, bool Value) const;

		/**
		 * @brief Sets an integer value for an integer uniform variable in the shader.
		 * @param Name The name of the uniform variable.
		 * @param Value The integer value.
		 */
		void SetInt(const std::string& Name, int Value) const;

		/**
		 * @brief Sets a floating-point value for a float uniform variable in the shader.
		 * @param Name The name of the uniform variable.
		 * @param Value The floating-point value.
		 */
		void SetFloat(const char* Name, float Value) const;

		/**
		 * @brief Sets a vec2 value for a vec2 uniform variable in the shader.
		 * @param Name The name of the uniform variable.
		 * @param Value1 The first component of the vec2 value.
		 * @param Value2 The second component of the vec2 value.
		 */
		void SetVec2(const std::string& Name, float Value1, float Value2) const;

		/**
		 * @brief Sets a vec2 value for a vec2 uniform variable in the shader.
		 * @param Name The name of the uniform variable.
		 * @param Value The vec2 value.
		 */
		void SetVec2(const std::string& Name, const glm::vec2& Value) const;

		/**
		 * @brief Sets a vec3 value for a vec3 uniform variable in the shader.
		 * @param Name The name of the uniform variable.
		 * @param Value The vec3 value.
		 */
		void SetVec3(const std::string& Name, const glm::vec3& Value) const;

		/**
		 * @brief Sets a value consisting of 3 floats for a uniform variable of type vec3 in the shader.
		 * @param Name The name of the uniform variable.
		 * @param Value1 The first float value.
		 * @param Value2 The second float value.
		 * @param Value3 The third float value.
		 */
		void Set3Float(const std::string& Name, float Value1, float Value2, float Value3) const;

		/**
		 * @brief Sets a 4x4 matrix value for a mat4 uniform variable in the shader.
		 * @param Name The name of the uniform variable.
		 * @param Matrix The mat4 value.
		 */
		void SetMatrix4(const char* Name, const glm::mat4& Matrix) const;

		/**
		 * @brief Retrieves the value of a vec2 uniform variable from the shader.
		 * @param UniformName The name of the uniform variable.
		 * @return The value of the vec3 variable.
		 */
		NODISCARD vec2 GetVec2(const std::string& UniformName) const;

		/**
		 * @brief Retrieves the value of a vec3 uniform variable from the shader.
		 * @param UniformName The name of the uniform variable.
		 * @return The value of the vec3 variable.
		 */
		NODISCARD vec3 GetVec3(const std::string& UniformName) const;

		/**
		 * @brief Retrieves the ID of the shader program.
		 * @return The ID of the shader program.
		 */
		NODISCARD uint32 GetId() const noexcept;

		/**
		 * @brief Cleans up the resources associated with the shader.
		 */
		void Cleanup() const;

		/**
		 * @brief Sets the view matrix for the shader.
		 * @param ViewMatrix The view matrix.
		 */
		virtual void SetViewMatrix(const mat4& ViewMatrix) const;

		/**
		 * @brief Sets the projection matrix for the shader.
		 * @param ProjectionMatrix The projection matrix.
		 */
		virtual void SetProjectionMatrix(const mat4& ProjectionMatrix) const;

		/**
		 * @brief Reloads the shaders by cleaning up the current shader and initializing a new one.
		 * @return True if the shader reload is successful, false otherwise.
		 */
		bool ReloadShader();

		/**
		 * @brief Indicates whether the shader has been initialized.
		 * @return True if the shader has been initialized, false otherwise.
		 */
		NODISCARD bool IsInitialized() const noexcept
		{
			return bIsInit;
		}

		virtual ~NShader() noexcept = default;

	protected:
		/** The file name of the vertex shader. */
		const char* VertexShaderFileName;

		/** The file name of the fragment shader. */
		const char* FragmentShaderFileName;

		/** The ID of the shader program. */
		uint32 id;

		/** Flag indicating if the shader has been initialized. */
		bool bIsInit = false;

		/**
		 * @brief Checks for compile errors for the specified shader or program.
		 * @param Shader The ID of the shader or program.
		 * @param Type The type of shader or program.
		 */
		void CheckCompileErrors(uint32_t Shader, const std::string& Type);

		/**
		 * @brief Checks if the file names of the vertex and fragment shaders are valid.
		 * @param VertexShader The name of the vertex shader file.
		 * @param FragmentShader The name of the fragment shader file.
		 * @return True if the file names are valid, false otherwise.
		 */
		bool CheckFileCompliance(const char* VertexShader, const char* FragmentShader) const noexcept;
	};
} // namespace Nocturn
#endif
