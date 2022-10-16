#include "pchTomato.h"
#include "OpenGLRenderer3D.h"

#include "RendererAPI/RendererData.h"
#include "RendererAPI/OpenGL/OpenGLTexture.h"
#include "Tomato/Core/App/App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Tomato
{
	struct OpenGLRenderer3DData
	{
		static const std::array<int, MAX_TEXTURE_SLOTS> TextureUnits;
	};
	const std::array<int, MAX_TEXTURE_SLOTS> OpenGLRenderer3DData::TextureUnits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

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
		OpenGLRenderer3D::Clear(0.0f, 0.0f, 0.0f, 1.0f);

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

	void OpenGLRenderer3D::Flush()
	{
		m_Shader->Use();

		m_VertexBuffer->Bind();
		m_VertexBuffer->SetData(m_Data.Vertices, m_Data.VertexCounter);
		m_VertexBuffer->Unbind();

		m_IndexBuffer->Bind();
		m_IndexBuffer->SetData(m_Data.Indices, m_Data.IndexCounter);
		m_IndexBuffer->Unbind();

		for (uint32_t i = 0; i < m_Data.TextureSlotsCounter; i++)
			std::dynamic_pointer_cast<OpenGLTexture>(m_Data.TextureSlots[i])->BindUnit(i);
		
		m_Shader->SetIntArray("u_Textures", OpenGLRenderer3DData::TextureUnits);

		m_VertexArray->Bind();

		glDrawElements(GL_TRIANGLES, m_Data.IndexCounter, GL_UNSIGNED_INT, 0);

		m_Data.VertexCounter = 0;
		m_Data.IndexCounter = 0;
		m_Data.TextureSlotsCounter = 0;

		m_VertexArray->Unbind();
	}
}