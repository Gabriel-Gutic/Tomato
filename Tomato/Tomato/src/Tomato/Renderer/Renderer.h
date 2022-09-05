#pragma once
#include "Shader.h"
#include "Buffer/VertexArray.h"
#include "Buffer/VertexBuffer.h"
#include "Buffer/FrameBuffer.h"
#include "Texture/Texture.h"
#include "Texture/Tilemap.h"
#include "Scene/Entity.h"
#include "Texture/Font.h"


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

		static void Draw(const Entity& entity, const std::shared_ptr<Texture>& texture = nullptr, const Mat4& transform = Mat4(1.0f));
		static void Draw(const Entity& entity, const std::shared_ptr<Tilemap>& tilemap, UInt row, UInt col, UInt rowspan, UInt colspan, const Mat4& transform = Mat4(1.0f));
		static void DrawQuad(const Entity& entity,  const std::shared_ptr<Tilemap>& tilemap, UInt row, UInt col, UInt rowspan, UInt colspan, const Mat4& transform = Mat4(1.0f));
		static void DrawText(std::string_view text, const Font& font, const Mat4& transform = Mat4(1.0f));
	private:
		static void Flush();

		static Float GetTextureIndex(const std::shared_ptr<Texture>& texture);
	private:
		std::unique_ptr<FrameBuffer> m_FrameBuffer;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;

		Float4 m_BackgroundColor;
		UInt m_LastNumberOfVertices;
		Mat4 m_VP;

		static Renderer* s_Instance;
	};

	
}

