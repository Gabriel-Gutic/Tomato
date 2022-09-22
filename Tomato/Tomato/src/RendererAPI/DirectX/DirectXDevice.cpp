#include "pchTomato.h"
#include "DirectXDevice.h"

#include "Tomato/Core/App/App.h"


#include <d3d11.h>
#include <d3dcompiler.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")



namespace Tomato
{
    struct DirectXDeviceData
    {
        static IDXGISwapChain* SwapChain;
        static ID3D11Device* Device;
        static ID3D11DeviceContext* DeviceContext;
        static ID3D11RenderTargetView* BackBuffer;
    };
    IDXGISwapChain*         DirectXDeviceData::SwapChain;
    ID3D11Device*           DirectXDeviceData::Device;
    ID3D11DeviceContext*    DirectXDeviceData::DeviceContext;
    ID3D11RenderTargetView* DirectXDeviceData::BackBuffer;

    DirectXDevice* DirectXDevice::s_Instance = nullptr;
	void DirectXDevice::Initialize()
	{
        TOMATO_ASSERT(!s_Instance, "DirectXDevice allready instantiated!");
        s_Instance = new DirectXDevice();

        DXGI_SWAP_CHAIN_DESC scd = {};

        auto& window = App::GetWindow();

        scd.BufferCount = 1;                                    // one back buffer
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
        scd.BufferDesc.Width = window->GetWidth();              // set the back buffer width
        scd.BufferDesc.Height = window->GetHeight();            // set the back buffer height
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be us
        scd.OutputWindow = std::any_cast<HWND>(window->Get());  // the window to be used
        scd.SampleDesc.Count = 4;                               // how many multisamples
        scd.Windowed = TRUE;                                    // windowed/full-screen mode
        scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow fullscreen switching

        // create a device, device context and 
        // swap chain using the information in the scd struct
        D3D11CreateDeviceAndSwapChain(NULL,
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            NULL,
            NULL,
            NULL,
            D3D11_SDK_VERSION,
            &scd,
            &DirectXDeviceData::SwapChain,
            &DirectXDeviceData::Device,
            NULL,
            &DirectXDeviceData::DeviceContext);

        auto& ins = s_Instance;

        // get the address of the back buffer
        ID3D11Texture2D* pBackBuffer = nullptr;
        DirectXDeviceData::SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

        TOMATO_ASSERT(pBackBuffer, "Failed to get the address of the back buffer!");

        // use the back buffer address to create the render target
        DirectXDeviceData::Device->CreateRenderTargetView(pBackBuffer, NULL, &DirectXDeviceData::BackBuffer);
        pBackBuffer->Release();

        SetRenderTarget();
        SetViewport(window->GetWidth(), window->GetHeight());
    }

	void DirectXDevice::Terminate()
	{
        DirectXDeviceData::SwapChain->SetFullscreenState(FALSE, NULL);  // switch to windowed mode

        DirectXDeviceData::SwapChain->Release();
        DirectXDeviceData::BackBuffer->Release();
        DirectXDeviceData::Device->Release();
        DirectXDeviceData::DeviceContext->Release();
	}

    void DirectXDevice::Clear(const Float4& color)
    {
        // Render a frame
        // clear the back buffer to a deep blue
        DirectXDeviceData::DeviceContext->ClearRenderTargetView(
            DirectXDeviceData::BackBuffer, color.ToPtr());
    }

    void DirectXDevice::Swap()
    {
        // switch the back buffer and the front buffer
        DirectXDeviceData::SwapChain->Present(0, 0);
    }

    void DirectXDevice::SetRenderTarget()
    {
        // set the render target as the back buffer
        DirectXDeviceData::DeviceContext->OMSetRenderTargets(1, &DirectXDeviceData::BackBuffer, NULL);
    }

    void DirectXDevice::RefreshRenderTarget(uint32_t width, uint32_t height)
    {
        if (DirectXDeviceData::Device)
        {
            // Destroy BackBuffer
            if (DirectXDeviceData::BackBuffer) { DirectXDeviceData::BackBuffer->Release(); DirectXDeviceData::BackBuffer = NULL; }
            
            DirectXDeviceData::SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
            
            // Recreate BackBuffer
            ID3D11Texture2D* pBackBuffer;
            DirectXDeviceData::SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
            DirectXDeviceData::Device->CreateRenderTargetView(pBackBuffer, NULL, &DirectXDeviceData::BackBuffer);
            pBackBuffer->Release();

            SetViewport(width, height);
        }
    }

    std::any DirectXDevice::GetDevice()
    {
        return std::any(DirectXDeviceData::Device);
    }

    std::any DirectXDevice::GetDeviceContext()
    {
        return std::any(DirectXDeviceData::DeviceContext);
    }

    std::any DirectXDevice::GetSwapChain()
    {
        return std::any(DirectXDeviceData::SwapChain);
    }

    std::any DirectXDevice::GetBackBuffer()
    {
        return std::any(DirectXDeviceData::BackBuffer);
    }

    void DirectXDevice::SetViewport(uint32_t width, uint32_t height)
    {        
        // Set the viewport
        D3D11_VIEWPORT viewport = {};

        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width = width;
        viewport.Height = height;

        DirectXDeviceData::DeviceContext->RSSetViewports(1, &viewport);
    }
}