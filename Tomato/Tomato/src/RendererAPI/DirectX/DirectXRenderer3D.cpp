#include "pchTomato.h"
#include "DirectXRenderer3D.h"

#include "DirectXDevice.h"

#include <d3d11.h>


namespace Tomato
{
	DirectXRenderer3D::DirectXRenderer3D()
	{
		DirectXDevice::Initialize();

		struct Vertex
		{
			Float3 Position;
			Float4 Color;
		};

		const Vertex vertices[] = {
			{{ 0.0f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
			{{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
		};

		m_Shader = std::move(Shader::CreateUnique("assets/Shaders/3D/VertexShader.hlsl", "assets/Shaders/3D/FragmentShader.hlsl"));
		m_VertexBuffer = std::move(VertexBuffer::CreateUnique(sizeof(vertices), BufferAllocType::Static, vertices));
	}

	DirectXRenderer3D::~DirectXRenderer3D()
	{
		DirectXDevice::Terminate();
	}

	void DirectXRenderer3D::Begin()
	{
	}

	void DirectXRenderer3D::End()
	{
		Flush();
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
		m_VertexBuffer->Bind();
		auto devcon = std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext());
		devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Draw without the index buffer
		devcon->Draw(3, 0);
		// Draw within the index buffer
		// devcon->DrawIndexed(6, 0, 0);
	}
}