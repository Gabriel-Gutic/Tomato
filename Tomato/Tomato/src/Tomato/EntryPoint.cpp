#include "pchTomato.h"
#include "App.h"
#include "Core/DateTime/DateTime.h"


int main(int argc, char** argv)
{
	Tomato::Logger::Init();
	TOMATO_PRINT("Start App: {0}", Tomato::DateTime::Now().ToString());

	auto app = Tomato::App::Create();
	int result = -1;

	if (app)
	{
		result = app->Run();

		TOMATO_PRINT("Deleting App...");
		delete app;
	}
	else
	{
		TOMATO_ERROR("App was not startup properly");
	}

	return result;
}
