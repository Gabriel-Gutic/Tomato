#include "pchTomato.h"
#include "DirectXDevice.h"

#ifdef TOMATO_PLATFORM_WINDOWS
#include "Tomato/Core/App/App.h"
#include "Tomato/Renderer/Renderer3D.h"

#include "DirectXFrameBuffer.h"


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
        static ID3D11RenderTargetView* FrameBuffer;
        static ID3D11RasterizerState* RasterizerState;
    };
    IDXGISwapChain*         DirectXDeviceData::SwapChain = nullptr;
    ID3D11Device*           DirectXDeviceData::Device = nullptr;
    ID3D11DeviceContext*    DirectXDeviceData::DeviceContext = nullptr;
    ID3D11RenderTargetView* DirectXDeviceData::FrameBuffer = nullptr;
    ID3D11RasterizerState*  DirectXDeviceData::RasterizerState = nullptr;

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
        DirectXDeviceData::Device->CreateRenderTargetView(pBackBuffer, NULL, &DirectXDeviceData::FrameBuffer);
        pBackBuffer->Release();

        SetRenderTarget(DirectXDeviceData::FrameBuffer);

        D3D11_RASTERIZER_DESC rasterizerDescription;
        rasterizerDescription.AntialiasedLineEnable = false;
        rasterizerDescription.CullMode = D3D11_CULL_BACK;
        rasterizerDescription.DepthBias = 0;
        rasterizerDescription.DepthBiasClamp = 0.0f;
        rasterizerDescription.DepthClipEnable = true;
        rasterizerDescription.FillMode = D3D11_FILL_SOLID;
        rasterizerDescription.FrontCounterClockwise = false;

        rasterizerDescription.MultisampleEnable = false;
        rasterizerDescription.ScissorEnable = false;
        rasterizerDescription.SlopeScaledDepthBias = 0.0f;

        TOMATO_ASSERT(!FAILED(DirectXDeviceData::Device->CreateRasterizerState(&rasterizerDescription, &DirectXDeviceData::RasterizerState)),
            "Failed to create the Rasterizer State!");
        DirectXDeviceData::DeviceContext->RSSetState(DirectXDeviceData::RasterizerState);

        SetViewport(window->GetWidth(), window->GetHeight());
    }

	void DirectXDevice::Terminate()
	{
        DirectXDeviceData::SwapChain->SetFullscreenState(FALSE, NULL);  // switch to windowed mode

        DirectXDeviceData::SwapChain->Release();
        DirectXDeviceData::FrameBuffer->Release();
        DirectXDeviceData::Device->Release();
        DirectXDeviceData::DeviceContext->Release();
	}

    void DirectXDevice::Clear(const Float4& color)
    {
        ID3D11RenderTargetView* rt;
        ID3D11DepthStencilView* dsv;
        DirectXDeviceData::DeviceContext->OMGetRenderTargets(1, &rt, &dsv);
        DirectXDeviceData::DeviceContext->ClearRenderTargetView(rt, color.ToPtr());
    }

    void DirectXDevice::Swap()
    {
        // switch the back buffer and the front buffer
        uint32_t vsync = App::GetWindow()->GetVSync() ? 1 : 0;
        DirectXDeviceData::SwapChain->Present(vsync, 0);
    }

    void DirectXDevice::SetRenderTarget(std::any rt)
    {
        ID3D11RenderTargetView* rtv = std::any_cast<ID3D11RenderTargetView*>(rt);
        // set the render target as the back buffer
        DirectXDeviceData::DeviceContext->OMSetRenderTargets(1, &rtv, NULL);
    }

    std::any DirectXDevice::RefreshRenderTarget(std::any rt, uint32_t width, uint32_t height)
    {
        if (DirectXDeviceData::Device)
        {
            try
            {
                ID3D11RenderTargetView* rtv = std::any_cast<ID3D11RenderTargetView*>(rt);
                if (rtv)
                {
                    rtv->Release();
                    rtv = nullptr;
                }

                DirectXDeviceData::SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
                
                ID3D11Texture2D* pBackBuffer;
                DirectXDeviceData::SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
                DirectXDeviceData::Device->CreateRenderTargetView(
                    pBackBuffer, NULL, &rtv);
                pBackBuffer->Release();
                return rtv;
            } 
            catch (std::bad_any_cast)
            {
                try
                {
                    std::shared_ptr<FrameBuffer> fb = std::any_cast<std::shared_ptr<FrameBuffer>>(rt);
                    fb = FrameBuffer::CreateShared(width, height);

                    return fb;
                }
                catch (std::bad_any_cast)
                {
                    TOMATO_ASSERT(0, "Invalid render target!");
                }
            }
        }
        return nullptr;
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
        return std::any(DirectXDeviceData::FrameBuffer);
    }

    void DirectXDevice::SetBackBuffer(std::any backbuffer)
    {
        try 
        {
            DirectXDeviceData::FrameBuffer = std::any_cast<ID3D11RenderTargetView*>(backbuffer);
        }
        catch (std::bad_any_cast){}
    }

    void DirectXDevice::SetViewport(uint32_t width, uint32_t height)
    {        
        if (DirectXDeviceData::DeviceContext)
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
}
#endif // TOMATO_PLATFORM_WINDOWS