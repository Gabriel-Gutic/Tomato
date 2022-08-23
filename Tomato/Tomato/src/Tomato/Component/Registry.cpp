#include "pchTomato.h"
#include "Registry.h"


namespace Tomato
{
	Registry* Registry::s_Instance = nullptr;
	void Registry::Initialize()
	{
		TOMATO_ASSERT(!s_Instance, "Registry already instantiated!");

		s_Instance = new Registry();
	}

	void Registry::Terminate()
	{
		delete s_Instance;
	}

	Registry* Registry::Get()
	{
		return s_Instance;
	}

}