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

		void SetBool( const std::string& Name, bool Value ) const;
		void SetInt( const std::string& Name, int Value ) const;
		void SetFloat( const char* Name, float Value ) const;
		void SetVec2( const std::string& Name, float Value1, float Value2 ) const;
		void SetVec2( const std::string& Name, const vec2& Value ) const;
		void SetVec3( const std::string& Name, const vec3& Value ) const;
		void Set3Float( const std::string& Name, float Value1, float Value2, float Value3 ) const;
		void SetMatrix4( const char* Name, const mat4& Matrix ) const;

		NODISCARD vec3 GetVec3(const std::string& uniformName) const;

		NODISCARD uint32 GetId( ) const noexcept;

		RStatus Init( );
		void Bind( ) const;
		void Unbind( ) const;
		void Cleanup( ) const;

		virtual void SetViewMatrix( const mat4& ViewMatrix ) const;
		virtual void SetProjectionMatrix( const mat4& ProjectionMatrix ) const;

		virtual ~NShader( ) noexcept = default;

	protected:
		const char* VertexShaderFileName;
		const char* FragmentShaderFileName;
		uint32 id;
		bool bIsInit = false;

		void CheckCompileErrors( uint32 Shader, const std::string& Type );
		bool CheckFileCompliance( const char* VertexShader, const char* FragmentShader ) const noexcept;
	};
} // namespace Nocturn
#endif
