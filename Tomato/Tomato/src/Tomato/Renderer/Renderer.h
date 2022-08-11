#pragma once
#include "Shader.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Buffer/FrameBuffer.h"
#include "Renderer/Texture/Texture.h"
#include "Object/Object.h"
#include "Object/3D/Cube.h"


namespace Tomato
{
	struct TextureLayout
	{
		int Index;
		int ID;
	};

	struct RendererData
	{
		static const UInt MaxVertexNumber = 2048;
		static const UInt MaxIndexNumber = 16 * MaxVertexNumber;
		static std::array<Vertex, MaxVertexNumber> Vertices;
		static UInt VertexCounter;
		static std::array<UInt, MaxIndexNumber> Indices;
		static UInt IndexCounter;

		static const UInt MaxTextureSlots = 32;
		static std::array<std::shared_ptr<Texture>, MaxTextureSlots> TextureSlots;
		static UInt TextureSlotsCounter;
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
		static const std::unique_ptr<FrameBuffer>& GetFrameBuffer();

		template <size_t SIZE>
		static void Draw(const Object<SIZE>& obj, std::shared_ptr<Texture> texture = nullptr);
	private:
		static void Flush();
	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<FrameBuffer> m_FrameBuffer;

		Mat4 m_Projection;
		Mat4 m_View;

		static Renderer* s_Instance;
	};

	template<size_t SIZE>
	inline void Renderer::Draw(const Object<SIZE>& obj, std::shared_ptr<Texture> texture)
	{
		auto& vertices = obj.GetVertices();
		auto indices = obj.GetIndices();
		if (RendererData::VertexCounter + vertices.size() >= RendererData::MaxVertexNumber ||
			RendererData::IndexCounter + indices.size() >= RendererData::MaxIndexNumber)
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

		for (auto& index : indices)
		{
			RendererData::Indices[RendererData::IndexCounter++] = index + RendererData::VertexCounter;
		}
		
		for (auto& vertex : vertices)
		{
			Float3 coords = obj.TransformCoords(vertex.Coords);
			RendererData::Vertices[RendererData::VertexCounter++] = Vertex(coords, vertex.Color, texIndex, vertex.TexCoords);
		}
	}
}

