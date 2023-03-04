#include "rendering/components/shaders/shader.h"

namespace Nocturn
{
	NShader::NShader( ) noexcept
	:
		VertexShaderFileName( nullptr ), FragmentShaderFileName( nullptr ), id( 0 )
	{}

	NShader::NShader( const char* VertexShaderFileNameIn, const char* FragmentShaderFileNameIn )
	:
		id(0)
	{
		VertexShaderFileName = VertexShaderFileNameIn;
		FragmentShaderFileName = FragmentShaderFileNameIn;
	}

	RStatus NShader::Init( )
	{
		if( CheckFileCompliance( VertexShaderFileName, FragmentShaderFileName ) == false )
		{
			return RInvalidArguments;
		}
		
		std::string vertexCode;
		std::string fragmentCode;

		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		vertexShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
		fragmentShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
		try
		{
			std::string PathToVertexShader{ Config::CDirShaders + VertexShaderFileName };
			std::string PathToFragmentShader{ Config::CDirShaders + FragmentShaderFileName };

			/* Open files */
			vertexShaderFile.open( PathToVertexShader.data( ) );
			fragmentShaderFile.open( PathToFragmentShader.data( ) );

			std::stringstream vertexShaderStream, fragmentShaderStream;
			vertexShaderStream << vertexShaderFile.rdbuf( );
			fragmentShaderStream << fragmentShaderFile.rdbuf( );

			vertexShaderFile.close( );
			fragmentShaderFile.close( );

			vertexCode	 = vertexShaderStream.str( );
			fragmentCode = fragmentShaderStream.str( );
		}
		catch( std::ifstream::failure& e )
		{
			std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << VertexShaderFileName << " with exception: " << e.what( ) << std::endl;
		}
		const char* vertexShaderCode   = vertexCode.c_str( );
		const char* fragmentShaderCode = fragmentCode.c_str( );

		uint32_t vertex, fragment;

		/* Vertex shader */
		vertex = glCreateShader( GL_VERTEX_SHADER );
		glShaderSource( vertex, 1, &vertexShaderCode, nullptr );
		glCompileShader( vertex );
		CheckCompileErrors( vertex, "VERTEX" );

		/* Fragment shader */
		fragment = glCreateShader( GL_FRAGMENT_SHADER );
		glShaderSource( fragment, 1, &fragmentShaderCode, nullptr );
		glCompileShader( fragment );
		CheckCompileErrors( fragment, "FRAGMENT" );

		/* Link program */
		id = glCreateProgram( );
		glAttachShader( id, vertex );
		glAttachShader( id, fragment );
		glLinkProgram( id );

		CheckCompileErrors( id, "PROGRAM" );

		glDeleteShader( vertex );
		glDeleteShader( fragment );

		bIsInit = true;

		return RSucces;
	}

	void NShader::Bind( ) const
	{
		Check( bIsInit );

		glUseProgram( id );
	}

	void NShader::Unbind( ) const
	{
		glUseProgram( 0 );
	}

	void NShader::SetBool( const std::string& Name, const bool Value ) const
	{
		glUniform1i( glGetUniformLocation( id, Name.c_str( ) ), int( Value ) );
	}

	void NShader::SetInt( const std::string& Name, const int Value ) const
	{
		glUniform1i( glGetUniformLocation( id, Name.c_str( ) ), Value );
	}

	void NShader::SetFloat( const char* const Name, const float Value ) const
	{
		glUniform1f( glGetUniformLocation( id, Name ), Value );
	}

	void NShader::SetVec2( const std::string& Name, const float Value1, const float Value2 ) const
	{
		glUniform2f( glGetUniformLocation( id, Name.c_str( ) ), Value1, Value2 );
	}

	void NShader::SetVec2( const std::string& Name, const glm::vec2& Value ) const
	{
		glUniform2fv( glGetUniformLocation( id, Name.c_str( ) ), 1, &Value[ 0 ] );
	}

	void NShader::SetVec3( const std::string& Name, const glm::vec3& Value ) const
	{
		glUniform3fv( glGetUniformLocation( id, Name.c_str( ) ), 1, &Value[ 0 ] );
	}

	void NShader::Set3Float( const std::string& Name, const float Value1, const float Value2, const float Value3 ) const
	{
		glUniform3f( glGetUniformLocation( id, Name.c_str( ) ), Value1, Value2, Value3 );
	}

	void NShader::SetMatrix4( const char* const Name, const glm::mat4& mat ) const
	{
		glUniformMatrix4fv( glGetUniformLocation( id, Name ), 1, GL_FALSE, glm::value_ptr( mat ) );
	}

	uint32_t NShader::GetId( ) const noexcept
	{
		return id;
	}

	void NShader::Cleanup( ) const
	{
		glDeleteProgram( id );
	}

	void NShader::SetViewMatrix( const NCamera& Camera ) const
	{
		assert( bIsInit );

		SetMatrix4( "projection", Camera.GetProjectionMatrix( ) );
	}

	void NShader::SetProjectionMatrix( const NCamera& Camera ) const
	{
		assert( bIsInit );

		SetMatrix4( "view", Camera.GetViewMatrix( ) );
	}

	void NShader::CheckCompileErrors( uint32_t Shader, const std::string& Type )
	{
		int	 succes;
		char log[ 512 ];
		if( Type == "PROGRAM" )
		{
			glGetProgramiv( Shader, GL_LINK_STATUS, &succes );
			if( !succes )
			{
				glGetProgramInfoLog( Shader, 512, nullptr, log );
				std::cerr << "ERROR_PROGRAM_LINKING::LINKING_FAILED\n " << log << std::endl;
			}
		}
		else
		{
			glGetShaderiv( Shader, GL_COMPILE_STATUS, &succes );
			if( !succes )
			{
				glGetShaderInfoLog( Shader, 512, nullptr, log );
				std::cerr << "ERROR_" << Type << "_SHADER::COMPILATION_FAILED\n " << log << std::endl;
			}
		}
	}

	bool NShader::CheckFileCompliance( const char* VertexShader, const char* FragmentShader ) const noexcept
	{
		if (VertexShader == nullptr || FragmentShader == nullptr)
		{
			LogError( "Invalid Arguments!" );
			return false;
		}

		return VertexShader[strlen( VertexShader ) - 2] == 'v' && FragmentShader[strlen(FragmentShader) - 2] == 'f';
	}
} // namespace Nocturn
