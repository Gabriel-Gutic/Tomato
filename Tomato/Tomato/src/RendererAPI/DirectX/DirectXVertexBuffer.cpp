#include "pchTomato.h"
#include "DirectXVertexBuffer.h"

#include "DirectXDevice.h"
#include "Tomato/Renderer/Renderer.h"

#include <d3d11.h>


namespace Tomato
{
	DirectXVertexBuffer::DirectXVertexBuffer(uint32_t size, BufferAllocType allocType, const void* data)
		:VertexBuffer(allocType)
	{
		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = size;               // size is the Vertex struct * number of vertices
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bd.MiscFlags = 0;
		
		switch (Renderer::GetType())
		{
		case RendererType::_2D:
		{
			bd.StructureByteStride = sizeof(Vertex);
		} break;
		case RendererType::_3D:
		{
			bd.StructureByteStride = sizeof(Float3) + sizeof(Float4);
		} break;
		}

		switch (allocType)
		{
		case Tomato::BufferAllocType::Static:
		{
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0;
		} break;
		case Tomato::BufferAllocType::Dynamic:
		{
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		} break;
		}

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = data;
		sd.SysMemPitch = 0;
		sd.SysMemSlicePitch = 0;

		ID3D11Buffer* buffer;

		// Create the vertex buffer
		TOMATO_ASSERT(!FAILED(std::any_cast<ID3D11Device*>(DirectXDevice::GetDevice())->CreateBuffer(&bd, &sd, &buffer)), "Failed to create the DirectX Vertex Buffer");       
		m_Data = buffer;
	}

	DirectXVertexBuffer::~DirectXVertexBuffer()
	{
		std::any_cast<ID3D11Buffer*>(m_Data)->Release();
	}

	void DirectXVertexBuffer::Bind()
	{
		UINT stride;
		switch (Renderer::GetType())
		{
		case RendererType::_2D:
			stride = sizeof(Vertex);
			break;
		case RendererType::_3D:
			stride = sizeof(Float3) + sizeof(Float4);
			break;
		default:
			stride = 0;
			break;
		}
		UINT offset = 0;
		auto buffer = std::any_cast<ID3D11Buffer*>(m_Data);
		std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext())->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	}

	void DirectXVertexBuffer::SetRawData(const void* data, unsigned int size) const
	{
		if (m_AllocType == BufferAllocType::Dynamic)
		{
			// Change the data from a dynamic Vertex Buffer
			D3D11_MAPPED_SUBRESOURCE mappedResource = {};

			auto buffer = std::any_cast<ID3D11Buffer*>(m_Data);
			auto devcon = std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext());

			//  Disable GPU access to the vertex buffer data
			devcon->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			//  Update the vertex buffer here.
			memcpy(mappedResource.pData, data, size);
			//  Reenable GPU access to the vertex buffer data.
			devcon->Unmap(buffer, 0);
		}
	}
}
