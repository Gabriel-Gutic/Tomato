#pragma once
#include "Shader/ShaderProgram.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Object/Triangle.h"
#include "Object/Quad.h"


namespace Tomato
{
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

		static void Draw(std::shared_ptr<Triangle> triangle);
		static void Draw(std::shared_ptr<Quad> quad);
	private:
		static void Flush();
	private:
		std::unique_ptr<ShaderProgram> m_ShaderProgram;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;

		Mat4 m_ProjectionView;

		static Renderer* s_Instance;
	};
}

