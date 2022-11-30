#include "pchTomato.h"
#include "VertexArray.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLVertexArray.h"


namespace Tomato
{
	std::unique_ptr<VertexArray> VertexArray::CreateUnique(const std::initializer_list<uint8_t>& layout)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_unique<OpenGLVertexArray>(layout);
		}
		return nullptr;
	}

	std::shared_ptr<VertexArray> VertexArray::CreateShared(const std::initializer_list<uint8_t>& layout)
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_shared<OpenGLVertexArray>(layout);
		}
		return nullptr;
	}
}