#include "pchTomato.h"
#include "App.h"

#include <imgui/imgui.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GUI/GUI.h"
#include "Renderer/ShaderProgram.h"


namespace Tomato
{
	App* App::s_Instance = nullptr;
	App::App()
		:isRunning(true)
	{
		TOMATO_ASSERT(!s_Instance, "App already instantiated!");
		s_Instance = this;

		m_Window = std::make_unique<Window>();

		GUI::Init();
	}

	App::~App()
	{
		GUI::Destroy();
	}

	void App::Run()
	{
		float coords[] =
		{
			-0.5f, -0.5f,
			-0.5f,  0.5f,
			 0.5f, -0.5f
		};
		unsigned int vb;
		glCreateBuffers(1, &vb);
		glBindBuffer(GL_ARRAY_BUFFER, vb);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);

		std::shared_ptr<ShaderProgram> shaderProgram = std::make_shared<ShaderProgram>("assets/Shaders/VertexShader.glsl", "assets/Shaders/FragmentShader.glsl");

		while (isRunning)
		{
			while (!m_EventQueue.empty())
			{
				auto& e = *m_EventQueue.front();

				if (e.GetType() == EventType::WindowClose)
				{
					Exit();
				}

				TOMATO_PRINT(e.ToString());

				for (auto& layer : m_LayerStack)
				{
					layer->OnEvent(e);
				}

				delete m_EventQueue.front();
				m_EventQueue.pop();
			}

			m_Window->Clear(1.0f, 0.0f, 0.0f);

			shaderProgram->Use();

			glDrawArrays(GL_TRIANGLES, 0, 3);

			for (auto& layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			shaderProgram->Use(false);

			GUI::Begin();
			
			ImGui::ShowDemoWindow();
			
			ImGui::Begin("First Layer");
			ImGui::End();
			
			for (auto& layer : m_LayerStack)
			{
				layer->OnGUI();
			}
			
			GUI::End();

			m_Window->Swap();
		}
	}

	void App::PushEvent(Event* event)
	{
		s_Instance->m_EventQueue.push(event);
	}

	void App::PushLayer(Layer* layer)
	{
		s_Instance->m_LayerStack.push_back(layer);
	}

	void App::PopLayer()
	{
		s_Instance->m_LayerStack.pop_back();
	}

	std::unique_ptr<Window>& App::GetWindow()
	{
		return s_Instance->m_Window;
	}

	void App::Exit()
	{
		s_Instance->isRunning = false;
	}
}