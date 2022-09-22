#pragma once
#include "Renderer/Texture/Image.h"


namespace Tomato
{
	struct WindowData
	{
		std::string Title;
		int X, Y;
		int Width, Height;
		bool VSync;
		bool Fullscreen;
	};

	class Window
	{
	public:
		Window(std::string_view title = "Tomato Window", int width = 1280, int height = 720);
		virtual ~Window();

		virtual std::any Get() = 0;

		virtual void DispatchEvents() const {};

		virtual int GetWidth() const;
		virtual int GetHeight() const;
		virtual Int2 GetSize() const;
		virtual void SetSize(int width, int height) = 0;
		virtual void SetWidth(int width) = 0;
		virtual void SetHeight(int height) = 0;
		virtual float GetAspectRatio() const;

		virtual int GetX() const;
		virtual int GetY() const;
		virtual Int2 GetPos() const;
		virtual void SetPos(int x, int y) = 0;
		virtual void SetX(int x);
		virtual void SetY(int y);

		virtual void SetTitle(std::string_view title) = 0;
		virtual const std::string& GetTitle() const;
		virtual void SetIcon(std::string_view iconPath) = 0;

		virtual void SetVSync(bool vsync) = 0;
		virtual bool GetVSync() const;

		virtual void SetFullscreen(bool fullscreen) = 0;
		virtual bool IsFullscreen() const;
	public:
		static std::unique_ptr<Window> CreateUnique(std::string_view title = "Tomato Window", int width = 1280, int height = 720);
		static std::shared_ptr<Window> CreateShared(std::string_view title = "Tomato Window", int width = 1280, int height = 720);
	protected:
		WindowData m_Data;
	};
}
