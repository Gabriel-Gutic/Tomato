#include "pchTomato.h"
#include "RendererAPI.h"


namespace Tomato
{
	RendererType RendererAPI::s_Type = RendererType::OpenGL;
	RendererType RendererAPI::GetType()
	{
		if (s_Type == RendererType::None)
		{
			TOMATO_ERROR("Invalid RendererAPI");
			__debugbreak();
		}
		return RendererAPI::s_Type;
	}

	void RendererAPI::SetType(RendererType type)
	{
		s_Type = type;
	}
}


