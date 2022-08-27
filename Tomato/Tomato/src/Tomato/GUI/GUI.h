#pragma once


namespace Tomato::GUI
{
	void Initialize();
	void Terminate();

	void Begin();
	void End();

	void ShowDockspace();
	void HideDockspace();
	void Dockspace();

	void ShowRenderWindow();
	void HideRenderWindow();
	void RenderWindow();
	bool IsRenderWindowShown();

	void ShowMainMenu();
	void HideMainMenu();
	bool IsMainMenuShown();

	void ShowSecondMenu();
	void HideSecondMenu();
	bool IsSecondMenuShown();
	
	void SetDarkThemeColors();
}
