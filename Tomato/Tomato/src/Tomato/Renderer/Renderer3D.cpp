#include "pchTomato.h"
#include "Renderer3D.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLRenderer3D.h"
#include "RendererAPI/DirectX/DirectXRenderer3D.h"


namespace Tomato
{
	Renderer3D* Renderer3D::s_Instance = nullptr;
	Renderer3D::Renderer3D()
		:m_BackgroundColor(0.0f, 0.0f, 0.0f, 1.0f), 
		m_IsUsingLight(false), m_LightSource()
	{
	}

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
			vertex.Position = transform * vertex.Position;
			vertex.Normal = transform * vertex.Normal;
			vertex.TexIndex = texIndex;
			m_Data.Vertices[m_Data.VertexCounter++] = vertex;
		}
	}

	void Renderer3D::DrawTriangle(const Float3& A, const Float3& B, const Float3& C, const Float3& color, const float alpha, const Mat4& transform)
	{
		Float3 u = B - A;
		Float3 v = C - A;
		Float3 normal = Float3::CrossProduct(u, v);

		Mesh mesh;
		mesh.Vertices.emplace_back(A, Float4(color, alpha), normal);
		mesh.Vertices.emplace_back(B, Float4(color, alpha), normal);
		mesh.Vertices.emplace_back(C, Float4(color, alpha), normal);

		mesh.Indices = { 0, 1, 2 };
		Draw(mesh, transform);
	}

	void Renderer3D::DrawTriangle(const Float3& center,
		const Float3& color, 
		float scale, 
		const float alpha, 
		const Mat4& transform)
	{
		Mesh mesh = Mesh::TriangleMesh();
		for (auto& vertex : mesh.Vertices)
		{
			vertex.Color = Float4(color, alpha);
		}
		Mat4 tran = Math::Translate(center) * transform * Math::Scale(Float3(scale, scale, 1.0f));
		Draw(mesh, tran);
	}

	void Renderer3D::DrawQuad(const Float3& A, const Float3& B, const Float3& C, const Float3& D, const Float3& color, const float alpha, const Mat4& transform)
	{
		DrawTriangle(A, B, C, color, alpha, transform);
		DrawTriangle(A, C, D, color, alpha, transform);
	}

	void Renderer3D::DrawSquare(const Float3& center, 
		const Float3& color, 
		float scale, 
		const float alpha, 
		const Mat4& transform)
	{
		Mesh mesh = Mesh::QuadMesh();
		for (auto& vertex : mesh.Vertices)
		{
			vertex.Color = Float4(color, alpha);
		}
		Mat4 tran = Math::Translate(center) * transform * Math::Scale(Float3(scale, scale, 1.0f));
		Draw(mesh, tran);
	}

	void Renderer3D::DrawLine(const Float3& A, const Float3& B, const Float3& color)
	{
		auto& index = m_Data.LineVertexCounter;
		if (index + 2 >= MAX_VERTEX_NUMBER)
			Flush();

		m_Data.LineVertices[index++] = Line::Vertex(A, color);
		m_Data.LineVertices[index++] = Line::Vertex(B, color);
	}

	void Renderer3D::RenderText(std::string_view text, const Font& font, const Float3& center, const Float4& color, float fontSize, const Float3& rotation)
	{
		Mat4 tran = Quaternion::Rotation(rotation).ToMat4();
		tran = Math::Translate(center) * tran;

		Float2 size = font.GetSize(text, fontSize);

		float x = -size.x / 2.0f;
		float y = -size.y / 2.0f;

		fontSize = fontSize / 1200.0f;

		for (const auto& c : text)
		{
			const auto& ch = font[c];
			float xpos = x + ch.Bearing.x * fontSize;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * fontSize;

			float w = ch.Size.x * fontSize;
			float h = ch.Size.y * fontSize;

			Mesh mesh;
			mesh.Vertices.resize(4);

			mesh.Vertices[0] = Mesh::Vertex(
				Float3(xpos, ypos + h, 0.0f),
				color,
				Float3(0.0f, 0.0f, 1.0f),
				Float2(0.0f, 0.0f),
				0.0f
			);
			mesh.Vertices[1] = Mesh::Vertex(
				Float3(xpos + w, ypos, 0.0f),
				color,
				Float3(0.0f, 0.0f, 1.0f),
				Float2(1.0f, 1.0f),
				0.0f
			);
			mesh.Vertices[2] = Mesh::Vertex(
				Float3(xpos, ypos, 0.0f),
				color,
				Float3(0.0f, 0.0f, 1.0f),
				Float2(0.0f, 1.0f),
				0.0f
			);
			mesh.Vertices[3] = Mesh::Vertex(
				Float3(xpos + w, ypos + h, 0.0f),
				color,
				Float3(0.0f, 0.0f, 1.0f),
				Float2(1.0f, 0.0f),
				0.0f
			);

			mesh.Indices = { 0, 2, 1, 0, 1, 3 };
			mesh.Textures.push_back(ch.Texture);
			DrawTextMesh(mesh, tran);

			x += (ch.Advance >> 6) * fontSize;
		}
	}

	void Renderer3D::DrawTextMesh(const Mesh& mesh, const Mat4& transform)
	{
		if (m_Data.TextVertexCounter + mesh.Vertices.size() >= MAX_VERTEX_NUMBER ||
			m_Data.TextIndexCounter + mesh.Indices.size() >= MAX_INDEX_NUMBER ||
			m_Data.TextTextureSlotsCounter + mesh.Textures.size() >= MAX_TEXTURE_SLOTS)
			Flush();
		if (m_Data.TextVertexCounter + mesh.Vertices.size() >= MAX_VERTEX_NUMBER ||
			m_Data.TextIndexCounter + mesh.Indices.size() >= MAX_INDEX_NUMBER ||
			m_Data.TextTextureSlotsCounter + mesh.Textures.size() >= MAX_TEXTURE_SLOTS)
			return;

		for (const auto& index : mesh.Indices)
		{
			m_Data.TextIndices[m_Data.TextIndexCounter++] = m_Data.TextVertexCounter + index;
		}

		for (auto vertex : mesh.Vertices)
		{
			float texIndex = -1.0f;
			if (vertex.TexIndex >= 0.0f)
				texIndex = GetTextureIndex(mesh.Textures[static_cast<int>(vertex.TexIndex)]);
			vertex.Position = (transform * Float4(vertex.Position, 1.0f)).xyz;
			vertex.Normal = (transform * Float4(vertex.Normal, 1.0f)).xyz;
			vertex.TexIndex = texIndex;
			m_Data.TextVertices[m_Data.TextVertexCounter++] = vertex;
		}
	}

	const Float4& Renderer3D::GetBackgroundColor()
	{
		return s_Instance->m_BackgroundColor;
	}

	void Renderer3D::SetBackgroundColor(const Float4& bgcolor)
	{
		s_Instance->m_BackgroundColor = bgcolor;
	}

	void Renderer3D::SetLight(const Float3& lightSource)
	{
		s_Instance->m_LightSource = lightSource;
		s_Instance->m_IsUsingLight = true;
	}

	void Renderer3D::RemoveLight()
	{
		s_Instance->m_IsUsingLight = false;
	}

	const Float3& Renderer3D::GetLight()
	{
		return s_Instance->m_LightSource;
	}

	Renderer3D* Renderer3D::Get()
	{
		return s_Instance;
	}

	void Renderer3D::SetFrameBuffer(const std::shared_ptr<FrameBuffer>& fb)
	{
		s_Instance->m_FrameBuffer = fb;
	}

	const std::shared_ptr<FrameBuffer>& Renderer3D::GetFrameBuffer()
	{
		return s_Instance->m_FrameBuffer;
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
