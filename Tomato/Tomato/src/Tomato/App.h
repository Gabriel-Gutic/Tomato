#pragma once
#include "Event/Event.h"
#include "Window.h"
#include "Layer.h"

#include "Renderer/Camera.h"


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

		static void PushEvent(Event* event);
		static void PushLayer(Layer* layer);
		static void PopLayer();
	private:
		bool isRunning;
		std::queue<Event*> m_EventQueue;
		std::vector<Layer*> m_LayerStack;

		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Camera> m_Camera;

		static App* s_Instance;
	};
}