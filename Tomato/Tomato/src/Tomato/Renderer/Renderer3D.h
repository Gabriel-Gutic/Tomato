#pragma once
#include "Shader.h"
#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/VertexArray.h"
#include "Buffer/FrameBuffer.h"
#include "Line.h"

#include "RendererAPI/RendererData.h"


namespace Tomato
{
	class Renderer3D
	{
	protected:
		Renderer3D() = default;
		virtual ~Renderer3D() = default;
	public:
		Renderer3D(const Renderer3D&) = delete;
		static void Initialize();
		static void Terminate();

		virtual void Begin() = 0;
		virtual void End() = 0;

		virtual void Clear(float r, float g, float b, float a) const = 0;
		virtual void Clear(const Float4& color) const;
		virtual void Swap() const = 0;

		virtual void Draw(const Mesh& mesh, const Mat4& transform = Mat4(1.0f));
		
		// Simple objects for drawing
		virtual void DrawTriangle(const Float3& center = Float3(), float scale = 1.0f, const Mat4& transform = Mat4(1.0f));
		virtual void DrawSquare(const Float3& center = Float3(), float scale = 1.0f, const Mat4& transform = Mat4(1.0f));
		virtual void DrawLine(const Float3& A, const Float3& B, const Float3& color = Float3(1.0f, 1.0f, 1.0f));


		static Renderer3D* Get();
		static void SetFrameBuffer(const std::shared_ptr<FrameBuffer>& fb);
		static const std::shared_ptr<FrameBuffer>& GetFrameBuffer();
	protected:
		virtual float GetTextureIndex(const std::shared_ptr<Texture>& texture);
		virtual void Flush() = 0;
	protected:
		struct Renderer3DData
		{
			std::array<Mesh::Vertex, MAX_VERTEX_NUMBER> Vertices = {};
			uint32_t VertexCounter = 0;
			std::array<uint32_t, MAX_INDEX_NUMBER> Indices = {};
			uint32_t IndexCounter = 0;
			std::array<std::shared_ptr<Texture>, MAX_TEXTURE_SLOTS> TextureSlots = {};
			uint32_t TextureSlotsCounter = 0;

			std::array<Line::Vertex, MAX_VERTEX_NUMBER> LineVertices = {};
			uint32_t LineVertexCounter = 0;
		} m_Data;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<FrameBuffer> m_FrameBuffer;

		static Renderer3D* s_Instance;
	};
}
