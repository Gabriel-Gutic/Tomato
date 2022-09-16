#include "pchTomato.h"
#include "App.h"
#include "Core/DateTime/DateTime.h"
#include "RendererAPI/RendererAPI.h"


#ifndef TOMATO_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	TOMATO_BENCHMARKING_START_SESSION("Logger Initialization", "benchmarking/logger_init.json");
	Tomato::Logger::Init();
	TOMATO_BENCHMARKING_END_SESSION();

	bool isRendererChosen = false;
	while (!isRendererChosen)
	{
		std::cout << "Select the Renderer: " << std::endl;
		std::cout << "0 -> Exit" << std::endl;
		std::cout << "1 -> OpenGL" << std::endl;
		std::cout << "2 -> DirectX" << std::endl;
		int choice;
		std::cout << "Choice: "; std::cin >> choice;
		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			Tomato::RendererAPI::SetType(Tomato::RendererType::OpenGL);
			isRendererChosen = true;
			break;
		case 2:
			TOMATO_ERROR("DirectX is only available on Windows Platform!");
			break;
		}

	}

	TOMATO_PRINT("Start App: {0}", Tomato::DateTime::Now().ToString());

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
		TOMATO_ASSERT(0, "App was not startup properly!");
	}

	return result;
}

#else

#include <fcntl.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	// Create a console for debugging
	AllocConsole();
	SetConsoleTitleA("Debugging Console");
	typedef struct { char* _ptr; int _cnt; char* _base; int _flag; int _file; int _charbuf; int _bufsiz; char* _tmpfname; } FILE_COMPLETE;
	*(FILE_COMPLETE*)stdout = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT), "w");
	*(FILE_COMPLETE*)stderr = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT), "w");
	*(FILE_COMPLETE*)stdin = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r");
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);

	TOMATO_BENCHMARKING_START_SESSION("Logger Initialization", "benchmarking/logger_init.json");
	Tomato::Logger::Init();
	TOMATO_BENCHMARKING_END_SESSION();

	bool isRendererChosen = false;
	while (!isRendererChosen)
	{
		std::cout << "Select the Renderer: " << std::endl;
		std::cout << "0 -> Exit" << std::endl;
		std::cout << "1 -> OpenGL" << std::endl;
		std::cout << "2 -> DirectX" << std::endl;
		int choice;
		std::cout << "Choice: "; std::cin >> choice;
		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			Tomato::RendererAPI::SetType(Tomato::RendererType::OpenGL);
			isRendererChosen = true;
			break;
		case 2:
			Tomato::RendererAPI::SetType(Tomato::RendererType::DirectX);
			isRendererChosen = true;
			break;
		}
	}

	TOMATO_PRINT("Start App: {0}", Tomato::DateTime::Now().ToString());

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
		TOMATO_ASSERT(0, "App was not startup properly!");
	}

	return result;
}

#endif // !TOMATO_PLATFORM_WINDOWS