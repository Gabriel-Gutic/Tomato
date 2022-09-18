#include "pchTomato.h"
#include "RendererAPI.h"


namespace Tomato
{
	RendererAPI::Type RendererAPI::s_Type = RendererAPI::Type::OpenGL;
	RendererAPI::Type RendererAPI::GetType()
	{
		if (s_Type == RendererAPI::Type::None)
		{
			TOMATO_ERROR("Invalid RendererAPI");
			__debugbreak();
		}
		return RendererAPI::s_Type;
	}

	void RendererAPI::SetType(RendererAPI::Type type)
	{
		s_Type = type;
	}
}


