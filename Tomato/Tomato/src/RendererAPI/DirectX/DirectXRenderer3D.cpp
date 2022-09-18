#include "pchTomato.h"
#include "DirectXRenderer3D.h"

#include "DirectXDevice.h"


namespace Tomato
{
	DirectXRenderer3D::DirectXRenderer3D()
	{
		DirectXDevice::Initialize();
	}

	DirectXRenderer3D::~DirectXRenderer3D()
	{
		DirectXDevice::Terminate();
	}

	void DirectXRenderer3D::Begin()
	{
		DirectXRenderer3D::Clear(1.0f, 0.5f, 0.2f, 1.0f);
	}

	void DirectXRenderer3D::End()
	{
	}

	void DirectXRenderer3D::Clear(float r, float g, float b, float a) const
	{
		Clear(Float4(r, g, b, a));
	}

	void DirectXRenderer3D::Clear(const Float4& color) const
	{
		DirectXDevice::Clear(color);
	}

	void DirectXRenderer3D::Swap() const
	{
		DirectXDevice::Swap();
	}

	void DirectXRenderer3D::Draw(const Mesh& mesh, const Mat4& transform)
	{
	}

	void DirectXRenderer3D::Flush()
	{
	}
}