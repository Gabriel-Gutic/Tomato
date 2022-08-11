#include "pchTomato.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "App.h"
#include "GUI/GUI.h"


namespace Tomato
{
	std::array<Vertex, RendererData::MaxVertexNumber> RendererData::Vertices = std::array<Vertex, MaxVertexNumber>();
	UInt RendererData::VertexCounter = 0;
	std::array<UInt, RendererData::MaxIndexNumber> RendererData::Indices = std::array<UInt, MaxIndexNumber>();
	UInt RendererData::IndexCounter = 0;

	std::array<std::shared_ptr<Texture>, RendererData::MaxTextureSlots> RendererData::TextureSlots = std::array < std::shared_ptr<Texture>, RendererData::MaxTextureSlots>();
	UInt RendererData::TextureSlotsCounter = 0;


	Renderer* Renderer::s_Instance = nullptr;
	void Renderer::Initialize()
	{
		TOMATO_ASSERT(!s_Instance, "Renderer already initialized!");

		s_Instance = new Renderer();

		s_Instance->m_Shader = std::make_unique<Shader>("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");
		
		s_Instance->m_VertexBuffer = std::make_unique<VertexBuffer>(RendererData::MaxVertexNumber);
		s_Instance->m_IndexBuffer = std::make_unique<IndexBuffer>(RendererData::MaxVertexNumber);

		s_Instance->m_VertexArray = std::make_unique<VertexArray>();

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		s_Instance->m_FrameBuffer = std::make_unique<FrameBuffer>();
	}

	void Renderer::Terminate()
	{
		delete s_Instance;
	}

	void Renderer::Begin()
	{
		const auto& window = App::GetWindow();

		bool renderWindow = GUI::IsRenderWindowShown();
		if (renderWindow)
		{
			s_Instance->m_FrameBuffer->SetSize(window->GetWidth(), window->GetHeight());
			s_Instance->m_FrameBuffer->Bind();
			s_Instance->m_FrameBuffer->GetTexture()->Bind();
		}
		else {
			s_Instance->m_FrameBuffer->Unbind();
		}

		window->Clear(1.0f, 0.0f, 0.0f);

		s_Instance->m_Shader->Use(true);

		s_Instance->m_Projection = App::GetCurrentCamera()->GetProjection();
		s_Instance->m_View = App::GetCurrentCamera()->GetView(renderWindow);
		
		s_Instance->m_Shader->SetMat4("u_Projection", s_Instance->m_Projection);
		s_Instance->m_Shader->SetMat4("u_View", s_Instance->m_View);
	}

	void Renderer::End()
	{
		Flush();

		s_Instance->m_Shader->Use(false);

		s_Instance->m_FrameBuffer->Unbind();
	}

	Renderer* Renderer::Get()
	{
		return s_Instance;
	}

	const std::unique_ptr<FrameBuffer>& Renderer::GetFrameBuffer()
	{
		return s_Instance->m_FrameBuffer;
	}

	void Renderer::Flush()
	{
		auto& ins = s_Instance;

		for (UInt i = 0; i < RendererData::TextureSlotsCounter; i++)
		{
			RendererData::TextureSlots[i]->BindUnit(i);
		}

		std::array<int, RendererData::MaxTextureSlots> arr;
		for (UInt i = 0; i < RendererData::MaxTextureSlots; i++)
			arr[i] = i;

		ins->m_Shader->SetIntArray("u_Textures", arr);

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
		RendererData::TextureSlotsCounter = 0;

		VertexArray::Unbind();
	}
}
