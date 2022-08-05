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
		static std::array<UInt, MaxVertexNumber> Indices;
		static UInt IndexCounter;
	};
	std::array<Vertex, RendererData::MaxVertexNumber> RendererData::Vertices = std::array<Vertex, MaxVertexNumber>();
	UInt RendererData::VertexCounter = 0;
	std::array<UInt, RendererData::MaxVertexNumber> RendererData::Indices = std::array<UInt, MaxVertexNumber>();
	UInt RendererData::IndexCounter = 0;


	Renderer* Renderer::s_Instance = nullptr;
	void Renderer::Initialize()
	{
		TOMATO_ASSERT(!s_Instance, "Renderer already initialized!");

		s_Instance = new Renderer();

		s_Instance->m_ShaderProgram = std::make_unique<ShaderProgram>("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");
		
		s_Instance->m_VertexBuffer = std::make_unique<VertexBuffer>(RendererData::MaxVertexNumber);
		s_Instance->m_IndexBuffer = std::make_unique<IndexBuffer>(RendererData::MaxVertexNumber);

		s_Instance->m_VertexArray = std::make_unique<VertexArray>();

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::Terminate()
	{
		delete s_Instance;
	}

	void Renderer::Begin()
	{
		s_Instance->m_ProjectionView = App::GetCurrentCamera()->Update();
	}

	void Renderer::End()
	{
		Flush();

		s_Instance->m_ShaderProgram->Use(false);
	}

	Renderer* Renderer::Get()
	{
		return s_Instance;
	}

	void Renderer::Draw(std::shared_ptr<Triangle> triangle)
	{
		if (RendererData::VertexCounter + 3 >= RendererData::MaxVertexNumber ||
			RendererData::IndexCounter + 3 >= RendererData::MaxVertexNumber)
			Flush();

		for (UInt i = 0; i < 3; i++)
		{
			Float4 coords = Float4(triangle->GetVertices()[i].Coords, 1.0f);

			coords = triangle->GetTransform() * coords;

			RendererData::Vertices[RendererData::VertexCounter++] = Vertex(coords.xyz, triangle->GetVertices()[i].Color, triangle->GetVertices()[i].TexCoords);
		}

		auto indices = triangle->GetIndices();

		UInt old_ic = RendererData::IndexCounter;

		for (UInt i = 0; i < indices.size(); i++)
		{
			RendererData::Indices[RendererData::IndexCounter++] = indices[i] + old_ic;
		}
	}

	void Renderer::Flush()
	{
		auto& ins = s_Instance;

		//Apply Camera Projection View
		for (UInt i = 0; i < RendererData::VertexCounter; i++)
		{
			Float4 pos = s_Instance->m_ProjectionView * Float4(RendererData::Vertices[i].Coords, 1.0f);

			RendererData::Vertices[i].Coords = pos.xyz;
		}

		ins->m_VertexBuffer->Bind();
		ins->m_VertexBuffer->SetData(RendererData::Vertices, RendererData::VertexCounter);
		ins->m_VertexBuffer->Unbind();

		ins->m_VertexArray->Bind();

		ins->m_IndexBuffer->Bind();
		ins->m_IndexBuffer->SetData(RendererData::Indices, RendererData::IndexCounter);
		ins->m_IndexBuffer->Unbind();

		ins->m_ShaderProgram->Use();

		glDrawElements(GL_TRIANGLES, RendererData::IndexCounter, GL_UNSIGNED_INT, nullptr);

		RendererData::VertexCounter = 0;
		RendererData::IndexCounter = 0;

		VertexArray::Unbind();
	}
}
