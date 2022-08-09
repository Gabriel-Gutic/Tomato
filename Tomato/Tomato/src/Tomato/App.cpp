#include "pchTomato.h"
#include "App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GUI/GUI.h"
#include "Renderer/Shader/ShaderProgram.h"

#include "Renderer/Buffer/VertexBuffer.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Texture/Texture.h"
#include "Renderer/Camera.h"

#include "Renderer/Renderer.h"


namespace Tomato
{
	App* App::s_Instance = nullptr;
	App::App()
		:isRunning(true)
	{
		TOMATO_ASSERT(!s_Instance, "App already instantiated!");
		s_Instance = this;

		m_Window = std::make_unique<Window>("Tomato Window", 800, 800);

		GUI::Initialize();

		Renderer::Initialize();

		m_SceneList.push_back(std::make_unique<Scene>());
	}

	App::~App()
	{
		GUI::Terminate();
	}

	Int App::Run()
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>("assets/images/plain.png");

		while (isRunning)
		{
			while (!m_EventQueue.empty())
			{
				const auto& e = *m_EventQueue.front();

				if (e.GetType() == EventType::WindowClose)
				{
					Exit();
				}

				TOMATO_PRINT(e.ToString());

				for (auto& layer : m_SceneList[0]->GetLayers())
				{
					layer->OnEvent(e);
				}

				delete m_EventQueue.front();
				m_EventQueue.pop();
			}

			m_Window->Clear(1.0f, 0.0f, 0.0f);

			texture->Bind();

			Renderer::Begin();

			for (auto& layer : m_SceneList[0]->GetLayers())
			{
				layer->OnUpdate();
			}

			Renderer::End();

			GUI::Begin();
			
			for (auto& layer : m_SceneList[0]->GetLayers())
			{
				layer->OnGUI();
			}
			
			GUI::End();

			m_Window->Swap();
		}

		return 0;
	}

	void App::PushEvent(Event* event)
	{
		s_Instance->m_EventQueue.push(event);
	}

	void App::PushLayer(Layer* layer)
	{
		s_Instance->m_SceneList[0]->GetLayers().push_back(layer);
	}

	void App::PopLayer()
	{
		s_Instance->m_SceneList[0]->GetLayers().pop_back();
	}

	std::unique_ptr<Window>& App::GetWindow()
	{
		return s_Instance->m_Window;
	}

	std::vector<std::unique_ptr<Scene>>& App::GetScenes()
	{
		return s_Instance->m_SceneList;
	}

	std::unique_ptr<Camera>& App::GetCurrentCamera()
	{
		return s_Instance->m_SceneList[0]->GetCamera();
	}

	void App::Exit()
	{
		s_Instance->isRunning = false;
	}
}