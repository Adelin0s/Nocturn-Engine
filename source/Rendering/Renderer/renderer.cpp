#include "rendering/renderer/renderer.h"

#include "application/application.h"
#include "rendering/components/shaders/shader.h"
#include "Rendering/Renderer/Data/model.hpp"

#include "Context/Components/CameraComponent.h"

namespace Nocturn::Render
{
	//Model< VertexType::GenericVertex > genericModel;
	UniquePtr< Model< VertexType::GenericVertex > > GenericModel;
	static NShader lineShader( "line.vs", "line.fs" );
	static const NCameraComponent* CameraComponent;

	void Init(const NCameraComponent* CameraComponentIn)
	{
		AssertInfo(CameraComponentIn != nullptr, "Failed to Init because CameraComponentIn is nullptr!");

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		lineShader.Init();

		CameraComponent = CameraComponentIn;

		GenericModel = std::make_unique< Model< VertexType::GenericVertex > >();
	}

	void DrawLine( const vec3 &start, const vec3 &end, const Style &style )
	{
		// First triangle
		VertexType::GenericVertex v{ };
		v.isStart	  = 1.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = -1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		GenericModel->AddVertexData( v );

		v.isStart	  = 1.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = 1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		GenericModel->AddVertexData( v );

		v.isStart	  = 0.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = 1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		GenericModel->AddVertexData( v );

		// Second triangle
		v.isStart	  = 1.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = -1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		GenericModel->AddVertexData( v );

		v.isStart	  = 0.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = 1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		GenericModel->AddVertexData( v );

		v.isStart	  = 0.0f;
		v.start		  = start;
		v.end		  = end;
		v.direction	  = -1.0f;
		v.color		  = style.color;
		v.strokeWidth = style.strokeWidth;
		GenericModel->AddVertexData( v );
	}

	void DrawBox( const vec3 &position, const glm::vec3 &size, const Style &style )
	{
		const auto center = position - 0.5f;
		const vec3 v0 = center - ( size * 0.5f );
		const vec3 v1 = v0 + vec3( size.x, 0, 0 );
		const vec3 v2 = v0 + vec3( 0, 0, size.z );
		const vec3 v3 = v0 + vec3( size.x, 0, size.z );

		const vec3 v4 = v0 + vec3( 0, size.y, 0 );
		const vec3 v5 = v1 + vec3( 0, size.y, 0 );
		const vec3 v6 = v2 + vec3( 0, size.y, 0 );
		const vec3 v7 = v3 + vec3( 0, size.y, 0 );

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

	void Render()
	{
		if (GenericModel->m_vertexData.empty())
		{
			return;
		}

		auto &vao = GenericModel->m_renderInfo.vao;
		auto &vbo = GenericModel->m_renderInfo.vbo;
		auto &indicesCount = GenericModel->m_renderInfo.indicesCount;

		if( indicesCount <= 0 )
		{
			return;
		}

		glDisable(GL_CULL_FACE); 

		assert(CameraComponent != nullptr);

		lineShader.Bind();
		lineShader.SetMatrix4("uProjection", CameraComponent->GetProjectionMatrix());
		lineShader.SetMatrix4("uView", CameraComponent->GetViewMatrix());
		lineShader.SetFloat("uAspectRatio", Application::GetWindow().GetAspectRatio());

		// Draw the 3D screen space stuff
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType::GenericVertex) * CMaxGenericModelSize, GenericModel->m_vertexData.data(), GL_DYNAMIC_DRAW);

		glBindVertexArray( GenericModel->m_renderInfo.vao );
		//std::cout << "\n" << GenericModel->m_renderInfo.vao << "\n";
		glDrawArrays( GL_TRIANGLES, 0, static_cast< int32 >( indicesCount ) );

		// Clear the batch
		indicesCount = 0;
		GenericModel->m_vertexData.clear( );

		glEnable( GL_CULL_FACE );
	}

	void Free( )
	{
	}

} // namespace Nocturn::Renderer