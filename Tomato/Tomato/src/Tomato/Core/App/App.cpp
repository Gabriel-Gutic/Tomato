#include "pchTomato.h"
#include "App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GUI/GUI.h"
#include "Renderer/Shader.h"

#include "Renderer/Renderer.h"
#include "Renderer/Renderer3D.h"

#include "Event/KeyboardEvent.h"
#include "Event/Input.h"
#include "Event/KeyboardCodes.h"

namespace Tomato
{
	App* App::s_Instance = nullptr;
	App::App(const std::unordered_map<std::string, std::any>& args)
		:isRunning(true), m_FPS(0), m_FrameCounter(0), m_MenuBar(nullptr), m_Args(args)
	{
		TOMATO_BENCHMARKING_FUNCTION();

		TOMATO_ASSERT(!s_Instance, "App already instantiated!");
		s_Instance = this;

		m_Window = Window::CreateShared();
		TOMATO_ASSERT(m_Window, "Failed to create Tomato Window!");

		if (Renderer::GetType() == RendererType::_3D)
			Renderer3D::Initialize();
		
		GUI::Initialize();
		Registry::Initialize();
	}

	App::~App()
	{
		GUI::Terminate();
		Registry::Terminate();
		if (Renderer::GetType() == RendererType::_3D)
			Renderer3D::Terminate();
	}

	int App::Run()
	{
		while (isRunning)
		{
			m_FrameCounter++;

			if (m_FrameTimer.GetSeconds() >= 1.0)
			{
				m_FPS = m_FrameCounter;
				m_FrameCounter = 0;
				m_FrameTimer.start();

				if (s_Instance->m_FPS != 0)
					s_Instance->m_DeltaTime = 1.0f / static_cast<float>(s_Instance->m_FPS);
			}

			if (m_FPS > 0)
			{
				m_Window->DispatchEvents();

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

				// Close the app if the Exit() was called in through an event
				if (!isRunning) 
					return 0; 

				GUI::Begin();
				if (Renderer::GetType() == RendererType::_3D)
					Renderer3D::Get()->Begin();

				for (const auto& [name, layer] : s_Instance->m_ImGuiLayers)
				{
					layer->OnUpdate(m_DeltaTime);
				}

				for (auto& layer : GetCurrentScene()->GetLayers())
				{
					layer->OnUpdate(m_DeltaTime);
				}

				if (Renderer::GetType() == RendererType::_3D)
					Renderer3D::Get()->End();


				for (auto& [name, layer] : s_Instance->m_ImGuiLayers)
				{
					layer->OnGUI();
				}

				for (auto& layer : GetCurrentScene()->GetLayers())
				{
					layer->OnGUI();
				}

				GUI::End();
				//
				//if (m_SerializerTimer.GetSeconds() > 2)
				//{
				//	for (auto& serializer : m_Serializers)
				//	{
				//		serializer->Serialize();
				//	}
				//	m_SerializerTimer.start();
				//}

				if (Renderer::GetType() == RendererType::_3D)
					Renderer3D::Get()->Swap();
			}
		}

		return 0;
	}

	void App::PushEvent(Event* event)
	{
		s_Instance->m_EventQueue.push(event);
	}

	const std::unique_ptr<Scene>& App::CreateScene(const std::string& name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(name) == ins->m_SceneMap.end(), "Scene {0} already exist!", name);
		ins->m_SceneMap[name] = std::make_unique<Scene>();
		if (ins->m_SceneMap.size() == 1)
			SetCurrentScene(name);
		return ins->m_SceneMap[name];
	}

	void App::RemoveScene(const std::string& name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(name) == ins->m_SceneMap.end(), "Scene {0} already exist!", name);
		ins->m_SceneMap.erase(name);
	}

	std::unique_ptr<Scene>& App::GetScene(const std::string& name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(name) != ins->m_SceneMap.end(), "Scene '{0}' doesn't exist!", name);
		return ins->m_SceneMap[name];
	}

	const std::unique_ptr<Scene>& App::SetCurrentScene(const std::string& name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(name) != ins->m_SceneMap.end(), "Scene '{0}' doesn't exist!", name);
		ins->m_CurrentSceneName = name;
		return ins->m_SceneMap[name];
	}

	const std::unique_ptr<Scene>& App::GetCurrentScene()
	{
		return s_Instance->m_SceneMap[s_Instance->m_CurrentSceneName];
	}

	const std::string& App::GetCurrentSceneName()
	{
		return s_Instance->m_CurrentSceneName;
	}

	void App::SetSceneName(const std::string& old_name, std::string_view new_name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(old_name) != ins->m_SceneMap.end(), "Scene '{0}' doesn't exist!", old_name);
	
		auto nodeHandler = ins->m_SceneMap.extract(old_name);
		nodeHandler.key() = new_name;
		ins->m_SceneMap.insert(std::move(nodeHandler));
	}

	void App::InitSceneSerializer(const std::string& sceneName, std::string_view filePath)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(sceneName) != ins->m_SceneMap.end(), "Scene '{0}' doesn't exist!", sceneName);
		ins->m_Serializers.push_back(std::make_unique<SceneSerializer>(sceneName, filePath));
		ins->m_Serializers.back()->Deserialize();
	}

	void App::PushImGuiLayer(const std::string& name, ImGuiLayer* layer)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_ImGuiLayers.find(name) == ins->m_ImGuiLayers.end(), "ImGuiLayer '{0}' already exist!", name);
		s_Instance->m_ImGuiLayers[name] = layer;
	}

	void App::RemoveImGuiLayer(const std::string& name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_ImGuiLayers.find(name) != ins->m_ImGuiLayers.end(), "ImGuiLayer '{0}' doesn't exist!", name);
		delete s_Instance->m_ImGuiLayers[name];
		s_Instance->m_ImGuiLayers.erase(name);
	}

	const std::unordered_map<std::string, std::any>& App::GetArgs()
	{
		return s_Instance->m_Args;
	}

	const std::shared_ptr<Window>& App::GetWindow()
	{
		return s_Instance->m_Window;
	}

	void App::SetMenuBar(MenuBar* menuBar)
	{
		if (!menuBar)
			s_Instance->m_MenuBar = nullptr;
		s_Instance->m_MenuBar = std::unique_ptr<MenuBar>(menuBar);
	}

	const std::unique_ptr<MenuBar>& App::GetMenuBar()
	{
		return s_Instance->m_MenuBar;
	}

	std::unordered_map<std::string, std::unique_ptr<Scene>>& App::GetScenes()
	{
		return s_Instance->m_SceneMap;
	}

	const std::unique_ptr<Entity>& App::GetCurrentCamera()
	{
		return s_Instance->m_SceneMap[s_Instance->m_CurrentSceneName]->GetCamera();
	}

	unsigned int App::GetFPS()
	{
		return s_Instance->m_FPS;
	}

	float App::GetDeltaTime()
	{
		return s_Instance->m_DeltaTime;
	}

	void App::Exit()
	{
		s_Instance->isRunning = false;
	}
}