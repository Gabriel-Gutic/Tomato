#pragma once
#include "Shader.h"
#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/VertexArray.h"


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

		virtual void Draw(const Mesh& mesh, const Mat4& transform = Mat4(1.0f)) = 0;

		static Renderer3D* Get();
	private:
		virtual void Flush() = 0;
	protected:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
	private:
		static Renderer3D* s_Instance;
	};
}
