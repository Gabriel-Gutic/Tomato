#include "pchTomato.h"
#include "Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Image.h"


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

	Texture::Texture(UInt width, UInt height)
	{
		Setup();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::Texture(std::string_view path)
	{
		Setup();

		std::unique_ptr<Image> image = std::make_unique<Image>(path);
	
		glTexImage2D(GL_TEXTURE_2D, 0, image->GetFormat(), image->GetWidth(), image->GetHeight(), 0, image->GetFormat(), GL_UNSIGNED_BYTE, image->GetData());
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

	void Texture::BindUnit(UInt unit) const
	{
		glBindTextureUnit(unit, m_RendererID);
	}

	void Texture::Reset(UInt width, UInt height)
	{
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glGenerateMipmap(GL_TEXTURE_2D); // do i need this?
	}

	UInt Texture::GetID() const
	{
		return m_RendererID;
	}

}