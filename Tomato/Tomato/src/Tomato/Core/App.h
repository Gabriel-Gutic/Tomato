#pragma once


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
	private:
		bool isRunning;

		static App* s_Instance;
	};
}