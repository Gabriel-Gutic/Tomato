#pragma once
#include "Tomato/Renderer/Renderer3D.h"


namespace Tomato
{
	class OpenGLRenderer3D : public Renderer3D
	{
	public:
		OpenGLRenderer3D();
		virtual ~OpenGLRenderer3D() override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Clear(float r, float g, float b, float a) const override;
		virtual void Swap() const override;
	private:
		virtual void Flush() override;
	private:
		std::unique_ptr<Shader> m_LineShader;
		std::unique_ptr<VertexArray> m_LineVertexArray;
		std::unique_ptr<VertexBuffer> m_LineVertexBuffer;
	};
}
