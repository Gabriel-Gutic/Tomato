#include "pchTomato.h"
#include "Texture.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLTexture.h"
#include "RendererAPI/DirectX/DirectXTexture.h"


namespace Tomato
{
	Texture::Texture(uint32_t width, uint32_t height)
		:m_Width(width), m_Height(height)
	{
	}

	Texture::~Texture()
	{
	}

	unsigned int Texture::GetWidth() const
	{
		return m_Width;
	}

	unsigned int Texture::GetHeight() const
	{
		return m_Height;
	}

	std::unique_ptr<Texture> Texture::CreateUnique(uint32_t width, uint32_t height, const uint8_t* data, Image::Format format)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_unique<OpenGLTexture>(width, height, data, format);
		case RendererAPI::Type::DirectX:
			return std::make_unique<DirectXTexture>(width, height, data, format);
		}
		return nullptr;
	}

	std::shared_ptr<Texture> Texture::CreateShared(uint32_t width, uint32_t height, const uint8_t* data, Image::Format format)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_shared<OpenGLTexture>(width, height, data, format);
		case RendererAPI::Type::DirectX:
			return std::make_shared<DirectXTexture>(width, height, data, format);
		}
		return nullptr;
	}

	std::unique_ptr<Texture> Texture::CreateUnique(std::string_view path)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_unique<OpenGLTexture>(path);
		case RendererAPI::Type::DirectX:
			return std::make_unique<DirectXTexture>(path);
		}
		return nullptr;
	}

	std::shared_ptr<Texture> Texture::CreateShared(std::string_view path)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_shared<OpenGLTexture>(path);
		case RendererAPI::Type::DirectX:
			return std::make_shared<DirectXTexture>(path);
		}
		return nullptr;
	}
}