#include "pchTomato.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "App.h"


namespace Tomato
{
	struct RendererData
	{
		static const UInt MaxVertexNumber = 1024;
		static std::array<Vertex, MaxVertexNumber> Vertices;
		static UInt VertexCounter;
	};
	std::array<Vertex, RendererData::MaxVertexNumber> RendererData::Vertices = std::array<Vertex, MaxVertexNumber>();
	UInt RendererData::VertexCounter = 0;


	Renderer* Renderer::s_Instance = nullptr;
	void Renderer::Initialize()
	{
		TOMATO_ASSERT(!s_Instance, "Renderer already initialized!");

		s_Instance = new Renderer();

		s_Instance->m_ShaderProgram = std::make_unique<ShaderProgram>("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");
		
		s_Instance->m_VertexBuffer = std::make_unique<VertexBuffer>(RendererData::MaxVertexNumber);

		s_Instance->m_VertexArray = std::make_unique<VertexArray>();

		RendererData::Vertices[0] = Vertex(Float3(-0.5f, -0.5f, 0.0f));
		RendererData::Vertices[1] = Vertex(Float3(+0.5f, -0.5f, 0.0f));
		RendererData::Vertices[2] = Vertex(Float3( 0.0f, +0.5f, 0.0f));
	
		RendererData::VertexCounter = 3;
	}

	void Renderer::Terminate()
	{
		delete s_Instance;
	}

	void Renderer::Begin()
	{
		
	}

	void Renderer::End()
	{
		s_Instance->m_ShaderProgram->Use(false);
	}

	Renderer* Renderer::Get()
	{
		return s_Instance;
	}

	void Renderer::Draw(const Triangle& triangle)
	{
		if (RendererData::VertexCounter + 3 >= RendererData::MaxVertexNumber)
			Flush();

		for (UInt i = 0; i < 3; i++)
			RendererData::Vertices[RendererData::VertexCounter++] = triangle.GetVertices()[i];
	}

	void Renderer::Flush()
	{
		auto& ins = s_Instance;
		ins->m_VertexBuffer->Bind();
		ins->m_VertexBuffer->SetData(RendererData::Vertices, RendererData::VertexCounter);

		ins->m_ShaderProgram->Use();

		auto view = App::GetCurrentCamera()->Update();

		ins->m_ShaderProgram->SetUniformMat4("View", view);

		ins->m_VertexArray->Bind();

		glDrawArrays(GL_TRIANGLES, 0, RendererData::VertexCounter);

		RendererData::VertexCounter = 0;

		VertexArray::Unbind();
	}
}
