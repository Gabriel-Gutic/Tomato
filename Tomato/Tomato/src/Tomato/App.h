#pragma once
#include "Event/Event.h"
#include "Window.h"
#include "Layer.h"

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

		static std::shared_ptr<FrameBuffer> GetFrameBuffer();
		static std::unique_ptr<Window>& GetWindow();
		static std::vector<std::unique_ptr<Scene>>& GetScenes();
		static std::unique_ptr<Camera>& GetCurrentCamera();

		static void PushEvent(Event* event);
		static void PushLayer(Layer* layer);
		static void PopLayer();
	private:
		bool isRunning;
		std::queue<Event*> m_EventQueue;

		std::shared_ptr<FrameBuffer> m_FrameBuffer;
		std::unique_ptr<Window> m_Window;
		std::vector<std::unique_ptr<Scene>> m_SceneList;

		static App* s_Instance;
	};
}