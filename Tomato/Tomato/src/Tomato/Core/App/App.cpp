#include "pchTomato.h"
#include "App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GUI/GUI.h"
#include "Renderer/Shader.h"

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
		TOMATO_BENCHMARKING_FUNCTION();

		TOMATO_ASSERT(!s_Instance, "App already instantiated!");
		s_Instance = this;

		m_Window = std::make_unique<Window>("Tomato Window", 800, 800);

		Renderer::Initialize();

		GUI::Initialize();
	}

	App::~App()
	{
		GUI::Terminate();
	}

	Int App::Run()
	{
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

				for (const auto& [name, layer] : s_Instance->m_ImGuiLayers)
				{
					layer->OnEvent(e);
				}

				for (auto& layer : GetCurrentScene()->GetLayers())
				{
					layer->OnEvent(e);
				}

				delete m_EventQueue.front();
				m_EventQueue.pop();
			}

			Renderer::Begin();

			for (const auto& [name, layer] : s_Instance->m_ImGuiLayers)
			{
				layer->OnUpdate();
			}

			for (auto& layer : GetCurrentScene()->GetLayers())
			{
				layer->OnUpdate();
			}

			Renderer::End();

			GUI::Begin();
			
			for (auto& [name, layer] : s_Instance->m_ImGuiLayers)
			{
				layer->OnGUI();
			}

			for (auto& layer : GetCurrentScene()->GetLayers())
			{
				layer->OnGUI();
			}
			
			GUI::End();

			for (auto& serializer : m_Serializers)
			{
				serializer->Serialize();
			}

			m_Window->Swap();
		}

		return 0;
	}

	void App::PushEvent(Event* event)
	{
		s_Instance->m_EventQueue.push(event);
	}

	const std::unique_ptr<Scene>& App::CreateScene(std::string_view name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(name.data()) == ins->m_SceneMap.end(), "Scene {0} already exist!", name.data());
		ins->m_SceneMap[name.data()] = std::make_unique<Scene>();
		if (ins->m_SceneMap.size() == 1)
			SetCurrentScene(name);
		return ins->m_SceneMap[name.data()];
	}

	void App::RemoveScene(std::string_view name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(name.data()) == ins->m_SceneMap.end(), "Scene {0} already exist!", name.data());
		ins->m_SceneMap.erase(name.data());
	}

	const std::unique_ptr<Scene>& App::GetScene(std::string_view name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(name.data()) != ins->m_SceneMap.end(), "Scene '{0}' doesn't exist!", name.data());
		return ins->m_SceneMap[name.data()];
	}

	const std::unique_ptr<Scene>& App::SetCurrentScene(std::string_view name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(name.data()) != ins->m_SceneMap.end(), "Scene '{0}' doesn't exist!", name.data());
		ins->m_CurrentSceneName = name;
		return ins->m_SceneMap[name.data()];
	}

	const std::unique_ptr<Scene>& App::GetCurrentScene()
	{
		return s_Instance->m_SceneMap[s_Instance->m_CurrentSceneName];
	}

	const std::string& App::GetCurrentSceneName()
	{
		return s_Instance->m_CurrentSceneName;
	}

	void App::InitSceneSerializer(std::string_view sceneName, std::string_view filePath)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(sceneName.data()) != ins->m_SceneMap.end(), "Scene '{0}' doesn't exist!", sceneName.data());
		ins->m_Serializers.push_back(std::make_unique<SceneSerializer>(sceneName, filePath));
		ins->m_Serializers.back()->Deserialize();
	}

	void App::PushImGuiLayer(std::string_view name, ImGuiLayer* layer)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_ImGuiLayers.find(name.data()) == ins->m_ImGuiLayers.end(), "ImGuiLayer '{0}' already exist!", name.data());
		s_Instance->m_ImGuiLayers[name.data()] = layer;
	}

	void App::RemoveImGuiLayer(std::string_view name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_ImGuiLayers.find(name.data()) != ins->m_ImGuiLayers.end(), "ImGuiLayer '{0}' doesn't exist!", name.data());
		s_Instance->m_ImGuiLayers.erase(name.data());
	}

	std::unique_ptr<Window>& App::GetWindow()
	{
		return s_Instance->m_Window;
	}

	std::unordered_map<std::string, std::unique_ptr<Scene>>& App::GetScenes()
	{
		return s_Instance->m_SceneMap;
	}

	const std::unique_ptr<Camera>& App::GetCurrentCamera()
	{
		return s_Instance->m_SceneMap[s_Instance->m_CurrentSceneName]->GetCamera();
	}

	void App::Exit()
	{
		s_Instance->isRunning = false;
	}
}