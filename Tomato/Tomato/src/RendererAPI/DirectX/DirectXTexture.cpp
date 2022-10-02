#include "pchTomato.h"
#include "DirectXTexture.h"


#ifdef TOMATO_PLATFORM_WINDOWS
#include "DirectXDevice.h"

#include <d3d11.h>

namespace Tomato
{
	DirectXTexture::DirectXTexture(uint32_t width, uint32_t height, const uint8_t* data, Image::Format format)
		:Texture(width, height)
	{
        D3D11_TEXTURE2D_DESC imageTextureDesc = {};

        imageTextureDesc.Width = width;
        imageTextureDesc.Height = height;
        imageTextureDesc.MipLevels = 1;
        imageTextureDesc.ArraySize = 1;
        imageTextureDesc.Format = static_cast<DXGI_FORMAT>(ConvertFormat(format));
        imageTextureDesc.SampleDesc.Count = 1;
        imageTextureDesc.SampleDesc.Quality = 0;
        imageTextureDesc.Usage = D3D11_USAGE_IMMUTABLE;
        imageTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        D3D11_SUBRESOURCE_DATA imageSubresourceData = {};

        imageSubresourceData.pSysMem = data;
        int nrOfChannels = 0;
        switch (format)
        {
        case Tomato::Image::Format::Red:
            nrOfChannels = 1;
            break;
        case Tomato::Image::Format::RG:
            nrOfChannels = 2;
            break;
        case Tomato::Image::Format::RGB:
            nrOfChannels = 4;
            break;
        case Tomato::Image::Format::RGBA:
            nrOfChannels = 4;
            break;
        }
        imageSubresourceData.SysMemPitch = nrOfChannels * width;

        ID3D11Texture2D* imageTexture;

        TOMATO_ASSERT(SUCCEEDED(std::any_cast<ID3D11Device*>(DirectXDevice::GetDevice())->CreateTexture2D(
            &imageTextureDesc,
            &imageSubresourceData,
            &imageTexture
        )), "Failed to create empty texture!");

        m_Buffer = imageTexture;
	}

	DirectXTexture::DirectXTexture(std::string_view path)
	{
        Image image = Image(path);

        D3D11_TEXTURE2D_DESC imageTextureDesc = {};

        imageTextureDesc.Width = image.GetWidth();
        imageTextureDesc.Height = image.GetHeight();
        imageTextureDesc.MipLevels = 1;
        imageTextureDesc.ArraySize = 1;
        imageTextureDesc.Format = static_cast<DXGI_FORMAT>(ConvertFormat(image.GetFormat()));
        imageTextureDesc.SampleDesc.Count = 1;
        imageTextureDesc.SampleDesc.Quality = 0;
        imageTextureDesc.Usage = D3D11_USAGE_IMMUTABLE;
        imageTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        D3D11_SUBRESOURCE_DATA imageSubresourceData = {};

        imageSubresourceData.pSysMem = image.GetData();
        imageSubresourceData.SysMemPitch = image.GetNrChannels() * image.GetWidth();

        ID3D11Texture2D* imageTexture;

        auto device = std::any_cast<ID3D11Device*>(DirectXDevice::GetDevice());

        TOMATO_ASSERT(SUCCEEDED(device->CreateTexture2D(
            &imageTextureDesc,
            &imageSubresourceData,
            &imageTexture
        )), "Failed to create texture from source: {0}", path.data());

        m_Buffer = imageTexture;

        ID3D11ShaderResourceView* imageShaderResourceView;
        TOMATO_ASSERT(SUCCEEDED(device->CreateShaderResourceView(
            imageTexture,
            nullptr,
            &imageShaderResourceView
        )), "Failed to create the resource view for texture from source: {0}", path.data());
        m_ResourceView = imageShaderResourceView;
    }

	DirectXTexture::~DirectXTexture()
	{
        std::any_cast<ID3D11Texture2D*>(m_Buffer)->Release();
	}

    std::any DirectXTexture::GetResourceView() const
    {
        return m_ResourceView;
    }

    int DirectXTexture::ConvertFormat(Image::Format format)
    {
        switch (format)
        {
        case Tomato::Image::Format::None:
            return 0;
        case Tomato::Image::Format::Red:
            return DXGI_FORMAT_R32_FLOAT;
        case Tomato::Image::Format::RG:
            return DXGI_FORMAT_R16G16_UNORM;
        case Tomato::Image::Format::RGB:
            return 	DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        case Tomato::Image::Format::RGBA:
            return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        }
        return 0;
    }
}

#endif // TOMATO_PLATFORM_WINDOWS
