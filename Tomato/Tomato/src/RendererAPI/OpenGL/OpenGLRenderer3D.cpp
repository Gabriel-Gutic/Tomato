#include "pchTomato.h"
#include "OpenGLRenderer3D.h"

#include "RendererAPI/RendererData.h"
#include "Tomato/Core/App/App.h"

#include <glad/glad.h>


namespace Tomato
{
	struct OpenGLRendererData
	{
		std::array<Mesh::Vertex, MAX_VERTEX_NUMBER> Vertices;
		uint32_t VertexCounter = 0;
		std::array<uint32_t, MAX_INDEX_NUMBER> Indices;
		uint32_t IndexCounter = 0;
	};
	static OpenGLRendererData RendererData;


	OpenGLRenderer3D::OpenGLRenderer3D()
	{
		m_Shader = std::move(Shader::CreateUnique("assets/Shaders/3D/VertexShader.glsl", "assets/Shaders/3D/FragmentShader.glsl"));
		m_VertexBuffer = std::make_unique<VertexBuffer>(MAX_VERTEX_NUMBER * sizeof(Mesh::Vertex));
		m_IndexBuffer = std::make_unique<IndexBuffer>(MAX_INDEX_NUMBER);
		m_VertexArray = std::make_unique<VertexArray>();

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	OpenGLRenderer3D::~OpenGLRenderer3D()
	{

	}

	void OpenGLRenderer3D::Begin()
	{
		const auto& window = App::GetWindow();
		window->Clear(Float4(1.0f, 0.5f, 0.2f, 1.0f));

		m_Shader->SetMat4("u_VP", App::GetCurrentScene()->GetViewProjection());
	}

	void OpenGLRenderer3D::End()
	{
		Flush();
	}

	void OpenGLRenderer3D::Draw(const Mesh& mesh, const Mat4& transform)
	{
		if (RendererData.VertexCounter + mesh.Vertices.size() >= MAX_VERTEX_NUMBER ||
			RendererData.IndexCounter + mesh.Indices.size() >= MAX_INDEX_NUMBER)
			Flush();
		if (RendererData.VertexCounter + mesh.Vertices.size() >= MAX_VERTEX_NUMBER ||
			RendererData.IndexCounter + mesh.Indices.size() >= MAX_INDEX_NUMBER)
			return;

		for (auto vertex : mesh.Vertices)
		{
			vertex.Position = (transform * Float4(vertex.Position, 1.0f)).xyz;
			RendererData.Vertices[RendererData.VertexCounter++] = vertex;
		}
		for (const auto& index : mesh.Indices)
		{
			RendererData.Indices[RendererData.IndexCounter++] = index;

		}
	}

	void OpenGLRenderer3D::Flush()
	{
		m_Shader->Use();

		m_VertexBuffer->Bind();
		m_VertexBuffer->SetData(RendererData.Vertices, RendererData.VertexCounter);
		m_VertexBuffer->Unbind();

		m_IndexBuffer->Bind();
		m_IndexBuffer->SetData(RendererData.Indices, RendererData.IndexCounter);
		m_IndexBuffer->Unbind();

		m_VertexArray->Bind();

		glDrawElements(GL_TRIANGLES, RendererData.IndexCounter, GL_UNSIGNED_INT, 0);

		RendererData.VertexCounter = 0;
		RendererData.IndexCounter = 0;

		VertexArray::Unbind();
	}
}