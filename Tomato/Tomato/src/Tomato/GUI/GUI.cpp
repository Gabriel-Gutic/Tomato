#include "pchTomato.h"
#include "GUI.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

#include "App.h"


namespace Tomato::GUI
{
    bool Data::IsDockspaceShown = false;

    void Init()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        //const char* fontPath = "assets/fonts/Roboto/Roboto-Regular.ttf";
        //io.Fonts->AddFontFromFileTTF(fontPath, 16.0f);

        // Setup Platform/Renderer bindings
        auto window = static_cast<GLFWwindow*>(App::GetWindow()->Get());

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
    }

    void Destroy()
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

        if (Data::IsDockspaceShown)
            Dockspace();
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
}