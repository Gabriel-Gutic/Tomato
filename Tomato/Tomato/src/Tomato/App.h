#pragma once
#include "Event/Event.h"
#include "Window.h"


namespace Tomato
{
	class App
	{
	public:
		App();
		~App();
		void Run();

		static App* Get() { return s_Instance; }
		static App* Create();
		static void Exit();

		static std::unique_ptr<Window>& GetWindow();

		static void PushEvent(Event* event);
	private:
		bool isRunning;
		std::queue<Event*> m_EventQueue;

		std::unique_ptr<Window> m_Window;

		static App* s_Instance;
	};
}