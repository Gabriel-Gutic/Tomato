#include "pchTomato.h"
#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Tomato
{
	Image::Image(std::string_view path)
	{
		TOMATO_ASSERT(File::Exist(path), "Image doesn't exist: {0}; ", path);

		stbi_set_flip_vertically_on_load(true);
		m_RawData.Data = stbi_load(path.data(), &m_RawData.Width, &m_RawData.Height, &m_RawData.NrChannels, 0);
	
		TOMATO_ASSERT(m_RawData.Data, "Failed to load image from path: {0}", path);

		m_RawData.Size = m_RawData.NrChannels * 4 * m_RawData.Width * m_RawData.Height;
	}

	Image::~Image()
	{
		stbi_image_free(m_RawData.Data);
	}

	const unsigned char* Image::GetData() const
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

	int Image::GetFormat() const
	{
		switch (m_RawData.NrChannels)
		{
		case 1:
			return GL_R;
		case 2:
			return GL_RG;
		case 3:
			return GL_RGB;
		case 4:
			return GL_RGBA;
		}
		return 0;
	}
}


