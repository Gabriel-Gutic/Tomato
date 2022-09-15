#pragma once
#include "Tomato/Renderer/Renderer3D.h"


namespace Tomato
{
	class OpenGLRenderer3D : public Renderer3D
	{
	public:
		OpenGLRenderer3D();
		virtual ~OpenGLRenderer3D() override;

		virtual void Begin();
		virtual void End();

		virtual void Draw(const Mesh& mesh, const Mat4& transform = Mat4(1.0f)) override;
	private:
		virtual void Flush() override;
	};
}
