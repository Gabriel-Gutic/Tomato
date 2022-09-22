#include "pchTomato.h"
#include "Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Tomato
{
	void Texture::Setup()
	{
		glGenTextures(1, &m_RendererID);

		this->Bind();

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	Texture::Texture(unsigned int width, unsigned int height, unsigned char* data, Image::Format format)
		:m_Width(width), m_Height(height)
	{
		Setup();

		int gl_format = ConvertFormat(format);
		glTexImage2D(GL_TEXTURE_2D, 0, gl_format, width, height, 0, gl_format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::Texture(unsigned int width, unsigned int height)
		:m_Width(width), m_Height(height)
	{
		Setup();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::Texture(std::string_view path)
	{
		Setup();

		std::unique_ptr<Image> image = std::make_unique<Image>(path);
		
		m_Width = image->GetWidth();
		m_Height = image->GetHeight();

		int gl_format = ConvertFormat(image->GetFormat());

		glTexImage2D(GL_TEXTURE_2D, 0, gl_format, m_Width, m_Height, 0, gl_format, GL_UNSIGNED_BYTE, image->GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void Texture::BindUnit(unsigned int unit) const
	{
		glBindTextureUnit(unit, m_RendererID);
	}

	void Texture::Reset(unsigned int width, unsigned int height)
	{
		m_Width = width;
		m_Height = height;
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glGenerateMipmap(GL_TEXTURE_2D); // do i need this?
	}

	unsigned int Texture::GetWidth() const
	{
		return m_Width;
	}

	unsigned int Texture::GetHeight() const
	{
		return m_Height;
	}

	unsigned int Texture::GetID() const
	{
		return m_RendererID;
	}

	std::shared_ptr<Texture> Texture::Create(std::string_view path)
	{
		return std::make_shared<Texture>(path);
	}

	int Texture::ConvertFormat(Image::Format format)
	{
		switch (format)
		{
		case Image::Format::Red:
			return GL_RED;
		case Image::Format::RG:
			return GL_RG;
		case Image::Format::RGB:
			return GL_RGB;
		case Image::Format::RGBA:
			return GL_RGBA;
		}
		return 0;
	}

}