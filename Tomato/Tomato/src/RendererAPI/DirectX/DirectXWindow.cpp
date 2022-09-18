#include "pchTomato.h"
#include "DirectXWindow.h"

#include "Tomato/Core/App/App.h"
#include "Tomato/Event/Events.h"
#include "DirectXCodes.h"
#include "DirectXDevice.h"


#include <Windows.h>
#include <commctrl.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/backends/imgui_impl_dx11.h>


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Tomato
{
    // Forward declare message handler from imgui_impl_win32.cpp

    static LRESULT CALLBACK WindowProc(HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam)
    {    
        if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
            return true;

        auto& data = *reinterpret_cast<WindowData*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        // sort through and find what code to run for the message given
        switch (message)
        {
        case WM_KEYDOWN:
        {
            App::PushEvent(new KeyPressEvent(DirectXCodes::Cast(wParam)));
        } break;
        case WM_KEYUP:
        {
            App::PushEvent(new KeyReleaseEvent(DirectXCodes::Cast(wParam)));
        } break;
        case WM_SYSKEYDOWN:
        {
            App::PushEvent(new KeyPressEvent(TOMATO_KEY_ALT));
        } break;
        case WM_SYSKEYUP:
        {
            App::PushEvent(new KeyReleaseEvent(TOMATO_KEY_ALT));
        } break;
        case WM_CHAR:
        {
            App::PushEvent(new CharEvent(wParam));
        } break;
        case WM_LBUTTONDOWN:
        {
            App::PushEvent(new MouseButtonPressEvent(TOMATO_MOUSE_BUTTON_LEFT));
        } break;
        case WM_LBUTTONUP:
        {
            App::PushEvent(new MouseButtonReleaseEvent(TOMATO_MOUSE_BUTTON_LEFT));
        } break;
        case WM_RBUTTONDOWN:
        {
            App::PushEvent(new MouseButtonPressEvent(TOMATO_MOUSE_BUTTON_RIGHT));
        } break;
        case WM_RBUTTONUP:
        {
            App::PushEvent(new MouseButtonReleaseEvent(TOMATO_MOUSE_BUTTON_RIGHT));
        } break;
        case WM_MBUTTONDOWN:
        {
            App::PushEvent(new MouseButtonPressEvent(TOMATO_MOUSE_BUTTON_MIDDLE));
        } break;
        case WM_MBUTTONUP:
        {
            App::PushEvent(new MouseButtonReleaseEvent(TOMATO_MOUSE_BUTTON_MIDDLE));
        } break;
        case WM_XBUTTONDOWN:
        {
            switch ((wParam & 0x000f0000) >> 16)
            {
            case XBUTTON1:
                App::PushEvent(new MouseButtonPressEvent(TOMATO_MOUSE_BUTTON_4));
                break;
            case XBUTTON2:
                App::PushEvent(new MouseButtonPressEvent(TOMATO_MOUSE_BUTTON_5));
                break;
            }
        } break;
        case WM_XBUTTONUP:
        {
            switch ((wParam & 0x000f0000) >> 16)
            {
            case XBUTTON1:
                App::PushEvent(new MouseButtonReleaseEvent(TOMATO_MOUSE_BUTTON_4));
                break;
            case XBUTTON2:
                App::PushEvent(new MouseButtonReleaseEvent(TOMATO_MOUSE_BUTTON_5));
                break;
            }
        } break;
        case WM_MOUSEMOVE:
        {
            uint32_t x = lParam & 0x0000ffff;
            uint32_t y = (lParam & 0xffff0000) >> 16;

            App::PushEvent(new MouseMoveEvent(static_cast<double>(x), static_cast<double>(y)));
        } break;
        case WM_MOUSEWHEEL:
        {
            int16_t delta = (wParam & 0xffff0000) >> 16;
            float value = static_cast<float>(delta) / static_cast<float>(WHEEL_DELTA);

            App::PushEvent(new WheelEvent(value));
        } break;
        case WM_SIZE:
        {
            switch (wParam)
            {
            case SIZE_MAXIMIZED:
            {
                App::PushEvent(new WindowMaximizeEvent(true));
                App::PushEvent(new WindowMinimizeEvent(false));
            } break;
            case SIZE_MINIMIZED:
            {
                App::PushEvent(new WindowMinimizeEvent(true));
                App::PushEvent(new WindowMaximizeEvent(false));
            } break;
            default:
            {
                App::PushEvent(new WindowMinimizeEvent(false));
                App::PushEvent(new WindowMaximizeEvent(false));
            } break;
            }

            uint32_t width = lParam & 0x0000ffff;
            uint32_t height = (lParam & 0xffff0000) >> 16;

            if (wParam != SIZE_MINIMIZED)
            {
                DirectXDevice::RefreshRenderTarget(width, height);
            }

            data.Width = static_cast<int>(width);
            data.Height = static_cast<int>(height);
            App::PushEvent(new WindowResizeEvent(width, height));
        } break;
        case WM_MOVE:
        {
            uint32_t x = lParam & 0x0000ffff;
            uint32_t y = (lParam & 0xffff0000) >> 16;

            data.X = x;
            data.Y = y;
        } break;
        case WM_DESTROY:
        {
            App::PushEvent(new WindowCloseEvent());
        } break;
        }

        // Handle any messages the switch statement didn't
        return DefWindowProc(hWnd, message, wParam, lParam);

    }

	DirectXWindow::DirectXWindow(std::string_view title, int width, int height)
		:Window(title, width, height)
	{
        DirectXCodes::Setup();

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

        auto hwnd = std::any_cast<HWND>(m_Handle);

        // Set the window user pointer
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&m_Data));

        // display the window on the screen
        ShowWindow(hwnd, std::any_cast<int>(args.at("nShowCmd")));
	}

	DirectXWindow::~DirectXWindow()
	{
        try {
            DestroyWindow(std::any_cast<HWND>(m_Handle));
            m_Handle = 0; // Clear the Handler
        }
        catch (const std::bad_any_cast& error){}

	}

    std::any DirectXWindow::Get()
    {
        return m_Handle;
    }

    void DirectXWindow::DispatchEvents() const
    {
        // Check to see if any messages are waiting in the queue
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Translate the message and dispatch it to WindowProc()
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
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