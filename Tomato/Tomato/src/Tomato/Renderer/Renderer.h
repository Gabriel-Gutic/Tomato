#pragma once
#include "Shader.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Texture/Texture.h"
#include "Object/Object.h"
#include "Object/3D/Cube.h"


namespace Tomato
{
	struct RendererData
	{
		static const UInt MaxVertexNumber = 2048;
		static const UInt MaxIndexNumber = 16 * MaxVertexNumber;
		static std::array<Vertex, MaxVertexNumber> Vertices;
		static UInt VertexCounter;
		static std::array<UInt, MaxIndexNumber> Indices;
		static UInt IndexCounter;
	};

	class Renderer
	{
		Renderer() = default;
	public:
		Renderer(const Renderer&) = delete;

		static void Initialize();
		static void Terminate();

		static void Begin();
		static void End();

		static Renderer* Get();

		template <size_t SIZE>
		static void Draw(const Object<SIZE>& obj);
		static void Draw(const Cube& cube);

		static Float CreateTexture(std::string_view name, std::string_view path);
		static Float GetTextureID(std::string_view name);
	private:
		static void Flush();
	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::vector<std::pair<std::string, std::shared_ptr<Texture>>> m_Textures;
		std::array<Int, 8> m_TextureIndices;
		UInt m_TextureCount;


		Mat4 m_Projection;
		Mat4 m_View;

		static Renderer* s_Instance;
	};

	template<size_t SIZE>
	inline void Renderer::Draw(const Object<SIZE>& obj)
	{
		auto& vertices = obj.GetVertices();
		auto indices = obj.GetIndices();
		if (RendererData::VertexCounter + vertices.size() >= RendererData::MaxVertexNumber ||
			RendererData::IndexCounter + indices.size() >= RendererData::MaxIndexNumber)
			Flush();

		Float texture_id = vertices[0].TexID;
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

		for (auto& index : indices)
		{
			RendererData::Indices[RendererData::IndexCounter++] = index + RendererData::VertexCounter;
		}
		
		for (auto& vertex : vertices)
		{
			Float3 coords = obj.TransformCoords(vertex.Coords);
			RendererData::Vertices[RendererData::VertexCounter++] = Vertex(coords, vertex.Color, vertex.TexID, vertex.TexCoords);
		}
	}
}

