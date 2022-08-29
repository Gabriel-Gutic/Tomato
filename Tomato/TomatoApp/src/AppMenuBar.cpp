#include "pchTomatoApp.h"
#include "AppMenuBar.h"


AppMenuBar::AppMenuBar()
{
	Tomato::GUI::ShowMainMenu();
	//Tomato::GUI::HideMainMenu();
	//Tomato::GUI::ShowSecondMenu();
	Tomato::GUI::HideSecondMenu();
}

void AppMenuBar::MainMenu()
{
	if (ImGui::BeginMenu("Main Menu"))
	{
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Exit"))
	{
		Tomato::App::Exit();
		ImGui::EndMenu();
	}
}

void AppMenuBar::SecondMenu()
{
	if (ImGui::BeginMenu("Second Menu"))
	{
		ImGui::EndMenu();
	}
}