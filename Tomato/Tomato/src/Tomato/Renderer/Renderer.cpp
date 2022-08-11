#include "pchTomato.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "App.h"


namespace Tomato
{
	std::array<Vertex, RendererData::MaxVertexNumber> RendererData::Vertices = std::array<Vertex, MaxVertexNumber>();
	UInt RendererData::VertexCounter = 0;
	std::array<UInt, RendererData::MaxIndexNumber> RendererData::Indices = std::array<UInt, MaxIndexNumber>();
	UInt RendererData::IndexCounter = 0;


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
	
		s_Instance->m_TextureCount = 0;
	}

	void Renderer::Terminate()
	{
		delete s_Instance;
	}

	void Renderer::Begin()
	{
		s_Instance->m_Shader->Use(true);

		s_Instance->m_Projection = App::GetCurrentCamera()->GetProjection();
		s_Instance->m_View = App::GetCurrentCamera()->GetView(true);
		
		s_Instance->m_Shader->SetMat4("u_Projection", s_Instance->m_Projection);
		s_Instance->m_Shader->SetMat4("u_View", s_Instance->m_View);
	}

	void Renderer::End()
	{
		Flush();

		s_Instance->m_Shader->Use(false);
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
				RendererData::IndexCounter + indices.size() >= RendererData::MaxIndexNumber)
				Flush();

			Int texture_id = static_cast<Int>(vertices[0].TexID);
			if (texture_id != -1)
			{
				bool found = false;
				for (UInt i = 0; i < s_Instance->m_TextureCount && !found; i++)
					if (texture_id == s_Instance->m_TextureIndices[i])
						found = true;

				if (!found)
				{
					if (s_Instance->m_TextureCount >= 8)
						Flush();
					s_Instance->m_TextureIndices[s_Instance->m_TextureCount++] = texture_id;
				}
			}

			for (const auto& index : indices)
			{
				RendererData::Indices[RendererData::IndexCounter++] = index + RendererData::VertexCounter;
			}

			for (auto& vertex : vertices)
			{
				Float3 coords = cube.TransformCoords(side.TransformCoords(vertex.Coords));
				RendererData::Vertices[RendererData::VertexCounter++] = Vertex(coords, vertex.Color, vertex.TexID, vertex.TexCoords);
			}
		}
	}

	Float Renderer::CreateTexture(std::string_view name, std::string_view path)
	{
		auto& ins = s_Instance;
		const char* c_name = name.data();

		for (const auto& [_name, _texture] : ins->m_Textures)
		{
			TOMATO_ASSERT(_name.compare(c_name) != 0, "Texture with name '{0}' already exist!", c_name);
		}

		ins->m_Textures.emplace_back(c_name, std::make_shared<Texture>(path));
		return static_cast<Float>(ins->m_Textures.size() - 1);
	}

	Float Renderer::GetTextureID(std::string_view name)
	{
		for (UInt i = 0; i < s_Instance->m_Textures.size(); i++)
			if (s_Instance->m_Textures[i].first.compare(name.data()) == 0)
				return static_cast<Float>(i);

		TOMATO_WARNING("Texture '{0}' not found!", name.data());
		return -1.0f;
	}

	void Renderer::Flush()
	{
		auto& ins = s_Instance;

		ins->m_Shader->SetIntArray("u_Textures", ins->m_TextureIndices);

		ins->m_VertexBuffer->Bind();
		ins->m_VertexBuffer->SetData(RendererData::Vertices, RendererData::VertexCounter);
		ins->m_VertexBuffer->Unbind();

		ins->m_VertexArray->Bind();

		ins->m_IndexBuffer->Bind();
		ins->m_IndexBuffer->SetData(RendererData::Indices, RendererData::IndexCounter);
		ins->m_IndexBuffer->Unbind();

		for (UInt i = 0; i < ins->m_TextureCount; i++)
		{
			Int unit = ins->m_TextureIndices[i];
			const auto& texture = ins->m_Textures[unit].second;
			texture->BindUnit(unit);
		}

		ins->m_TextureCount = 0;

		glDrawElements(GL_TRIANGLES, RendererData::IndexCounter, GL_UNSIGNED_INT, nullptr);

		RendererData::VertexCounter = 0;
		RendererData::IndexCounter = 0;

		VertexArray::Unbind();
	}
}
