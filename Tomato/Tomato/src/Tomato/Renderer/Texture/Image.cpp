#include "pchTomato.h"
#include "Image.h"

#include "RendererAPI/RendererAPI.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>


namespace Tomato
{
	Image::Image(std::string_view path)
	{
		TOMATO_ASSERT(File::Exist(path), "Image doesn't exist: {0}; ", path);


		stbi_set_flip_vertically_on_load(true);
		
		uint8_t* data = stbi_load(path.data(), &m_RawData.Width, &m_RawData.Height, &m_RawData.NrChannels, 0);
	
		TOMATO_ASSERT(data, "Failed to load image from path: {0}", path);

		if (m_RawData.NrChannels == 3 && RendererAPI::GetType() == RendererAPI::Type::DirectX)
		{
			uint32_t size = 3 * m_RawData.Width * m_RawData.Height;
			m_RawData.Data = new uint8_t[4 * m_RawData.Width * m_RawData.Height];

			uint32_t j = 0;
			for (uint32_t i = 0; i < size; i++)
			{
				m_RawData.Data[j++] = data[i];
				if (i % 3 == 2)
					m_RawData.Data[j++] = 255;
			}
			m_RawData.NrChannels = 4;
		}
		else m_RawData.Data = data;

		m_RawData.Size = m_RawData.NrChannels * 4 * m_RawData.Width * m_RawData.Height;
	}

	Image::~Image()
	{
		stbi_image_free(m_RawData.Data);
	}

	const uint8_t* Image::GetData() const
	{
		return m_RawData.Data;
	}

	unsigned int Image::GetBufferSize() const
	{
		return m_RawData.Size;
	}

	int Image::GetWidth() const
	{
		return m_RawData.Width;
	}

	int Image::GetHeight() const
	{
		return m_RawData.Height;
	}

	int Image::GetNrChannels() const
	{
		return m_RawData.NrChannels;
	}

	Image::Format Image::GetFormat() const
	{
		switch (m_RawData.NrChannels)
		{
		case 1:
			return Format::Red;
		case 2:
			return Format::RG;
		case 3:
			return Format::RGB;
		case 4:
			return Format::RGBA;
		}
		return Format::None;
	}
}


