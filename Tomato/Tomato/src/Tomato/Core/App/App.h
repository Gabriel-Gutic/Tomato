#pragma once
#include "Event/Event.h"
#include "Window.h"
#include "ImGuiLayer.h"

#include "Renderer/Scene/Scene.h"
#include "Renderer/Scene/SceneSerializer.h"
#include "Renderer/Buffer/FrameBuffer.h"
#include "MenuBar.h"


namespace Tomato
{
	class App
	{
	public:
		App(const std::unordered_map<std::string, std::any>& args = {});
		virtual ~App();
		int Run();

		static App* Get() { return s_Instance; }
		static App* Create(const std::unordered_map<std::string, std::any>& args = {});
		static void Exit();
		 
		static const std::shared_ptr<Window>& GetWindow();
		static void SetMenuBar(MenuBar* menuBar);
		static const std::unique_ptr<MenuBar>& GetMenuBar();
		static std::unordered_map<std::string, std::unique_ptr<Scene>>& GetScenes();
		static const std::unique_ptr<Entity>& GetCurrentCamera();
		static unsigned int GetFPS();
		static float GetDeltaTime();

		static void PushEvent(Event* event);
		static const std::unique_ptr<Scene>& CreateScene(std::string_view name);
		static void RemoveScene(std::string_view name);
		static std::unique_ptr<Scene>& GetScene(std::string_view name);
		static const std::unique_ptr<Scene>& SetCurrentScene(std::string_view name);
		static const std::unique_ptr<Scene>& GetCurrentScene();
		static const std::string& GetCurrentSceneName();
		static void SetSceneName(std::string_view old_name, std::string_view new_name);
		static void InitSceneSerializer(std::string_view sceneName, std::string_view  filePath);

		static void PushImGuiLayer(std::string_view name, ImGuiLayer* layer);
		static void RemoveImGuiLayer(std::string_view name);

		static const std::unordered_map<std::string, std::any>& GetArgs();
	private:
		unsigned int m_FPS;
		float m_DeltaTime;
		unsigned int m_FrameCounter;
		Timer m_FrameTimer;
		Timer m_SerializerTimer;
		bool isRunning;
		std::queue<Event*> m_EventQueue;

		std::shared_ptr<Window> m_Window;
		std::unique_ptr<MenuBar> m_MenuBar;
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_SceneMap;
		std::vector<std::unique_ptr<Serializer>> m_Serializers;
		std::string m_CurrentSceneName;

		std::unordered_map<std::string, ImGuiLayer*> m_ImGuiLayers;

		std::unordered_map<std::string, std::any> m_Args;
		static App* s_Instance;
	};
}