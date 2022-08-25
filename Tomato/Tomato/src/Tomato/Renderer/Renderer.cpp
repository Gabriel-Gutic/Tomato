#include "pchTomato.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core/App/App.h"
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

		s_Instance->m_VP = Mat4(1.0f);
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

		s_Instance->m_VP = App::GetCurrentScene()->GetViewProjection(renderWindow);
		s_Instance->m_Shader->SetMat4("u_VP", s_Instance->m_VP);
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

	UInt Renderer::GetNumberOfVertices()
	{
		return s_Instance->m_LastNumberOfVertices;
	}

	const Mat4& Renderer::GetViewProjection()
	{
		return s_Instance->m_VP;
	}

	void Renderer::SetBackgroundColor(const Float4& color)
	{
		s_Instance->m_BackgroundColor = color;
	}

	void Renderer::DrawTriangle(const Entity& entity, const std::shared_ptr<Texture>& texture, const Mat4& transform)
	{
		TOMATO_BENCHMARKING_FUNCTION();
		if (RendererData::VertexCounter + 3 >= RendererData::MaxVertexNumber)
			Flush();

		auto& rend = entity.GetComponent<Component::Renderer>();
		Float texIndex = GetTextureIndex(texture);

		Vertex v1;
		v1.Coords = Float3(0.0f, -0.5f + sqrtf(3) / 2.0f, 0.0f);
		v1.Color = rend.Color;
		v1.TexCoords = Float2(0.5f, 1.0f);
		v1.TexIndex = texIndex;

		Vertex v2;
		v2.Coords = Float3(-0.5f, -0.5f, 0.0f);
		v2.Color = rend.Color;
		v2.TexCoords = Float2(0.0f, 0.0f);
		v2.TexIndex = texIndex;

		Vertex v3;
		v3.Coords = Float3(0.5f, -0.5f, 0.0f);
		v3.Color = rend.Color;
		v3.TexCoords = Float2(1.0f, 0.0f);
		v3.TexIndex = texIndex;

		if (entity.HasComponent<Component::Transform>())
		{
			auto tran = entity.GetComponent<Component::Transform>().Get();

			v1.Coords = (tran * Float4(v1.Coords, 1.0f)).xyz;
			v2.Coords = (tran * Float4(v2.Coords, 1.0f)).xyz;
			v3.Coords = (tran * Float4(v3.Coords, 1.0f)).xyz;
		}
		v1.Coords = (transform * Float4(v1.Coords, 1.0f)).xyz;
		v2.Coords = (transform * Float4(v2.Coords, 1.0f)).xyz;
		v3.Coords = (transform * Float4(v3.Coords, 1.0f)).xyz;

		RendererData::Vertices[RendererData::VertexCounter++] = v1;
		RendererData::Vertices[RendererData::VertexCounter++] = v2;
		RendererData::Vertices[RendererData::VertexCounter++] = v3;
	}

	void Renderer::DrawQuad(const Entity& entity, const std::shared_ptr<Texture>& texture, const Mat4& transform)
	{
		TOMATO_BENCHMARKING_FUNCTION();
		if (RendererData::VertexCounter + 6 >= RendererData::MaxVertexNumber)
			Flush();

		auto& rend = entity.GetComponent<Component::Renderer>();
		Float texIndex = GetTextureIndex(texture);

		std::array<Vertex, 4> vertices;
		
		vertices[0].Coords = Float3(-0.5f, 0.5f, 0.0f);
		vertices[0].Color = rend.Color;
		vertices[0].TexCoords = Float2(0.0f, 1.0f);
		vertices[0].TexIndex = texIndex;

		vertices[1].Coords = Float3(-0.5f, -0.5f, 0.0f);
		vertices[1].Color = rend.Color;
		vertices[1].TexCoords = Float2(0.0f, 0.0f);
		vertices[1].TexIndex = texIndex;

		vertices[2].Coords = Float3(0.5f, -0.5f, 0.0f);
		vertices[2].Color = rend.Color;
		vertices[2].TexCoords = Float2(1.0f, 0.0f);
		vertices[2].TexIndex = texIndex;

		vertices[3].Coords = Float3(0.5f, 0.5f, 0.0f);
		vertices[3].Color = rend.Color;
		vertices[3].TexCoords = Float2(1.0f, 1.0f);
		vertices[3].TexIndex = texIndex;

		if (entity.HasComponent<Component::Transform>())
		{
			auto tran = entity.GetComponent<Component::Transform>().Get();

			for (auto& vertex : vertices)
				vertex.Coords = (tran * Float4(vertex.Coords, 1.0f)).xyz;
		}
		for (auto& vertex : vertices)
			vertex.Coords = (transform * Float4(vertex.Coords, 1.0f)).xyz;
		std::array<UInt, 6> indices = { 0, 1, 2, 1, 2, 3 };
		for (const auto& index : indices)
			RendererData::Vertices[RendererData::VertexCounter++] = vertices[index];
	}

	void Renderer::DrawQuad(const Entity& entity, const std::shared_ptr<Tilemap>& tilemap, UInt row, UInt col, UInt rowspan, UInt colspan, const Mat4& transform)
	{
		TOMATO_BENCHMARKING_FUNCTION();
		if (RendererData::VertexCounter + 6 >= RendererData::MaxVertexNumber)
			Flush();

		auto& rend = entity.GetComponent<Component::Renderer>();
		Float texIndex = GetTextureIndex(tilemap->GetTexture());

		std::array<Vertex, 4> vertices;
		vertices[0].Coords = Float3(-0.5f, -0.5f, 0.0f);
		vertices[1].Coords = Float3(-0.5f,  0.5f, 0.0f);
		vertices[2].Coords = Float3( 0.5f, -0.5f, 0.0f);
		vertices[3].Coords = Float3( 0.5f,  0.5f, 0.0f);

		auto texCoords = tilemap->GetTexCoords(row, col, rowspan, colspan);
		for (UInt i = 0; i < 4; i++)
		{
			vertices[i].Color = rend.Color;
			vertices[i].TexCoords = texCoords[i];
			vertices[i].TexIndex = texIndex;
		}
		
		if (entity.HasComponent<Component::Transform>())
		{
			auto tran = entity.GetComponent<Component::Transform>().Get();

			for (auto& vertex : vertices)
				vertex.Coords = (tran * Float4(vertex.Coords, 1.0f)).xyz;
		}
		for (auto& vertex : vertices)
			vertex.Coords = (transform * Float4(vertex.Coords, 1.0f)).xyz;

		std::array<UInt, 6> indices = { 0, 1, 2, 1, 2, 3 };
		for (const auto& index : indices)
			RendererData::Vertices[RendererData::VertexCounter++] = vertices[index];
	}

	void Renderer::DrawPolygon(const Entity& entity, const std::shared_ptr<Texture>& texture, const Mat4& transform)
	{
		const UInt nr = 6;
		std::vector<UInt> indices = Math::GeneratePolygonIndices(nr);
		TOMATO_BENCHMARKING_FUNCTION();
		if (RendererData::VertexCounter + indices.size() >= RendererData::MaxVertexNumber)
			Flush();

		auto& rend = entity.GetComponent<Component::Renderer>();
		Float texIndex = GetTextureIndex(texture);

		std::vector<Float2> coords = Math::GeneratePolygonCoords(nr);
		std::array<Vertex, nr + 1> vertices;

		for (UInt i = 0; i <= nr; i++)
		{
			vertices[i].Coords.xy = coords[i];
			vertices[i].Color = rend.Color;
			vertices[i].TexCoords = Float2();
			vertices[i].TexIndex = texIndex;
		}

		if (entity.HasComponent<Component::Transform>())
		{
			auto tran = entity.GetComponent<Component::Transform>().Get();

			for (auto& vertex : vertices)
				vertex.Coords = (tran * Float4(vertex.Coords, 1.0f)).xyz;
		}
		for (auto& vertex : vertices)
			vertex.Coords = (transform * Float4(vertex.Coords, 1.0f)).xyz;

		for (const auto& index : indices)
			RendererData::Vertices[RendererData::VertexCounter++] = vertices[index];
	}

	void Renderer::DrawCircle(const Entity& entity, const std::shared_ptr<Texture>& texture, const Mat4& transform)
	{
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

		ins->m_LastNumberOfVertices = RendererData::VertexCounter;
		RendererData::VertexCounter = 0;
		RendererData::TextureSlotsCounter = 0;

		VertexArray::Unbind();
	}

	Float Renderer::GetTextureIndex(const std::shared_ptr<Texture>& texture)
	{
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
		return texIndex;
	}
}
