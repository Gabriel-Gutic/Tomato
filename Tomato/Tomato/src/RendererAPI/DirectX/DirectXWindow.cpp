#include "pchTomato.h"
#include "DirectXWindow.h"

#include "Tomato/Core/App/App.h"


namespace Tomato
{
    // the WindowProc function prototype
    static LRESULT CALLBACK WindowProc(HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam)
    {    
        // sort through and find what code to run for the message given
        switch (message)
        {
            // this message is read when the window is closed
        case WM_DESTROY:
        {
            // close the application entirely
            return 0;
        } break;
        }

        // Handle any messages the switch statement didn't
        return DefWindowProc(hWnd, message, wParam, lParam);

    }

	DirectXWindow::DirectXWindow(std::string_view title, int width, int height)
		:Window(title, width, height)
	{
        // this struct holds information for the window class
        WNDCLASSEX wc = {};

        // fill in the struct with the needed information
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WindowProc;

        auto& args = App::GetArgs();

        HINSTANCE hInstance = std::any_cast<HINSTANCE>(args.at("hInstance"));
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        // wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.lpszClassName = L"Tomato_DirectX_WindowClass";

        // register the window class
        RegisterClassEx(&wc);

        std::wstring _title(title.size(), L'#');
        mbstowcs(&_title[0], title.data(), title.size());

        // create the window and use the result as the handle
        m_Handle = CreateWindowEx(NULL,
            L"Tomato_DirectX_WindowClass",    // name of the window class
            _title.data(),   // title of the window
            WS_OVERLAPPEDWINDOW,    // window style
            m_Data.X,    // x-position of the window
            m_Data.Y,    // y-position of the window
            m_Data.Width,    // width of the window
            m_Data.Height,    // height of the window
            NULL,    // we have no parent window, NULL
            NULL,    // we aren't using menus, NULL
            hInstance,    // application handle
            NULL);    // used with multiple windows, NULL

        // display the window on the screen
        ShowWindow(std::any_cast<HWND>(m_Handle), std::any_cast<int>(args.at("nShowCmd")));
	}

	DirectXWindow::~DirectXWindow()
	{
	}
    void DirectXWindow::Clear(float r, float g, float b, float a) const
    {
    }
    void DirectXWindow::Clear(const Float4& color) const
    {
    }
    void DirectXWindow::Swap()
    {
    }
    void DirectXWindow::SetSize(int width, int height)
    {
    }
    void DirectXWindow::SetWidth(int width)
    {
    }
    void DirectXWindow::SetHeight(int height)
    {
    }
    void DirectXWindow::SetPos(int x, int y)
    {
    }
    void DirectXWindow::SetTitle(std::string_view title)
    {
    }
    void DirectXWindow::SetIcon(std::string_view iconPath)
    {
    }
    void DirectXWindow::SetVSync(bool vsync)
    {
    }
    void DirectXWindow::SetFullscreen(bool fullscreen)
    {
    }
}