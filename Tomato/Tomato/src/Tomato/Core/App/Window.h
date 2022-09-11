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
	};

	class Window
	{
	public:
		Window(std::string_view title = "Tomato Window", int width = 1280, int height = 720);
		virtual ~Window();

		virtual void Clear(float r, float g, float b, float a) const = 0;
		virtual void Clear(const Float4& color) const = 0;
		virtual void Swap() = 0;

		virtual int GetWidth() const;
		virtual int GetHeight() const;
		virtual std::pair<int, int> GetSize() const;
		virtual void SetSize(int width, int height) = 0;
		virtual void SetWidth(int width) = 0;
		virtual void SetHeight(int height) = 0;
		virtual float GetAspectRatio() const;

		virtual int GetX() const;
		virtual int GetY() const;
		virtual std::pair<int, int> GetPos() const;
		virtual void SetPos(int x, int y) = 0;
		virtual void SetX(int x);
		virtual void SetY(int y);

		virtual void SetTitle(std::string_view title) = 0;
		virtual const std::string& GetTitle() const;
		virtual void SetIcon(std::string_view iconPath) = 0;

		virtual void SetVSync(bool vsync) = 0;
		virtual bool GetVSync() const;
	public:
		static std::shared_ptr<Window> Create(std::string_view title = "Tomato Window", int width = 1280, int height = 720);
	protected:
		WindowData m_Data;
	};
}
