#include "pchTomato.h"
#include "DirectXWindow.h"

#ifdef TOMATO_PLATFORM_WINDOWS

#include "Tomato/Core/App/App.h"
#include "Tomato/Renderer/Renderer3D.h"
#include "Tomato/Event/Events.h"

#include "DirectXCodes.h"
#include "DirectXDevice.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/backends/imgui_impl_dx11.h>


#include <d3d11.h>


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
            uint32_t y = lParam >> 16;

            App::PushEvent(new MouseMoveEvent(static_cast<double>(x), static_cast<double>(y)));
        } break;
        case WM_MOUSEWHEEL:
        {
            int16_t delta = wParam >> 16;
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
                DirectXDevice::SetBackBuffer(DirectXDevice::RefreshRenderTarget(DirectXDevice::GetBackBuffer(), width, height));
                if (Renderer3D::Get() != nullptr)
                {
                    if (Renderer3D::GetFrameBuffer() != nullptr)
                        Renderer3D::SetFrameBuffer(
                            std::any_cast<std::shared_ptr<FrameBuffer>>(
                                DirectXDevice::RefreshRenderTarget(
                                    Renderer3D::GetFrameBuffer()
                                    , width, height)));
                }
            }

            data.Width = static_cast<int>(width);
            data.Height = static_cast<int>(height);
            App::PushEvent(new WindowResizeEvent(width, height));
        } break;
        case WM_MOVE:
        {
            uint32_t x = lParam & 0x0000ffff;
            uint32_t y = lParam >> 16;

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

        auto _title = String::ToWString(title);

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

        SetIcon("assets/Logo/logo.ico");
	}

	DirectXWindow::~DirectXWindow()
	{
        try 
        {
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
        RECT windowRect = { m_Data.X, m_Data.Y, m_Data.X + width, m_Data.Y + height };                      // set the size, but not the position
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);      // adjust the size
        m_Data.Width = width;
        m_Data.Height = height;

        HWND hWnd = std::any_cast<HWND>(m_Handle);
        SetWindowPos(hWnd, 0, windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_SHOWWINDOW);
    }

    void DirectXWindow::SetWidth(int width)
    {
        SetSize(width, m_Data.Height);
    }

    void DirectXWindow::SetHeight(int height)
    {
        SetSize(m_Data.Width, height);
    }

    void DirectXWindow::SetPos(int x, int y)
    {
        RECT windowRect = { x, y, x + m_Data.Width, y + m_Data.Height };                      // set the size, but not the position
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

        HWND hWnd = std::any_cast<HWND>(m_Handle);
        m_Data.X = windowRect.left;
        m_Data.Y = windowRect.top;
        SetWindowPos(hWnd, 0, m_Data.X, m_Data.Y, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_SHOWWINDOW);   
    }

    void DirectXWindow::SetTitle(std::string_view title)
    {
        HWND hWnd = std::any_cast<HWND>(m_Handle);
        SetWindowText(hWnd, String::ToWString(title).data());
    }

    void DirectXWindow::SetIcon(std::string_view iconPath)
    {
        HWND hWnd = std::any_cast<HWND>(m_Handle);
        if (File::Exist(iconPath))
        {
            if (iconPath.substr(iconPath.length() - 4) == ".ico")
            {
                HANDLE icon = LoadImage(std::any_cast<HINSTANCE>(App::GetArgs().at("hInstance")),
                    String::ToWString(iconPath).c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
                SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)(icon));
            }
            else
            {
                TOMATO_ERROR("Not a valid .ico file: '{0}'!", iconPath.data());
            }
        }
        else 
        {
            TOMATO_ERROR("Icon '{0}' not found!", iconPath.data());
        }
    }

    void DirectXWindow::SetVSync(bool vsync)
    {
        m_Data.VSync = vsync;
    }

    void DirectXWindow::SetFullscreen(bool fullscreen)
    {
        m_Data.Fullscreen = fullscreen;
        BOOL _fullscreen = fullscreen ? TRUE : FALSE;
        std::any_cast<IDXGISwapChain*>(DirectXDevice::GetSwapChain())->SetFullscreenState(_fullscreen, NULL);
    }
}

#endif