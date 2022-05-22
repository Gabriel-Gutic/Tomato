#include "pchTomato.h"
#include "App.h"


namespace Tomato
{
	App* App::s_Instance = nullptr;
	App::App()
		:isRunning(true)
	{
		TOMATO_ASSERT(!s_Instance, "App already instantiated!");
	}

	App::~App()
	{
	}

	void App::Run()
	{
		while (isRunning)
		{

		}
	}
}