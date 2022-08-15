#pragma once
#include "Event/Event.h"
#include "Window.h"
#include "ImGuiLayer.h"

#include "Renderer/Scene.h"
#include "Renderer/Buffer/FrameBuffer.h"


namespace Tomato
{
	class App
	{
	public:
		App();
		~App();
		Int Run();

		static App* Get() { return s_Instance; }
		static App* Create();
		static void Exit();

		static std::unique_ptr<Window>& GetWindow();
		static std::unordered_map<std::string, std::unique_ptr<Scene>>& GetScenes();
		static const std::unique_ptr<Camera>& GetCurrentCamera();

		static void PushEvent(Event* event);
		static const std::unique_ptr<Scene>& CreateScene(std::string_view name);
		static void RemoveScene(std::string_view name);
		static const std::unique_ptr<Scene>& GetScene(std::string_view name);
		static const std::unique_ptr<Scene>& SetCurrentScene(std::string_view name);
		static const std::unique_ptr<Scene>& GetCurrentScene();
		static const std::string& GetCurrentSceneName();
	
		static void PushImGuiLayer(std::string_view name, ImGuiLayer* layer);
		static void RemoveImGuiLayer(std::string_view name);
	private:
		bool isRunning;
		std::queue<Event*> m_EventQueue;

		std::unique_ptr<Window> m_Window;
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_SceneMap;
		std::string m_CurrentSceneName;

		std::unordered_map<std::string, ImGuiLayer*> m_ImGuiLayers;

		static App* s_Instance;
	};
}