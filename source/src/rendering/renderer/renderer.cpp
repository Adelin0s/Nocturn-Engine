#include "rendering/renderer/renderer.h"

#include "application/application.h"
#include "rendering/components/shaders/shader.h"
#include "rendering/data/mesh.hpp"
#include "rendering/data/model.h"

#include <iostream>

namespace Nocturn::Renderer
{
	static const Camera *camera;
	static LineModel	 batchLines;
	static Shader		 lineShader( Config::CLineVertexShader, Config::CLineFragmentShader );

	void Init( const Camera &cameraRef )
	{
		batchLines.SetNumVertices( 0 );
		camera = nullptr;

		batchLines.Init( { { 0, 3, AttributeType::Float, offsetof( RenderVertexLine, start ) },
						   { 1, 3, AttributeType::Float, offsetof( RenderVertexLine, end ) },
						   { 2, 1, AttributeType::Float, offsetof( RenderVertexLine, isStart ) },
						   { 3, 1, AttributeType::Float, offsetof( RenderVertexLine, direction ) },
						   { 4, 1, AttributeType::Float, offsetof( RenderVertexLine, strokeWidth ) },
						   { 5, 4, AttributeType::Float, offsetof( RenderVertexLine, color ) } } );

		lineShader.init( );

		camera = &cameraRef;
	}

	void Render( )
	{
		if( batchLines.GetNumVertices( ) <= 0 )
		{
			return;
		}

		glDisable( GL_CULL_FACE );

		assert( camera != nullptr );

		lineShader.bind( );
		lineShader.setMatrix4( "uProjection", camera->getProjectionMatrix( ) );
		lineShader.setMatrix4( "uView", camera->getViewMatrix( ) );
		lineShader.setFloat( "uAspectRatio", Application::getWindow( ).getAspectRatio( ) );

		batchLines.Flush( );

		glEnable( GL_CULL_FACE );
	}

	void DrawLine( const vec3 &start, const vec3 &end, const Style &style )
	{
		// First triangle
		RenderVertexLine v{ };
		v.isStart	  = 1.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = -1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		batchLines.AddVertex( v );

		v.isStart	  = 1.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = 1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		batchLines.AddVertex( v );

		v.isStart	  = 0.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = 1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		batchLines.AddVertex( v );

		// Second triangle
		v.isStart	  = 1.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = -1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		batchLines.AddVertex( v );

		v.isStart	  = 0.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = 1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		batchLines.AddVertex( v );

		v.isStart	  = 0.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = -1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		batchLines.AddVertex( v );
	}

	void DrawBox( const glm::vec3 &center, const glm::vec3 &size, const Style &style )
	{
		glm::vec3 v0 = center - ( size * 0.5f );
		glm::vec3 v1 = v0 + glm::vec3( size.x, 0, 0 );
		glm::vec3 v2 = v0 + glm::vec3( 0, 0, size.z );
		glm::vec3 v3 = v0 + glm::vec3( size.x, 0, size.z );

		glm::vec3 v4 = v0 + glm::vec3( 0, size.y, 0 );
		glm::vec3 v5 = v1 + glm::vec3( 0, size.y, 0 );
		glm::vec3 v6 = v2 + glm::vec3( 0, size.y, 0 );
		glm::vec3 v7 = v3 + glm::vec3( 0, size.y, 0 );

		DrawLine( v0, v1, style );
		DrawLine( v0, v2, style );
		DrawLine( v2, v3, style );
		DrawLine( v1, v3, style );

		DrawLine( v4, v5, style );
		DrawLine( v4, v6, style );
		DrawLine( v5, v7, style );
		DrawLine( v6, v7, style );

		DrawLine( v0, v4, style );
		DrawLine( v1, v5, style );
		DrawLine( v2, v6, style );
		DrawLine( v3, v7, style );
	}

	void Free( )
	{
	}

} // namespace Nocturn::Renderer
