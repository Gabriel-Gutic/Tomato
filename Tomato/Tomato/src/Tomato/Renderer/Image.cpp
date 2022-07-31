#include "pchTomato.h"
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>


namespace Tomato
{
	Image::Image(std::string_view path)
	{
		TOMATO_ASSERT(File::Exist(path), "Image doesn't exist: {0}; ", path);

		m_RawData.Data = stbi_load(path.data(), &m_RawData.Width, &m_RawData.Height, &m_RawData.NrChannels, 0);
	
		TOMATO_ASSERT(m_RawData.Data, "Failed to load image from path: {0}", path);
	}

	Image::~Image()
	{
		stbi_image_free(m_RawData.Data);
	}

	Int Image::GetWidth() const
	{
		return m_RawData.Width;
	}

	Int Image::GetHeight() const
	{
		return m_RawData.Height;
	}

	Int Image::GetNrChannels() const
	{
		return m_RawData.NrChannels;
	}
}


