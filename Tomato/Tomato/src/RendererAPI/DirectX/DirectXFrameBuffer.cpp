#include "pchTomato.h"
#include "DirectXFrameBuffer.h"

#include "DirectXDevice.h"
#include "DirectXTexture.h"

#include <d3d11.h>


namespace Tomato
{
	DirectXFrameBuffer::DirectXFrameBuffer(uint32_t width, uint32_t height)
		:FrameBuffer(width, height)
	{
		m_Texture = Texture::CreateShared(width, height);

		ID3D11RenderTargetView* rtv;

		std::any_cast<ID3D11Device*>(DirectXDevice::GetDevice())->CreateRenderTargetView(
			std::any_cast<ID3D11Texture2D*>(std::dynamic_pointer_cast<DirectXTexture>(m_Texture)->GetBuffer()), 
			NULL, &rtv);

		m_RenderTargetView = rtv;
	}

	DirectXFrameBuffer::~DirectXFrameBuffer()
	{
		std::any_cast<ID3D11RenderTargetView*>(m_RenderTargetView)->Release();
	}

	std::any DirectXFrameBuffer::GetRenderTargetView() const
	{
		return m_RenderTargetView;
	}
}