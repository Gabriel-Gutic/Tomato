#include "pchTomato.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "App.h"
#include "GUI/GUI.h"


namespace Tomato
{
	struct RendererData
	{
		static const UInt MaxVertexNumber = 2048;
		static std::array<Vertex, MaxVertexNumber> Vertices;
		static UInt VertexCounter;

		static const UInt MaxTextureSlots = 32;
		static std::array<std::shared_ptr<Texture>, MaxTextureSlots> TextureSlots;
		static UInt TextureSlotsCounter;
	};
	std::array<Vertex, RendererData::MaxVertexNumber> RendererData::Vertices = std::array<Vertex, MaxVertexNumber>();
	UInt RendererData::VertexCounter = 0;

	std::array<std::shared_ptr<Texture>, RendererData::MaxTextureSlots> RendererData::TextureSlots = std::array < std::shared_ptr<Texture>, RendererData::MaxTextureSlots>();
	UInt RendererData::TextureSlotsCounter = 0;


	Renderer* Renderer::s_Instance = nullptr;
	void Renderer::Initialize()
	{
		TOMATO_ASSERT(!s_Instance, "Renderer already initialized!");

		s_Instance = new Renderer();

		s_Instance->m_Shader = std::make_unique<Shader>("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");
		
		s_Instance->m_VertexBuffer = std::make_unique<VertexBuffer>(RendererData::MaxVertexNumber);

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
		TOMATO_BENCHMARKING_FUNCTION();

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

		window->Clear(s_Instance->m_BackgroundColor);

		s_Instance->m_Shader->Use(true);

		s_Instance->m_Projection = App::GetCurrentCamera()->GetProjection();
		s_Instance->m_View = App::GetCurrentCamera()->GetView(renderWindow);
		
		s_Instance->m_Shader->SetMat4("u_Projection", s_Instance->m_Projection);
		s_Instance->m_Shader->SetMat4("u_View", s_Instance->m_View);
	}

	void Renderer::End()
	{
		TOMATO_BENCHMARKING_FUNCTION();
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

	void Renderer::SetBackgroundColor(const Float4& color)
	{
		s_Instance->m_BackgroundColor = color;
	}

	void Renderer::Draw(const Triangle& obj, std::shared_ptr<Texture> texture, const Transform& transform)
	{
		auto& vertices = obj.GetVertices();
		if (RendererData::VertexCounter + vertices.size() >= RendererData::MaxVertexNumber)
			Flush();

		Float texIndex = -1.0f;
		if (texture)
		{
			for (UInt i = 0; i < RendererData::TextureSlotsCounter; i++)
			{
				if (texture == RendererData::TextureSlots[i])
					texIndex = static_cast<Float>(texIndex);
			}
			if (texIndex == -1.0f)
			{
				if (RendererData::TextureSlotsCounter >= RendererData::MaxTextureSlots)
					Flush();
				texIndex = static_cast<Float>(RendererData::TextureSlotsCounter);
				RendererData::TextureSlots[RendererData::TextureSlotsCounter++] = texture;
			}
		}

		for (auto& vertex : vertices)
		{
			Float3 coords = transform.Apply(obj.TransformCoords(vertex.Coords));
			RendererData::Vertices[RendererData::VertexCounter++] = Vertex(coords, vertex.Color, texIndex, vertex.TexCoords);
		}
	}

	void Renderer::Draw(const Quad& obj, std::shared_ptr<Texture> texture, const Transform& transform)
	{
		auto& vertices = obj.GetVertices();
		auto indices = obj.GetIndices();
		if (RendererData::VertexCounter + indices.size() >= RendererData::MaxVertexNumber)
			Flush();

		Float texIndex = -1.0f;
		if (texture)
		{
			for (UInt i = 0; i < RendererData::TextureSlotsCounter; i++)
			{
				if (texture == RendererData::TextureSlots[i])
					texIndex = static_cast<Float>(texIndex);
			}
			if (texIndex == -1.0f)
			{
				if (RendererData::TextureSlotsCounter >= RendererData::MaxTextureSlots)
					Flush();
				texIndex = static_cast<Float>(RendererData::TextureSlotsCounter);
				RendererData::TextureSlots[RendererData::TextureSlotsCounter++] = texture;
			}
		}

		for (const auto& index : indices)
		{
			Float3 coords = transform.Apply(obj.TransformCoords(vertices[index].Coords));
			RendererData::Vertices[RendererData::VertexCounter++] = Vertex(coords, vertices[index].Color, texIndex, vertices[index].TexCoords);
		}
	}

	void Renderer::Draw(const Polygon& polygon, std::shared_ptr<Texture> texture, const Transform& transform)
	{
		auto& vertices = polygon.GetVertices();
		auto indices = polygon.GetIndices();
		if (RendererData::VertexCounter + indices.size() >= RendererData::MaxVertexNumber)
			Flush();

		Float texIndex = -1.0f;
		if (texture)
		{
			for (UInt i = 0; i < RendererData::TextureSlotsCounter; i++)
			{
				if (texture == RendererData::TextureSlots[i])
					texIndex = static_cast<Float>(texIndex);
			}
			if (texIndex == -1.0f)
			{
				if (RendererData::TextureSlotsCounter >= RendererData::MaxTextureSlots)
					Flush();
				texIndex = static_cast<Float>(RendererData::TextureSlotsCounter);
				RendererData::TextureSlots[RendererData::TextureSlotsCounter++] = texture;
			}
		}

		for (const auto& index : indices)
		{
			Float3 coords = transform.Apply(polygon.TransformCoords(vertices[index].Coords));
			RendererData::Vertices[RendererData::VertexCounter++] = Vertex(coords, vertices[index].Color, texIndex, vertices[index].TexCoords);
		}
	}

	void Renderer::Draw(const Circle& circle, std::shared_ptr<Texture> texture, const Transform& transform)
	{
		Renderer::Draw(circle.GetPolygon(), texture, transform);
	}

	void Renderer::Flush()
	{
		TOMATO_BENCHMARKING_FUNCTION();

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

		glDrawArrays(GL_TRIANGLES, 0, RendererData::VertexCounter);

		RendererData::VertexCounter = 0;
		RendererData::TextureSlotsCounter = 0;

		VertexArray::Unbind();
	}
}
