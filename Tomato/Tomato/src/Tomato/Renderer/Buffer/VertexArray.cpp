#include "pchTomato.h"
#include "VertexArray.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLVertexArray.h"


namespace Tomato
{
	std::unique_ptr<VertexArray> VertexArray::CreateUnique()
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_unique<OpenGLVertexArray>();
		}
		return nullptr;
	}

	std::shared_ptr<VertexArray> VertexArray::CreateShared()
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}
		return nullptr;
	}
}