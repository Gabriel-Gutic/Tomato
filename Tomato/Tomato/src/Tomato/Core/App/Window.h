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
		~Window();

		void Clear(float r, float g, float b, float a) const;
		void Clear(const Float4& color) const;
		void Swap();
		void* Get();

		int GetWidth() const;
		int GetHeight() const;
		std::pair<int, int> GetSize() const;
		void SetSize(int width, int height);
		void SetWidth(int width);
		void SetHeight(int height);
		float GetAspectRatio() const;

		int GetX() const;
		int GetY() const;
		std::pair<int, int> GetPos() const;
		void SetPos(int x, int y);
		void SetX(int x);
		void SetY(int y);

		void SetTitle(std::string_view title);
		const std::string& GetTitle() const;
		void SetIcon(std::string_view iconPath);

		void SetVSync(bool vsync);
		bool GetVSync() const;
	private:
		void* m_Window;
		WindowData m_Data;
	};
}
