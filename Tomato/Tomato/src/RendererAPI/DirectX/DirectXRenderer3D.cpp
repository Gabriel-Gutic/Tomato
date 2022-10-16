#include "pchTomato.h"
#include "DirectXRenderer3D.h"

#ifdef TOMATO_PLATFORM_WINDOWS
#include "RendererAPI/RendererData.h"
#include "DirectXDevice.h"
#include "DirectXTexture.h"
#include "DirectXFrameBuffer.h"
#include "Tomato/Core/App/App.h"


#include <d3d11.h>


namespace Tomato
{
	DirectXRenderer3D::DirectXRenderer3D()
	{
		DirectXDevice::Initialize();

		m_Shader = std::move(Shader::CreateUnique("assets/Shaders/3D/VertexShader.hlsl", "assets/Shaders/3D/FragmentShader.hlsl"));
		m_VertexBuffer = std::move(VertexBuffer::CreateUnique(MAX_VERTEX_NUMBER * sizeof(Mesh::Vertex), BufferAllocType::Dynamic, m_Data.Vertices.data()));
		m_IndexBuffer = std::move(IndexBuffer::CreateUnique(MAX_INDEX_NUMBER, BufferAllocType::Dynamic, m_Data.Indices.data()));
	
		m_FrameBuffer = nullptr;
	}

	DirectXRenderer3D::~DirectXRenderer3D()
	{
		DirectXDevice::Terminate();
	}

	void DirectXRenderer3D::Begin()
	{
		if (Renderer3D::GetFrameBuffer())
			DirectXDevice::SetRenderTarget(std::dynamic_pointer_cast<DirectXFrameBuffer>(Renderer3D::GetFrameBuffer())->GetRenderTargetView());

		Renderer3D::Get()->Clear(1.0f, 0.0f, 0.0f, 1.0f);

		m_Shader->Use();
		m_Shader->SetMat4("VP", Math::Transpose(App::GetCurrentScene()->GetViewProjection()));
	}

	void DirectXRenderer3D::End()
	{
		Flush();

		DirectXDevice::SetRenderTarget(DirectXDevice::GetBackBuffer());
		Renderer3D::Get()->Clear(0.0f, 0.0f, 1.0f, 1.0f);
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

	void DirectXRenderer3D::Flush()
	{
		m_VertexBuffer->SetData(m_Data.Vertices, m_Data.VertexCounter);
		m_VertexBuffer->Bind();

		m_IndexBuffer->SetData(m_Data.Indices, m_Data.IndexCounter);
		m_IndexBuffer->Bind();

		auto devcon = std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext());
		devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		ID3D11ShaderResourceView* resources[MAX_TEXTURE_SLOTS];
		for (uint32_t i = 0; i < m_Data.TextureSlotsCounter; i++)
			resources[i] = std::any_cast<ID3D11ShaderResourceView*>(
				std::dynamic_pointer_cast<DirectXTexture>(m_Data.TextureSlots[i])->GetResourceView());
		devcon->PSSetShaderResources(0, m_Data.TextureSlotsCounter, resources);

		// Draw without the index buffer
		// devcon->Draw(3, 0);
		// Draw within the index buffer
		devcon->DrawIndexed(m_Data.IndexCounter, 0, 0);

		m_Data.VertexCounter = 0;
		m_Data.IndexCounter = 0;
		m_Data.TextureSlotsCounter = 0;
	}
}

#endif // TOMATO_PLATFORM_WINDOWS
