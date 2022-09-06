#include "pchTomato.h"
#include "App.h"
#include "Core/DateTime/DateTime.h"


int main(int argc, char** argv)
{
	TOMATO_BENCHMARKING_START_SESSION("Logger Initialization", "benchmarking/logger_init.json");
	Tomato::Logger::Init();
	TOMATO_PRINT("Start App: {0}", Tomato::DateTime::Now().ToString());
	TOMATO_BENCHMARKING_END_SESSION();

	TOMATO_BENCHMARKING_START_SESSION("App Initialization", "benchmarking/app_init.json");
	auto app = Tomato::App::Create();
	int result = -1;
	TOMATO_BENCHMARKING_END_SESSION();

	if (app)
	{
		TOMATO_BENCHMARKING_START_SESSION("Running Application", "benchmarking/run_init.json");
		result = app->Run();
		TOMATO_BENCHMARKING_END_SESSION();

		TOMATO_PRINT("Deleting App...");
		delete app;
	}
	else
	{
		TOMATO_ERROR("App was not startup properly!");
	}

	return result;
}
