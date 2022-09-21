#include "pchTomato.h"
#include "DirectXGUI.h"

#include "Tomato/Core/App/App.h"
#include "DirectXDevice.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_dx11.h>
#include <imgui/backends/imgui_impl_win32.h>

#include "Tomato/Renderer/Renderer3D.h"
#include <d3d11.h>


namespace Tomato
{
	void DirectXGUI::Initialize()
	{
		// Setup Platform/Renderer backends
		TOMATO_ASSERT(ImGui_ImplWin32_Init(std::any_cast<HWND>(App::GetWindow()->Get())), 
			"Failed to configure ImGui for HWND!");
		TOMATO_ASSERT(ImGui_ImplDX11_Init(std::any_cast<ID3D11Device*>(DirectXDevice::GetDevice()),
			std::any_cast<ID3D11DeviceContext*>(DirectXDevice::GetDeviceContext())), 
			"Failed to configure ImGui for DirectX11!");
	}

	void DirectXGUI::Terminate()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
	}

	void DirectXGUI::Begin()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();

		DirectXDevice::SetRenderTarget();
		Renderer3D::Get()->Clear(1.0f, 0.5f, 0.2f, 1.0f);
	}

	void DirectXGUI::End()
	{
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable))
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
}