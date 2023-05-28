#include "Gui/hud.h"

#include "Application/Window/window.h"

namespace Nocturn
{
	unsigned int VBO, VAO, EBO;

	NHUD::NHUD( )
	{
		Shader	= std::make_unique< NShader >("texture.vs" , "texture.fs");
		Texture = std::make_unique< NTexture >( HUD::CCrossHairPath );
	}

	void NHUD::Initialize( )
	{
		constexpr float Vertices[] =
		{
			// positions          // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
		};
		constexpr unsigned int Indices[] =
		{
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		glGenVertexArrays( 1, &VAO );
		glGenBuffers( 1, &VBO );
		glGenBuffers( 1, &EBO );

		glBindVertexArray( VAO );

		glBindBuffer( GL_ARRAY_BUFFER, VBO );
		glBufferData( GL_ARRAY_BUFFER, sizeof( Vertices ), Vertices, GL_STATIC_DRAW );

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( Indices ), Indices, GL_STATIC_DRAW );

		/* Position attribute */
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), ( void* )0 );
		glEnableVertexAttribArray( 0 );

		/* Texture coord attribute */
		glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), ( void* )( 3 * sizeof( float ) ) );
		glEnableVertexAttribArray( 1 );

		Shader->Init( );
		Texture->Init( );

		Shader->Bind( );
		const auto Projection = glm::perspective( 45.f, static_cast< float >( NWindow::Width ) / static_cast< float >( NWindow::Height ), 0.1f, 100.0f );
		auto Model			  = mat4( 1.0f ); // make sure to initialize matrix to identity matrix first
		Model				  = glm::scale( Model, vec3( 0.1f, 0.1f, 1.0f ) );
		auto View			  = mat4( 1.0f );
		View				  = glm::translate( View, glm::vec3( 0.0f, 0.0f, -3.0f ) );

		/* Note: Currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once */
		Shader->SetMatrix4( "uView", View );
		Shader->SetMatrix4( "uModel", Model );
		Shader->SetMatrix4( "uProjection", Projection );
	}

	void NHUD::Update( )
	{
		glDisable( GL_DEPTH_TEST );
		glDisable( GL_CULL_FACE );

		Texture->Bind( );

		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		Shader->Bind( );

		glBindVertexArray( VAO );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );

		glBindVertexArray( 0 );
		Texture->Unbind( );
		Shader->Unbind( );
	}

} // namespace Nocturn
