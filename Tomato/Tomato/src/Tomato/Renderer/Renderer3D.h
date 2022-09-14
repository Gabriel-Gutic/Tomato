#pragma once
#include "Shader.h"
#include "Buffer/VertexBuffer.h"
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

		static Renderer3D* Get();
	protected:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
	private:
		static Renderer3D* s_Instance;
	};
}
