#pragma once
#include "Shader.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/FrameBuffer.h"
#include "Renderer/Texture/Texture.h"
#include "Renderer/Texture/Tilemap.h"
#include "Component/Transform.h"
#include "Object/2D/Triangle.h"
#include "Object/2D/Quad.h"
#include "Object/2D/Polygon.h"
#include "Object/2D/Circle.h"


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

		static void SetBackgroundColor(const Float4& color);

		static void Draw(const Triangle& obj, std::shared_ptr<Texture> texture = nullptr, const Mat4& transform = Mat4(1.0f));
		static void Draw(const Quad& quad, std::shared_ptr<Texture> texture = nullptr, const Mat4& transform = Mat4(1.0f));
		static void Draw(const Quad& quad, std::shared_ptr<Tilemap> tilemap, UInt row, UInt col, UInt rowspan, UInt colspan, const Mat4& transform = Mat4(1.0f));
		static void Draw(const Polygon& polygon, std::shared_ptr<Texture> texture = nullptr, const Mat4& transform = Mat4(1.0f));
		static void Draw(const Circle& circle, std::shared_ptr<Texture> texture = nullptr, const Mat4& transform = Mat4(1.0f));
	private:
		static void Flush();
	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<FrameBuffer> m_FrameBuffer;

		Float4 m_BackgroundColor;
		Mat4 m_Projection;
		Mat4 m_View;

		static Renderer* s_Instance;
	};

	
}

