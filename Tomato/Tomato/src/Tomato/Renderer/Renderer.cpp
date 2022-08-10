#include "pchTomato.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "App.h"


namespace Tomato
{
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
		s_Instance->m_ShaderProgram->Use(true);

		s_Instance->m_Projection = App::GetCurrentCamera()->GetProjection();
		s_Instance->m_View = App::GetCurrentCamera()->GetView();
		
		s_Instance->m_ShaderProgram->SetUniformMat4("Projection", s_Instance->m_Projection);
		s_Instance->m_ShaderProgram->SetUniformMat4("View", s_Instance->m_View);
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

	void Renderer::Draw(const Cube& cube)
	{
		for (const auto& [name, side] : cube.GetSides())
		{
			auto& vertices = side.GetVertices();
			auto indices = side.GetIndices();
			if (RendererData::VertexCounter + vertices.size() >= RendererData::MaxVertexNumber ||
				RendererData::IndexCounter + indices.size() >= RendererData::MaxVertexNumber)
				Flush();

			for (auto& index : indices)
			{
				RendererData::Indices[RendererData::IndexCounter++] = index + RendererData::VertexCounter;
			}

			const Mat4 side_tran = side.GetTransform();

			for (auto& vertex : vertices)
			{
				Float3 coords = Quaternion::Rotate((side_tran * Float4(vertex.Coords, 1.0f)).xyz, 0.0f, 45.0f, 45.0f);
				RendererData::Vertices[RendererData::VertexCounter++] = Vertex(coords, vertex.Color, vertex.TexCoords);
			}
		}
	}

	void Renderer::Flush()
	{
		auto& ins = s_Instance;

		ins->m_VertexBuffer->Bind();
		ins->m_VertexBuffer->SetData(RendererData::Vertices, RendererData::VertexCounter);
		ins->m_VertexBuffer->Unbind();

		ins->m_VertexArray->Bind();

		ins->m_IndexBuffer->Bind();
		ins->m_IndexBuffer->SetData(RendererData::Indices, RendererData::IndexCounter);
		ins->m_IndexBuffer->Unbind();

		glDrawElements(GL_TRIANGLES, RendererData::IndexCounter, GL_UNSIGNED_INT, nullptr);

		RendererData::VertexCounter = 0;
		RendererData::IndexCounter = 0;

		VertexArray::Unbind();
	}
}
