#pragma once
#include "Image.h"


namespace Tomato
{
	class Texture
	{
	public:
		Texture(uint32_t width = 0, uint32_t height = 0);
		virtual ~Texture();

		virtual unsigned int GetWidth() const;
		virtual unsigned int GetHeight() const;

		static std::unique_ptr<Texture> CreateUnique(uint32_t width, uint32_t height, const uint8_t* data = nullptr, Image::Format format = Image::Format::RGB);
		static std::shared_ptr<Texture> CreateShared(uint32_t width, uint32_t height, const uint8_t* data = nullptr, Image::Format format = Image::Format::RGB);
		static std::unique_ptr<Texture> CreateUnique(std::string_view path);
		static std::shared_ptr<Texture> CreateShared(std::string_view path);
	protected:
		uint32_t m_Width, m_Height;
	};
}
