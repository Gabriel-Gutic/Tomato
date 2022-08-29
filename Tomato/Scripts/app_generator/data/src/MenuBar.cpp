#include "pch{ProjectName}.h"
#include "{ProjectName}MenuBar.h"


{ProjectName}MenuBar::{ProjectName}MenuBar()
{
	Tomato::GUI::ShowMainMenu();
	//Tomato::GUI::HideMainMenu();
	//Tomato::GUI::ShowSecondMenu();
	Tomato::GUI::HideSecondMenu();
}

void {ProjectName}MenuBar::MainMenu()
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

void {ProjectName}MenuBar::SecondMenu()
{
	if (ImGui::BeginMenu("Second Menu"))
	{
		ImGui::EndMenu();
	}
}