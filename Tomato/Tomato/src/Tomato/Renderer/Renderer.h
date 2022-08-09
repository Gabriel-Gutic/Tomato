#pragma once
#include "Shader/ShaderProgram.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Object/Object.h"
#include "Object/3D/Cube.h"


namespace Tomato
{
	struct RendererData
	{
		static const UInt MaxVertexNumber = 16384;
		static std::array<Vertex, MaxVertexNumber> Vertices;
		static UInt VertexCounter;
		static std::array<UInt, MaxVertexNumber> Indices;
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
	private:
		static void Flush();
	private:
		std::unique_ptr<ShaderProgram> m_ShaderProgram;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;

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
			RendererData::IndexCounter + indices.size() >= RendererData::MaxVertexNumber)
			Flush();

		for (auto& index : indices)
		{
			RendererData::Indices[RendererData::IndexCounter++] = index + RendererData::VertexCounter;
		}

		const Mat4 tran = obj.GetTransform();

		for (auto& vertex : vertices)
		{
			Float4 coords = tran * Float4(vertex.Coords, 1.0f);
			RendererData::Vertices[RendererData::VertexCounter++] = Vertex(coords.xyz, vertex.Color, vertex.TexCoords);
		}
	}
}

