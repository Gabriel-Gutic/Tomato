#include "pchTomato.h"
#include "OpenGLRenderer3D.h"

#include "RendererAPI/RendererData.h"
#include "RendererAPI/OpenGL/OpenGLTexture.h"
#include "RendererAPI/OpenGL/OpenGLFrameBuffer.h"
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
		m_VertexArray = std::move(VertexArray::CreateUnique({3, 4, 3, 2, 1}));
		
		m_TextShader = std::move(Shader::CreateUnique("assets/Shaders/3D/VertexShader.glsl", "assets/Shaders/3D/TextFragmentShader.glsl"));
		m_TextVertexBuffer = std::move(VertexBuffer::CreateUnique(MAX_VERTEX_NUMBER * sizeof(Mesh::Vertex), BufferAllocType::Dynamic));
		m_TextIndexBuffer = std::move(IndexBuffer::CreateUnique(MAX_INDEX_NUMBER, BufferAllocType::Dynamic));
		m_TextVertexArray = std::move(VertexArray::CreateUnique({ 3, 4, 3, 2, 1 }));

		m_LineShader = std::move(Shader::CreateUnique("assets/Shaders/3D/LineVertexShader.glsl", "assets/Shaders/3D/LineFragmentShader.glsl"));
		m_LineVertexBuffer = std::move(VertexBuffer::CreateUnique(MAX_VERTEX_NUMBER * sizeof(Line::Vertex), BufferAllocType::Dynamic));
		m_LineVertexArray = std::move(VertexArray::CreateUnique({ 3, 4 }));

		m_FrameBuffer = nullptr;

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glLineWidth(3.0);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glCullFace(GL_FRONT);
		//glFrontFace(GL_CW);
	}

	OpenGLRenderer3D::~OpenGLRenderer3D()
	{
	}

	void OpenGLRenderer3D::Begin()
	{
		bool drawToFramebuffer = m_FrameBuffer != nullptr;
		if (drawToFramebuffer)
		{
			const auto& [w, h] = App::GetWindow()->GetSize().data;
			m_FrameBuffer->SetSize(w, h);
			std::dynamic_pointer_cast<OpenGLFrameBuffer>(m_FrameBuffer)->Bind();
			std::dynamic_pointer_cast<OpenGLTexture>(m_FrameBuffer->GetTexture())->Bind();

			//glCullFace(GL_FRONT);
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
			//glCullFace(GL_BACK);
		}
		
		Clear();
		
		Mat4 vp = App::GetCurrentScene()->GetProjectionView(drawToFramebuffer);

		m_Shader->SetMat4("u_VP", vp);
		m_Shader->SetFloat3("u_CameraPosition", App::GetCurrentCamera()->GetComponent<TransformComponent>().Position);
		m_Shader->SetFloat3("u_CameraTarget", App::GetCurrentCamera()->GetComponent<CameraComponent>().Target);
		m_Shader->SetFloat3("u_LightSource", GetLight());
		m_Shader->SetFloat("u_IsUsingLight", static_cast<float>(m_IsUsingLight));

		m_LineShader->SetMat4("u_VP", vp);
		m_TextShader->SetMat4("u_VP", vp);
	}

	void OpenGLRenderer3D::End()
	{
		Flush();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void DrawLine()
	{
		
	}

	void OpenGLRenderer3D::Clear() const
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(
			m_BackgroundColor.r, 
			m_BackgroundColor.g,
			m_BackgroundColor.b,
			m_BackgroundColor.a
		);
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
		TOMATO_BENCHMARKING_FUNCTION();

		m_Shader->Use();
		m_VertexArray->Bind();

		m_VertexBuffer->Bind();
		m_VertexBuffer->SetData(m_Data.Vertices, m_Data.VertexCounter);
		m_VertexBuffer->Unbind();

		m_IndexBuffer->Bind();
		m_IndexBuffer->SetData(m_Data.Indices, m_Data.IndexCounter);
		m_IndexBuffer->Unbind();

		for (uint32_t i = 0; i < m_Data.TextureSlotsCounter; i++)
			std::dynamic_pointer_cast<OpenGLTexture>(m_Data.TextureSlots[i])->BindUnit(i);
		
		m_Shader->SetIntArray("u_Textures", OpenGLRenderer3DData::TextureUnits);


		glDrawElements(GL_TRIANGLES, m_Data.IndexCounter, GL_UNSIGNED_INT, 0);

		m_Data.VertexCounter = 0;
		m_Data.IndexCounter = 0;
		m_Data.TextureSlotsCounter = 0;

		m_VertexArray->Unbind();

		m_LineShader->Use();
		
		m_LineVertexArray->Bind();

		m_LineVertexBuffer->Bind();
		m_LineVertexBuffer->SetData(m_Data.LineVertices, m_Data.LineVertexCounter);
		m_LineVertexBuffer->Unbind();
		
		glDrawArrays(GL_LINES, 0, m_Data.LineVertexCounter);
		
		m_Data.LineVertexCounter = 0;
		
		m_LineVertexArray->Unbind();

		// Draw Text
		m_TextShader->Use();
		m_TextVertexArray->Bind();

		m_TextVertexBuffer->Bind();
		m_TextVertexBuffer->SetData(m_Data.TextVertices, m_Data.TextVertexCounter);
		m_TextVertexBuffer->Unbind();

		m_TextIndexBuffer->Bind();
		m_TextIndexBuffer->SetData(m_Data.TextIndices, m_Data.TextIndexCounter);
		m_TextIndexBuffer->Unbind();

		for (uint32_t i = 0; i < m_Data.TextTextureSlotsCounter; i++)
			std::dynamic_pointer_cast<OpenGLTexture>(m_Data.TextTextureSlots[i])->BindUnit(i);

		m_TextShader->SetIntArray("u_Textures", OpenGLRenderer3DData::TextureUnits);


		glDrawElements(GL_TRIANGLES, m_Data.TextIndexCounter, GL_UNSIGNED_INT, 0);

		m_Data.TextVertexCounter = 0;
		m_Data.TextIndexCounter = 0;
		m_Data.TextTextureSlotsCounter = 0;

		m_TextVertexArray->Unbind();
	}
}