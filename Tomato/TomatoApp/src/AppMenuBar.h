#pragma once
#include "Tomato.h"


class AppMenuBar : public Tomato::MenuBar
{
public:
	AppMenuBar()
	{
		Tomato::GUI::ShowMainMenu();
		Tomato::GUI::ShowSecondMenu();
	}
	
	void MainMenu() override
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

	void SecondMenu() override
	{
		if (ImGui::BeginMenu("Second Menu"))
		{
			ImGui::EndMenu();
		}
	}
};
