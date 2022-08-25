#pragma once
#include "Shader.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/FrameBuffer.h"
#include "Renderer/Texture/Texture.h"
#include "Renderer/Texture/Tilemap.h"
#include "Scene/Entity.h"


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
		static UInt GetNumberOfVertices();
		static const Mat4& GetViewProjection();

		static void SetBackgroundColor(const Float4& color);

		static void DrawTriangle(const Entity& entity, const std::shared_ptr<Texture>& texture = nullptr, const Mat4& transform = Mat4(1.0f));
		static void DrawQuad(const Entity& entity,     const std::shared_ptr<Texture>& texture = nullptr, const Mat4& transform = Mat4(1.0f));
		static void DrawQuad(const Entity& entity,     const std::shared_ptr<Tilemap>& tilemap, UInt row, UInt col, UInt rowspan, UInt colspan, const Mat4& transform = Mat4(1.0f));
		static void DrawPolygon(const Entity& entity,  const std::shared_ptr<Texture>& texture = nullptr, const Mat4& transform = Mat4(1.0f));
		static void DrawCircle(const Entity& entity,   const std::shared_ptr<Texture>& texture = nullptr, const Mat4& transform = Mat4(1.0f));
	private:
		static void Flush();

		static Float GetTextureIndex(const std::shared_ptr<Texture>& texture);
	private:
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<FrameBuffer> m_FrameBuffer;

		Float4 m_BackgroundColor;
		UInt m_LastNumberOfVertices;
		Mat4 m_VP;

		static Renderer* s_Instance;
	};

	
}

