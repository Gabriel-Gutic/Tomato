#include "pchTomato.h"
#include "Renderer3D.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLRenderer3D.h"
#include "RendererAPI/DirectX/DirectXRenderer3D.h"


namespace Tomato
{
	Renderer3D* Renderer3D::s_Instance = nullptr;
	void Renderer3D::Initialize()
	{
		TOMATO_ASSERT(!s_Instance, "Renderer3D already initialized!");
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			s_Instance = new OpenGLRenderer3D();
			break;
		case RendererAPI::Type::DirectX:
			s_Instance = new DirectXRenderer3D();
			break;
		}
		TOMATO_ASSERT(s_Instance, "Failed to initialize Renderer3D!");
	}

	void Renderer3D::Terminate()
	{
		delete s_Instance;
	}

	void Renderer3D::Clear(const Float4& color) const
	{
		this->Clear(color.x, color.y, color.z, color.w);
	}

	void Renderer3D::Draw(const Mesh& mesh, const Mat4& transform)
	{
		if (m_Data.VertexCounter + mesh.Vertices.size() >= MAX_VERTEX_NUMBER ||
			m_Data.IndexCounter + mesh.Indices.size() >= MAX_INDEX_NUMBER ||
			m_Data.TextureSlotsCounter + mesh.Textures.size() >= MAX_TEXTURE_SLOTS)
			Flush();
		if (m_Data.VertexCounter + mesh.Vertices.size() >= MAX_VERTEX_NUMBER ||
			m_Data.IndexCounter + mesh.Indices.size() >= MAX_INDEX_NUMBER ||
			m_Data.TextureSlotsCounter + mesh.Textures.size() >= MAX_TEXTURE_SLOTS)
			return;

		for (const auto& index : mesh.Indices)
		{
			m_Data.Indices[m_Data.IndexCounter++] = m_Data.VertexCounter + index;
		}

		for (auto vertex : mesh.Vertices)
		{
			float texIndex = -1.0f;
			if (vertex.TexIndex >= 0.0f)
				texIndex = GetTextureIndex(mesh.Textures[static_cast<int>(vertex.TexIndex)]);
			vertex.Position = (transform * Float4(vertex.Position, 1.0f)).xyz;
			vertex.Normal = (transform * Float4(vertex.Normal, 1.0f)).xyz;
			vertex.TexIndex = texIndex;
			m_Data.Vertices[m_Data.VertexCounter++] = vertex;
		}
	}

	Renderer3D* Renderer3D::Get()
	{
		return s_Instance;
	}

	float Renderer3D::GetTextureIndex(const std::shared_ptr<Texture>& texture)
	{
		float texIndex = -1.0f;
		if (texture)
		{
			// Check if texture allready exist in RendererData.TextureSlots
			for (uint32_t i = 0; i < m_Data.TextureSlotsCounter; i++)
			{
				if (texture == m_Data.TextureSlots[i])
					texIndex = static_cast<float>(i);
			}
			// Add the texture to RendererData.TextureSlots if it doesn't exist 
			if (texIndex == -1.0f)
			{
				if (m_Data.TextureSlotsCounter >= MAX_TEXTURE_SLOTS)
					Flush();
				texIndex = static_cast<float>(m_Data.TextureSlotsCounter);
				m_Data.TextureSlots[m_Data.TextureSlotsCounter++] = texture;
			}
		}
		return texIndex;
	}
}
