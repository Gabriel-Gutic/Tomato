#include "pchTomato.h"
#include "GUI.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include "Core/App/App.h"
#include "Renderer/Renderer.h"


namespace Tomato::GUI
{
	bool Data::IsDockspaceShown = false;
	bool Data::IsRenderWindowShown = false;

    void Initialize()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        const char* fontPath = "assets/Fonts/Roboto/Roboto-Regular.ttf";
        io.Fonts->AddFontFromFileTTF(fontPath, 16.0f);

        // Setup Platform/Renderer bindings
        auto window = static_cast<GLFWwindow*>(App::GetWindow()->Get());

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        // Setup Dear ImGui style
        SetDarkThemeColors();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
    }

    void Terminate()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Begin()
    {
        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		//bool demo = true;
		//ImGui::ShowDemoWindow(&demo);

        if (Data::IsDockspaceShown)
        {
            Dockspace();
            
            if (Data::IsRenderWindowShown)
                RenderWindow();
        }
    }

    void End()
    {
        auto& window = App::GetWindow();
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(window->GetWidth(), window->GetHeight());

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void GUI::ShowDockspace()
    {
        Data::IsDockspaceShown = true;
    }

    void GUI::HideDockspace()
    {
        Data::IsDockspaceShown = false;
    }

    void GUI::Dockspace()
    {
        auto& window = App::GetWindow();
        ImGui::SetNextWindowPos(ImVec2(window->GetX(), window->GetY()));
        ImGui::SetNextWindowSize(ImVec2(window->GetWidth(), window->GetHeight()));
        ImGui::Begin("DockSpace", NULL,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse
        );

        // TODO: Menu

        // Declare Central dockspace
        auto dockspaceID = ImGui::GetID("HUB_DockSpace");
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);
        ImGui::End();
    }

    void ShowRenderWindow()
    {
        Data::IsRenderWindowShown = true;
    }

    void HideRenderWindow()
    {
        Data::IsRenderWindowShown = false;
    }

    void RenderWindow()
    {
		ImGui::Begin("RenderWindow");

        auto [w, h] = Renderer::GetFrameBuffer()->GetSize();
        ImVec2 size = ImGui::GetWindowSize();

        ImGui::Image((ImTextureID)Renderer::GetFrameBuffer()->GetTexture()->GetID(), ImVec2(size.x, (size.x * h) / (Float)w));

		ImGui::End();
    }

    bool IsRenderWindowShown()
    {
        return Data::IsRenderWindowShown;
    }

	void GUI::SetDarkThemeColors()
	{
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	}
}