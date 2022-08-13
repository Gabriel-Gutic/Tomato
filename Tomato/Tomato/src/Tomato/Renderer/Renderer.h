#pragma once
#include "Shader.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Buffer/FrameBuffer.h"
#include "Renderer/Texture/Texture.h"
#include "Object/2D/Triangle.h"
#include "Object/2D/Quad.h"
#include "Object/2D/Circle.h"
#include "Object/3D/Cube.h"


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
		static const std::unique_ptr<FrameBuffer>& GetFrameBuffer();

		static void Draw(const Triangle& obj, std::shared_ptr<Texture> texture = nullptr, const Transform& transform = Transform());
		static void Draw(const Quad& obj, std::shared_ptr<Texture> texture = nullptr, const Transform& transform = Transform());
		static void Draw(const Circle& circle, std::shared_ptr<Texture> texture = nullptr, const Transform& transform = Transform());
	private:
		static void Flush();
	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Shader> m_CircleShader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<FrameBuffer> m_FrameBuffer;

		Mat4 m_Projection;
		Mat4 m_View;

		static Renderer* s_Instance;
	};

	
}

