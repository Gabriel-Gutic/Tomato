#include "pchTomato.h"
#include "GUI_API.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLGUI.h"
#include "RendererAPI/DirectX/DirectXGUI.h"


namespace Tomato
{
	std::unique_ptr<GUI_API> GUI_API::CreateUnique()
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_unique<OpenGLGUI>();
		case RendererAPI::Type::DirectX:
			return std::make_unique<DirectXGUI>();
		}
		return nullptr;
	}

	std::shared_ptr<GUI_API> GUI_API::CreateShared()
	{
		switch (RendererAPI::GetType())
		{
		case RendererAPI::Type::OpenGL:
			return std::make_shared<OpenGLGUI>();
		case RendererAPI::Type::DirectX:
			return std::make_shared<DirectXGUI>();
		}
		return nullptr;
	}
}