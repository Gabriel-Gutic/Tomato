#pragma once
#include "Tomato/Renderer/Renderer3D.h"


namespace Tomato
{
	class DirectXRenderer3D : public Renderer3D
	{
	public:
		DirectXRenderer3D();
		virtual ~DirectXRenderer3D() override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Clear(float r, float g, float b, float a) const override;
		virtual void Clear(const Float4& color) const override;
		virtual void Swap() const override;

		virtual void Draw(const Mesh& mesh, const Mat4& transform = Mat4(1.0f)) override;
	private:
		virtual void Flush() override;
	};
}
