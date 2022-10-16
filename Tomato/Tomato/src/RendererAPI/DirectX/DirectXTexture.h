#pragma once
#include "Tomato/Renderer/Texture/Texture.h"



namespace Tomato
{
#ifdef TOMATO_PLATFORM_WINDOWS
	class DirectXTexture : public Texture
	{
	public:
		DirectXTexture(uint32_t width, uint32_t height, const uint8_t* data, Image::Format format = Image::Format::RGB);
		DirectXTexture(std::string_view path);
		virtual ~DirectXTexture() override;
		std::any GetBuffer() const;
		std::any GetResourceView() const;
	private:
		static int ConvertFormat(Image::Format format);
	private:
		std::any m_Buffer;
		std::any m_ResourceView;
	};
#else
	class DirectXTexture : public Texture
	{
	public:
		DirectXTexture(uint32_t width, uint32_t height, const uint8_t* data = nullptr, Image::Format format = Image::Format::RGB){}
		DirectXTexture(std::string_view path){}
		virtual ~DirectXTexture() override{}
	};
#endif // TOMATO_PLATFORM_WINDOWS
}
