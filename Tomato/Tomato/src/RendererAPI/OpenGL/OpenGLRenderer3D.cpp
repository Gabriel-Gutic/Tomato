#include "pchTomato.h"
#include "OpenGLRenderer3D.h"

#include "RendererAPI/RendererData.h"
#include "RendererAPI/OpenGL/OpenGLTexture.h"
#include "Tomato/Core/App/App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Tomato
{
	struct OpenGLRendererData
	{
		std::array<Mesh::Vertex, MAX_VERTEX_NUMBER> Vertices = {};
		uint32_t VertexCounter = 0;
		std::array<uint32_t, MAX_INDEX_NUMBER> Indices = {};
		uint32_t IndexCounter = 0;
		std::array<std::shared_ptr<Texture>, MAX_TEXTURE_SLOTS> TextureSlots;
		uint32_t TextureSlotsCounter;
	};
	static OpenGLRendererData RendererData;


	OpenGLRenderer3D::OpenGLRenderer3D()
	{
		m_Shader = std::move(Shader::CreateUnique("assets/Shaders/3D/VertexShader.glsl", "assets/Shaders/3D/FragmentShader.glsl"));
		m_VertexBuffer = std::move(VertexBuffer::CreateUnique(MAX_VERTEX_NUMBER * sizeof(Mesh::Vertex), BufferAllocType::Dynamic));
		m_IndexBuffer = std::move(IndexBuffer::CreateUnique(MAX_INDEX_NUMBER, BufferAllocType::Dynamic));
		m_VertexArray = std::move(VertexArray::CreateUnique());

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);
	}

	OpenGLRenderer3D::~OpenGLRenderer3D()
	{
	}

	void OpenGLRenderer3D::Begin()
	{
		OpenGLRenderer3D::Clear(1.0f, 0.5f, 0.2f, 1.0f);

		m_Shader->SetMat4("u_VP", App::GetCurrentScene()->GetViewProjection());
	}

	void OpenGLRenderer3D::End()
	{
		Flush();
	}

	void OpenGLRenderer3D::Clear(float r, float g, float b, float a) const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(r, g, b, a);
	}

	void OpenGLRenderer3D::Swap() const
	{
		/* Swap front and back buffers */
		glfwSwapBuffers(std::any_cast<GLFWwindow*>(App::GetWindow()->Get()));

		/* Poll for and process events */
		glfwPollEvents();
	}

	void OpenGLRenderer3D::Draw(const Mesh& mesh, const Mat4& transform)
	{
		if (RendererData.VertexCounter + mesh.Vertices.size() >= MAX_VERTEX_NUMBER ||
			RendererData.IndexCounter + mesh.Indices.size() >= MAX_INDEX_NUMBER ||
			RendererData.TextureSlotsCounter + mesh.Textures.size() >= MAX_TEXTURE_SLOTS)
			Flush();
		if (RendererData.VertexCounter + mesh.Vertices.size() >= MAX_VERTEX_NUMBER ||
			RendererData.IndexCounter + mesh.Indices.size() >= MAX_INDEX_NUMBER ||
			RendererData.TextureSlotsCounter + mesh.Textures.size() >= MAX_TEXTURE_SLOTS)
			return;

		for (const auto& index : mesh.Indices)
		{
			RendererData.Indices[RendererData.IndexCounter++] = RendererData.VertexCounter + index;
		}

		for (auto vertex : mesh.Vertices)
		{
			float texIndex = -1.0f;
			if (vertex.TexIndex >= 0.0f)
				texIndex = GetTextureIndex(mesh.Textures[static_cast<int>(vertex.TexIndex)]);
			vertex.Position = (transform * Float4(vertex.Position, 1.0f)).xyz;
			vertex.Normal = (transform * Float4(vertex.Normal, 1.0f)).xyz;
			vertex.TexIndex = texIndex;
			RendererData.Vertices[RendererData.VertexCounter++] = vertex;
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

		std::array<int, MAX_TEXTURE_SLOTS> textureSlots;
		for (uint32_t i = 0; i < MAX_TEXTURE_SLOTS; i++)
			if (i < RendererData.TextureSlotsCounter)
			{
				std::dynamic_pointer_cast<OpenGLTexture>(RendererData.TextureSlots[i])->BindUnit(i);
				textureSlots[i] = i;
			}
			else textureSlots[i] = -1;
		m_Shader->SetIntArray("u_Textures", textureSlots);

		m_VertexArray->Bind();

		glDrawElements(GL_TRIANGLES, RendererData.IndexCounter, GL_UNSIGNED_INT, 0);

		RendererData.VertexCounter = 0;
		RendererData.IndexCounter = 0;
		RendererData.TextureSlotsCounter = 0;

		m_VertexArray->Unbind();
	}

	float OpenGLRenderer3D::GetTextureIndex(const std::shared_ptr<Texture>& texture)
	{
		float texIndex = -1.0f;
		if (texture)
		{
			// Check if texture allready exist in RendererData.TextureSlots
			for (uint32_t i = 0; i < RendererData.TextureSlotsCounter; i++)
			{
				if (texture == RendererData.TextureSlots[i])
					texIndex = static_cast<float>(i);
			}
			// Add the texture to RendererData.TextureSlots if it doesn't exist 
			if (texIndex == -1.0f)
			{
				if (RendererData.TextureSlotsCounter >= MAX_TEXTURE_SLOTS)
					Flush();
				texIndex = static_cast<float>(RendererData.TextureSlotsCounter);
				RendererData.TextureSlots[RendererData.TextureSlotsCounter++] = texture;
			}
		}
		return texIndex;
	}
}