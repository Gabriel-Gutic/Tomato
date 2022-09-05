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

#include "Renderer/Renderer.h"


namespace Tomato
{
	App* App::s_Instance = nullptr;
	App::App()
		:isRunning(true), m_FPS(0), m_FrameCounter(0), m_MenuBar(nullptr)
	{
		TOMATO_BENCHMARKING_FUNCTION();

		TOMATO_ASSERT(!s_Instance, "App already instantiated!");
		s_Instance = this;

		m_Window = std::make_unique<Window>("Tomato Window", 800, 800);

		Renderer::Initialize();

		GUI::Initialize();

		Registry::Initialize();
	}

	App::~App()
	{
		GUI::Terminate();
		Registry::Terminate();
	}

	Int App::Run()
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
					s_Instance->m_DeltaTime = 1.0f / static_cast<Float>(s_Instance->m_FPS);
			}

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
				layer->OnUpdate(m_DeltaTime);
			}

			for (auto& layer : GetCurrentScene()->GetLayers())
			{
				layer->OnUpdate(m_DeltaTime);
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

			if (m_SerializerTimer.GetSeconds() > 2)
			{
				for (auto& serializer : m_Serializers)
				{
					serializer->Serialize();
				}
				m_SerializerTimer.start();
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

	std::unique_ptr<Scene>& App::GetScene(std::string_view name)
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

	void App::SetSceneName(std::string_view old_name, std::string_view new_name)
	{
		auto& ins = s_Instance;
		TOMATO_ASSERT(ins->m_SceneMap.find(old_name.data()) != ins->m_SceneMap.end(), "Scene '{0}' doesn't exist!", old_name.data());
	
		auto nodeHandler = ins->m_SceneMap.extract(old_name.data());
		nodeHandler.key() = new_name.data();
		ins->m_SceneMap.insert(std::move(nodeHandler));
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

	UInt App::GetFPS()
	{
		return s_Instance->m_FPS;
	}

	Float App::GetDeltaTime()
	{
		return s_Instance->m_DeltaTime;
	}

	void App::Exit()
	{
		s_Instance->isRunning = false;
	}
}