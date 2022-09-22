#include "pchTomato.h"
#include "DirectXIndexBuffer.h"

#ifdef TOMATO_PLATFORM_WINDOWS
#include "DirectXDevice.h"

#include <d3d11.h>


namespace Tomato
{
	DirectXIndexBuffer::DirectXIndexBuffer(uint32_t count, BufferAllocType allocType, const void* data)
		:IndexBuffer(allocType)
	{
		D3D11_BUFFER_DESC ibDescription = {};

		switch (allocType)
		{
		case Tomato::BufferAllocType::Static:
			ibDescription.Usage = D3D11_USAGE_DEFAULT;
			ibDescription.CPUAccessFlags = 0;
			break;
		case Tomato::BufferAllocType::Dynamic:
			ibDescription.Usage = D3D11_USAGE_DYNAMIC;
			ibDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;
		}
		ibDescription.ByteWidth = count * sizeof(uint32_t);
		ibDescription.StructureByteStride = sizeof(uint32_t);
		ibDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDescription.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA ibSubresourceData = {};
		ibSubresourceData.pSysMem = data;

		ID3D11Buffer* indexBuffer;
		TOMATO_ASSERT(!FAILED(std::any_cast<ID3D11Device*>(DirectXDevice::GetDevice())->CreateBuffer(&ibDescription, &ibSubresourceData, &indexBuffer)), 
			"Failed to create the DirectX Index Buffer");
		m_Data = indexBuffer;
	}

	DirectXIndexBuffer::~DirectXIndexBuffer()
	{
		std::any_cast<ID3D11Buffer*>(m_Data)->Release();
	}

	void DirectXIndexBuffer::Bind()
	{
		auto indexBuffer = std::any_cast<ID3D11Buffer*>(m_Data);
		std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext())->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0u);
	}

	void DirectXIndexBuffer::SetRawData(const void* data, uint32_t size) const
	{
		if (m_AllocType == BufferAllocType::Dynamic)
		{
			// Change the data from a dynamic Vertex Buffer
			D3D11_MAPPED_SUBRESOURCE mappedResource = {};

			auto indexBuffer = std::any_cast<ID3D11Buffer*>(m_Data);
			auto devcon = std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext());

			//  Disable GPU access to the vertex buffer data
			devcon->Map(indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
			//  Update the vertex buffer here.
			memcpy(mappedResource.pData, data, size);
			//  Reenable GPU access to the vertex buffer data.
			devcon->Unmap(indexBuffer, 0);
		}
	}
}

#endif // TOMATO_PLATFORM_WINDOWS
