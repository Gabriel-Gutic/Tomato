#include "pchTomato.h"
#include "VertexBuffer.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLVertexBuffer.h"


namespace Tomato
{
	VertexBuffer::VertexBuffer(BufferAllocType allocType)
		:Buffer(allocType)
	{

	}

	std::unique_ptr<VertexBuffer> VertexBuffer::CreateUnique(uint32_t size, BufferAllocType allocType, const void* data)
	{
		switch (RendererAPI::GetType())
		{
		case RendererType::OpenGL:
			return std::make_unique<OpenGLVertexBuffer>(size, allocType, data);
		}
		return nullptr;
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::CreateShared(uint32_t size, BufferAllocType allocType, const void* data)
	{
		switch (RendererAPI::GetType())
		{
		case RendererType::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(size, allocType, data);
		}
		return nullptr;
	}
}


