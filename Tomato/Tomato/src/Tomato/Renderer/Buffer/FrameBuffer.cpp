#include "pchTomato.h"
#include "FrameBuffer.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLFrameBuffer.h"
#include "RendererAPI/DirectX/DirectXFrameBuffer.h"


namespace Tomato
{
	FrameBuffer::FrameBuffer(uint32_t width, uint32_t height)
		:m_Width(width), m_Height(height), m_Texture(nullptr)
	{

	}

	const std::shared_ptr<Texture>& FrameBuffer::GetTexture() const
	{
		return m_Texture;
	}

	UInt2 FrameBuffer::GetSize() const
	{
		return { m_Width, m_Height };
	}

	void FrameBuffer::SetSize(uint32_t width, uint32_t height)
	{
		m_Width = width;
		m_Height = height;
		m_Texture = Texture::CreateShared(width, height);
	}

	std::shared_ptr<FrameBuffer> FrameBuffer::CreateShared(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_shared<OpenGLFrameBuffer>(width, height);
		case RendererAPI::Type::DirectX:
			return std::make_shared<DirectXFrameBuffer>(width, height);
		}
		return nullptr;
	}

	std::unique_ptr<FrameBuffer> FrameBuffer::CreateUnique(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_unique<OpenGLFrameBuffer>(width, height);
		case RendererAPI::Type::DirectX:
			return std::make_unique<DirectXFrameBuffer>(width, height);
		}
		return nullptr;
	}
}