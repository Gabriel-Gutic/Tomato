#include "pchTomato.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core/App/App.h"
#include "GUI/GUI.h"


namespace Tomato
{
	RendererType Renderer::s_Type = RendererType::_3D;
	RendererType Renderer::GetType()
	{
		return s_Type;
	}

	// Old Renderer

	//struct RendererData
	//{
	//	static const unsigned int MaxVertexNumber = 16384;
	//	static std::array<Vertex, MaxVertexNumber> Vertices;
	//	static unsigned int VertexCounter;
	//
	//};
	//std::array<Vertex, RendererData::MaxVertexNumber> RendererData::Vertices = std::array<Vertex, MaxVertexNumber>();
	//unsigned int RendererData::VertexCounter = 0;
	//
	//std::array<std::shared_ptr<Texture>, RendererData::MaxTextureSlots> RendererData::TextureSlots = std::array < std::shared_ptr<Texture>, RendererData::MaxTextureSlots>();
	//unsigned int RendererData::TextureSlotsCounter = 0;

	/*
	Renderer* Renderer::s_Instance = nullptr;
	void Renderer::Initialize()
	{
		TOMATO_ASSERT(!s_Instance, "Renderer already initialized!");

		s_Instance = new Renderer();

		// Drawing
		s_Instance->m_Shader = std::move(Shader::CreateUnique("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl"));
		s_Instance->m_VertexBuffer = std::move(VertexBuffer::CreateUnique(RendererData::MaxVertexNumber * sizeof(Vertex), BufferAllocType::Dynamic));
		s_Instance->m_VertexArray = std::move(VertexArray::CreateUnique());

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

		//window->Clear(s_Instance->m_BackgroundColor);

		s_Instance->m_Shader->Use();

		s_Instance->m_VP = App::GetCurrentScene()->GetViewProjection(renderWindow);
		s_Instance->m_Shader->SetMat4("u_VP", s_Instance->m_VP);
	}

	void Renderer::End()
	{
		TOMATO_BENCHMARKING_FUNCTION();
		Flush();

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

	unsigned int Renderer::GetNumberOfVertices()
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

	void Renderer::Draw(const Entity& entity, const std::shared_ptr<Texture>& texture, const Mat4& transform)
	{
		if (!entity.HasComponent<MeshRendererComponent>())
			return;

		const auto& mesh = entity.GetComponent<MeshRendererComponent>();
		if (RendererData::VertexCounter + mesh.mesh.Indices.size() >= RendererData::MaxVertexNumber)
			Flush();

		float texIndex = GetTextureIndex(texture);

		bool hasTransform = false;
		Mat4 tran(1.0f);
		if (entity.HasComponent<TransformComponent>())
		{
			hasTransform = true;
			tran = entity.GetComponent<TransformComponent>().Get();
		}

		for (unsigned int i = 0; i < mesh.mesh.Indices.size(); i++)
		{
			unsigned int index = mesh.mesh.Indices[i];
			auto vertex = mesh.mesh.Vertices[index];
			if (hasTransform)
				vertex.Position = (transform * tran * Float4(vertex.Position, 1.0f)).xyz;
			RendererData::Vertices[RendererData::VertexCounter++] = Vertex(vertex.Position, mesh.Color, texIndex, vertex.TexCoords);
		}
	}

	// TODO: TexCoords for other entities than quad
	void Renderer::Draw(const Entity& entity, const std::shared_ptr<Tilemap>& tilemap, unsigned int row, unsigned int col, unsigned int rowspan, unsigned int colspan, const Mat4& transform)
	{
		if (!entity.HasComponent<MeshRendererComponent>())
			return;

		const auto& mesh = entity.GetComponent<MeshRendererComponent>();
		if (RendererData::VertexCounter + mesh.mesh.Indices.size() >= RendererData::MaxVertexNumber)
			Flush();

		float texIndex = GetTextureIndex(tilemap->GetTexture());

		std::vector<Vertex> vertices;
		size_t size = mesh.mesh.Vertices.size();
		vertices.resize(size);

		auto texCoords = tilemap->GetTexCoords(row, col, rowspan, colspan);
		for (unsigned int i = 0; i < size; i++)
		{
			vertices[i].Coords = mesh.mesh.Vertices[i].Position;
			vertices[i].Color = mesh.Color;
			vertices[i].TexCoords = texCoords[i];
			vertices[i].TexIndex = texIndex;
		}

		bool hasTransform = false;
		Mat4 tran(1.0f);
		if (entity.HasComponent<TransformComponent>())
		{
			hasTransform = true;
			tran = entity.GetComponent<TransformComponent>().Get();
		}

		for (unsigned int i = 0; i < mesh.mesh.Indices.size(); i++)
		{
			unsigned int index = mesh.mesh.Indices[i];
			auto vertex = vertices[index];
			if (hasTransform)
				vertex.Coords = (transform * tran * Float4(vertex.Coords, 1.0f)).xyz;
			RendererData::Vertices[RendererData::VertexCounter++] = vertex;
		}
	}

	void Renderer::DrawText(std::string_view text, const Font& font, const Mat4& transform)
	{
		auto& ins = s_Instance;
		// activate corresponding render state	
		ins->m_Shader->Use();
		ins->m_VertexArray->Bind();

		float scale = 0.01f;

		// iterate through all characters
		float x = 0.0f;
		for (const auto c : text)
		{
			auto& ch = font[c];

			float xpos = x + ch.Bearing.x * scale;
			float ypos = - (ch.Size.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;

			auto color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

			auto texIndex = GetTextureIndex(ch.Texture);

			if (RendererData::VertexCounter + 6 >= RendererData::MaxVertexNumber)
				Flush();

			std::array<Float4, 6> coords;
			coords[0] = Float4(xpos, ypos + h, 0.0f, 1.0f);
			coords[1] = Float4(xpos, ypos, 0.0f, 1.0f);
			coords[2] = Float4(xpos + w, ypos, 0.0f, 1.0f);
			coords[3] = Float4(xpos, ypos + h, 0.0f, 1.0f);
			coords[4] = Float4(xpos + w, ypos, 0.0f, 1.0f);
			coords[5] = Float4(xpos + w, ypos + h, 0.0f, 1.0f);

			RendererData::Vertices[RendererData::VertexCounter++] = Vertex((transform * coords[0]).xyz, color, texIndex, Float2(0.0f, 0.0f), 1.0f);
			RendererData::Vertices[RendererData::VertexCounter++] = Vertex((transform * coords[1]).xyz, color, texIndex, Float2(0.0f, 1.0f), 1.0f);
			RendererData::Vertices[RendererData::VertexCounter++] = Vertex((transform * coords[2]).xyz, color, texIndex, Float2(1.0f, 1.0f), 1.0f);

			RendererData::Vertices[RendererData::VertexCounter++] = Vertex((transform * coords[3]).xyz, color, texIndex, Float2(0.0f, 0.0f), 1.0f);
			RendererData::Vertices[RendererData::VertexCounter++] = Vertex((transform * coords[4]).xyz, color, texIndex, Float2(1.0f, 1.0f), 1.0f);
			RendererData::Vertices[RendererData::VertexCounter++] = Vertex((transform * coords[5]).xyz, color, texIndex, Float2(1.0f, 0.0f), 1.0f);
		
			x += (ch.Advance >> 6) * scale;
		}

		ins->m_VertexArray->Unbind();
	}

	void Renderer::Flush()
	{
		TOMATO_BENCHMARKING_FUNCTION();

		auto& ins = s_Instance;

		for (unsigned int i = 0; i < RendererData::TextureSlotsCounter; i++)
		{
			//RendererData::TextureSlots[i]->BindUnit(i);
		}

		std::array<int, RendererData::MaxTextureSlots> arr;
		for (unsigned int i = 0; i < RendererData::MaxTextureSlots; i++)
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

		ins->m_VertexArray->Unbind();
	}

	float Renderer::GetTextureIndex(const std::shared_ptr<Texture>& texture)
	{
		float texIndex = -1.0f;
		if (texture)
		{
			for (unsigned int i = 0; i < RendererData::TextureSlotsCounter; i++)
			{
				if (texture == RendererData::TextureSlots[i])
					texIndex = static_cast<float>(i);
			}
			if (texIndex == -1.0f)
			{
				if (RendererData::TextureSlotsCounter >= RendererData::MaxTextureSlots)
					Flush();
				texIndex = static_cast<float>(RendererData::TextureSlotsCounter);
				RendererData::TextureSlots[RendererData::TextureSlotsCounter++] = texture;
			}
		}
		return texIndex;
	}
	*/
}
