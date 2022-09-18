#include "pchTomato.h"
#include "OpenGLGUI.h"

#include "Tomato/Core/App/App.h"
#include "OpenGLWindow.h"

#include <GLFW/glfw3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>


namespace Tomato
{
	void OpenGLGUI::Initialize()
	{
		auto window = std::any_cast<GLFWwindow*>(App::GetWindow()->Get());

		TOMATO_ASSERT(ImGui_ImplGlfw_InitForOpenGL(window, true), "Failed to configure ImGui for GLFW!");
		TOMATO_ASSERT(ImGui_ImplOpenGL3_Init(), "Failed to initialize OpenGL3 for ImGui!");
	}

	void OpenGLGUI::Terminate()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
	}

	void OpenGLGUI::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
	}

	void OpenGLGUI::End()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}