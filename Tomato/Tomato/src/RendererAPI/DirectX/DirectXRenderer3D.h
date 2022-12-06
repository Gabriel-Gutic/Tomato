#pragma once
#include "Tomato/Renderer/Renderer3D.h"


namespace Tomato
{
#ifdef TOMATO_PLATFORM_WINDOWS
	class DirectXRenderer3D : public Renderer3D
	{
	public:
		DirectXRenderer3D();
		virtual ~DirectXRenderer3D() override;

		virtual void Begin() override;
		virtual void End() override;

		virtual void Clear() const override;
		virtual void Swap() const override;
	private:
		virtual void Flush() override;
	};
#else 
	class DirectXRenderer3D : public Renderer3D
	{
	public:
		DirectXRenderer3D(){}
		virtual ~DirectXRenderer3D() override {}

		virtual void Begin() override {}
		virtual void End() override {}

		virtual void Clear(float r, float g, float b, float a) const override {}
		virtual void Clear(const Float4& color) const override {}
		virtual void Swap() const override {}
	private:
		virtual void Flush() override {}
	};
#endif // TOMATO_PLATFORM_WINDOWS
}
