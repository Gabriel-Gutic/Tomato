#include "pchTomato.h"
#include "GUI.h"

#include <imgui/imgui.h>

#include "Core/App/App.h"
#include "Renderer/Renderer.h"
#include "GUI_API.h"


namespace Tomato::GUI
{
    struct Data {
        static bool IsDockspaceShown;
        static bool IsRenderWindowShown;
        static bool IsMainMenuShown;
        static bool IsSecondMenuShown;
    };
	bool Data::IsDockspaceShown = false;
	bool Data::IsRenderWindowShown = false;
    bool Data::IsMainMenuShown = false;
    bool Data::IsSecondMenuShown = false;

    static std::unique_ptr<GUI_API> s_GUI_API;
    void Initialize()
    {
        s_GUI_API = GUI_API::CreateUnique();

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
        s_GUI_API->Initialize();

        // Setup Dear ImGui style
        SetDarkThemeColors();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        style.WindowBorderSize = 0.0f;
    }

    void Terminate()
    {
        s_GUI_API->Terminate();
        ImGui::DestroyContext();
    }

    void Begin()
    {
        // feed inputs to dear imgui, start new frame
        s_GUI_API->Begin();
        ImGui::NewFrame();

        if (Data::IsDockspaceShown)
        {
            Dockspace();
            
            if (Data::IsRenderWindowShown)
                RenderWindow();
        }

        //bool demo = true;
        //ImGui::ShowDemoWindow(&demo);
    }

    void End()
    {
        auto& window = App::GetWindow();
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(window->GetWidth(), window->GetHeight());

        // Render dear imgui into screen
        ImGui::Render();
        s_GUI_API->End();
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
        float menu_y = 0.0f;
        auto& window = App::GetWindow();

        if (Data::IsMainMenuShown)
        {
            ImGui::SetNextWindowPos(ImVec2(window->GetX(), window->GetY()));
            ImGui::SetNextWindowSize(ImVec2(window->GetWidth(), window->GetHeight()));
            ImGui::Begin("MainMenuBar Backend", NULL,
                ImGuiWindowFlags_NoDecoration |
                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse |
                ImGuiWindowFlags_NoSavedSettings |
                ImGuiWindowFlags_NoBringToFrontOnFocus |
                ImGuiWindowFlags_MenuBar
            );

            if (ImGui::BeginMenuBar())
            {
                App::GetMenuBar()->MainMenu();
                menu_y += ImGui::GetFrameHeight();
                ImGui::EndMenuBar();
            }

            ImGui::End();
        }

        if (Data::IsSecondMenuShown)
        {
            ImGui::SetNextWindowPos(ImVec2(window->GetX(), window->GetY() + menu_y));
            ImGui::SetNextWindowSize(ImVec2(window->GetWidth(), window->GetHeight() - menu_y));
            ImGui::Begin("SecondMenuBar Backend", NULL,
                ImGuiWindowFlags_NoDecoration |
                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse |
                ImGuiWindowFlags_NoSavedSettings |
                ImGuiWindowFlags_NoBringToFrontOnFocus |
                ImGuiWindowFlags_MenuBar
            );

            if (ImGui::BeginMenuBar())
            {
                App::GetMenuBar()->SecondMenu();
                menu_y += ImGui::GetFrameHeight();
                ImGui::EndMenuBar();
            }

            ImGui::End();
        }

        ImGui::SetNextWindowPos(ImVec2(window->GetX(), window->GetY() + menu_y));
        ImGui::SetNextWindowSize(ImVec2(window->GetWidth(), window->GetHeight() - menu_y));
        ImGui::Begin("DockSpace", NULL,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse
        );

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

        ImGui::Image((ImTextureID)Renderer::GetFrameBuffer()->GetTexture()->GetID(), ImVec2(size.x, (size.x * h) / (float)w));

		ImGui::End();
    }

    bool IsRenderWindowShown()
    {
        return Data::IsRenderWindowShown;
    }

    void ShowMainMenu()
    {
        Data::IsMainMenuShown = true;
    }

    void HideMainMenu()
    {
        Data::IsMainMenuShown = false;
    }

    bool IsMainMenuShown()
    {
        return Data::IsMainMenuShown;
    }

    void ShowSecondMenu()
    {
        Data::IsSecondMenuShown = true;
    }

    void HideSecondMenu()
    {
        Data::IsSecondMenuShown = false;
    }

    bool IsSecondMenuShown()
    {
        return Data::IsSecondMenuShown;
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