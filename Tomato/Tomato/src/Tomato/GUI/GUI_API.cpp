#include "pchTomato.h"
#include "GUI_API.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLGUI.h"


namespace Tomato
{
	std::unique_ptr<GUI_API> GUI_API::CreateUnique()
	{
		switch (RendererAPI::GetType())
		{
		case RendererType::OpenGL:
			return std::make_unique<OpenGLGUI>();
		}
		return nullptr;
	}

	std::shared_ptr<GUI_API> GUI_API::CreateShared()
	{
		switch (RendererAPI::GetType())
		{
		case RendererType::OpenGL:
			return std::make_shared<OpenGLGUI>();
		}
		return nullptr;
	}
}