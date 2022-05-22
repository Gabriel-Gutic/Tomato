#include "pchTomato.h"
#include "App.h"
#include "DateTime/DateTime.h"


int main(int argc, char** argv)
{
	Tomato::Logger::Init();
	TOMATO_PRINT("Start App: {0}", Tomato::DateTime::Now().ToString());

	auto app = Tomato::App::Create();

	app->Run();

	delete app;

	return 0;
}
