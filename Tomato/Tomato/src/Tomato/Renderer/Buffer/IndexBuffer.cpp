#include "pchTomato.h"
#include "IndexBuffer.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLIndexBuffer.h"
#include "RendererAPI/DirectX/DirectXIndexBuffer.h"


namespace Tomato
{
	IndexBuffer::IndexBuffer(BufferAllocType allocType)
		:Buffer(allocType)
	{
	}

	IndexBuffer::~IndexBuffer()
	{
	}

	std::unique_ptr<IndexBuffer> IndexBuffer::CreateUnique(uint32_t count, BufferAllocType allocType, const void* data)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_unique<OpenGLIndexBuffer>(count, allocType, data);
		case RendererAPI::Type::DirectX:
			return std::make_unique<DirectXIndexBuffer>(count, allocType, data);
		}
		return nullptr;
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::CreateShared(uint32_t count, BufferAllocType allocType, const void* data)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(count, allocType, data);
		case RendererAPI::Type::DirectX:
			return std::make_shared<DirectXIndexBuffer>(count, allocType, data);
		}
		return nullptr;
	}
}