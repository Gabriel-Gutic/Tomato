#include "pchTomato.h"
#include "Window.h"

#include "RendererAPI/RendererAPI.h"
#include "RendererAPI/OpenGL/OpenGLWindow.h"
#include "RendererAPI/DirectX/DirectXWindow.h"


namespace Tomato
{
	Window::Window(std::string_view title, int width, int height)
		:m_Data({
				title.data(),
				200,		// XPos
				100,		// YPos
				width,
				height,
				false,		// VSync
				false,		// Fullscreen
			}){}

	Window::~Window()
	{

	}

	int Window::GetWidth() const
	{
		return m_Data.Width;
	}

	int Window::GetHeight() const
	{
		return m_Data.Height;
	}

	std::pair<int, int> Window::GetSize() const
	{
		return { m_Data.Width, m_Data.Height };
	}

	float Window::GetAspectRatio() const
	{
		return static_cast<float>(m_Data.Width) / static_cast<float>(m_Data.Height);
	}

	int Window::GetX() const
	{
		return m_Data.X;
	}

	int Window::GetY() const
	{
		return m_Data.Y;
	}

	std::pair<int, int> Window::GetPos() const
	{
		return { m_Data.X, m_Data.Y };
	}

	void Window::SetX(int x)
	{
		SetPos(x, m_Data.Y);
	}

	void Window::SetY(int y)
	{
		SetPos(m_Data.X, y);
	}

	const std::string& Window::GetTitle() const
	{
		return m_Data.Title;
	}

	bool Window::GetVSync() const
	{
		return m_Data.VSync;
	}

	bool Window::IsFullscreen() const
	{
		return m_Data.Fullscreen;
	}

	std::unique_ptr<Window> Window::CreateUnique(std::string_view title, int width, int height)
	{
		switch (RendererAPI::GetType())
		{
		case RendererType::OpenGL:
			return std::make_unique<OpenGLWindow>(title, width, height);
		case RendererType::DirectX:
			return std::make_unique<DirectXWindow>(title, width, height);
		}
		return nullptr;
	}

	std::shared_ptr<Window> Window::CreateShared(std::string_view title, int width, int height)
	{
		switch (RendererAPI::GetType())
		{
		case RendererType::OpenGL:
			return std::make_shared<OpenGLWindow>(title, width, height);
		case RendererType::DirectX:
			return std::make_shared<DirectXWindow>(title, width, height);
		}
		return nullptr;
	}

}