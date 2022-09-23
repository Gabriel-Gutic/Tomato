#include "pchTomato.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Tomato
{
	void OpenGLTexture::Setup()
	{
		glGenTextures(1, &m_RendererID);

		this->Bind();

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height, const uint8_t* data, Image::Format format)
		:Texture(width, height)
	{
		Setup();

		int gl_format = ConvertFormat(format);
		glTexImage2D(GL_TEXTURE_2D, 0, gl_format, width, height, 0, gl_format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	OpenGLTexture::OpenGLTexture(std::string_view path)
	{
		Setup();

		std::unique_ptr<Image> image = std::make_unique<Image>(path);

		m_Width = image->GetWidth();
		m_Height = image->GetHeight();

		int gl_format = ConvertFormat(image->GetFormat());

		glTexImage2D(GL_TEXTURE_2D, 0, gl_format, m_Width, m_Height, 0, gl_format, GL_UNSIGNED_BYTE, image->GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void OpenGLTexture::BindUnit(unsigned int unit) const
	{
		glBindTextureUnit(unit, m_RendererID);
	}

	unsigned int OpenGLTexture::GetID() const
	{
		return m_RendererID;
	}

	int OpenGLTexture::ConvertFormat(Image::Format format)
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