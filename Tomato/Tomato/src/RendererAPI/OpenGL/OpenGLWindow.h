#pragma once
#include "Tomato/Core/App/Window.h"


namespace Tomato
{
	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(std::string_view title = "Tomato OpenGL Window", int width = 1280, int height = 720);
		virtual ~OpenGLWindow() override;

		virtual std::any Get() override;

		virtual void SetSize(int width, int height) override;
		virtual void SetWidth(int width) override;
		virtual void SetHeight(int height) override;
		virtual void SetPos(int x, int y) override;

		virtual void SetTitle(std::string_view title) override;
		virtual void SetIcon(std::string_view iconPath) override;
		virtual void SetVSync(bool vsync) override;
		virtual void SetFullscreen(bool fullscreen) override;
	private:
		std::any m_Window;
	};
}
