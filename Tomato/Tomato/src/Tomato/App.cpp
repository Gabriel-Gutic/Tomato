#include "pchTomato.h"
#include "App.h"

#include <imgui/imgui.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GUI/GUI.h"
#include "Renderer/ShaderProgram.h"

#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"


namespace Tomato
{
	App* App::s_Instance = nullptr;
	App::App()
		:isRunning(true)
	{
		TOMATO_ASSERT(!s_Instance, "App already instantiated!");
		s_Instance = this;

		m_Window = std::make_unique<Window>("Tomato Window", 800, 800);

		GUI::Init();
	}

	App::~App()
	{
		GUI::Destroy();
	}

	void App::Run()
	{
		std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(std::initializer_list<Vertex>{
			{ { -0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
			{ { -0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{ {  0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
			{ {  0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f} },
			{ {  1.0f,  0.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}},
		});
		
		unsigned int va;
		glCreateVertexArrays(1, &va);
		glBindVertexArray(va);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(Float3)));

		std::shared_ptr<IndexBuffer> ib = std::make_shared<IndexBuffer>(std::initializer_list<UInt>{
			0, 1, 2,
			2, 3, 1,
			3, 4, 2,
		});

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
			glBindVertexArray(va);
			ib->Bind();

			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, ib->GetSize(), GL_UNSIGNED_INT, (void*)0);

			for (auto& layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			glBindVertexArray(0);

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