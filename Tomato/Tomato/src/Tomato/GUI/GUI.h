#pragma once

#include "Renderer/Buffer/FrameBuffer.h"


namespace Tomato::GUI
{
	void Initialize();
	void Terminate();

	void Begin();
	void End();

	void ShowDockspace();
	void HideDockspace();
	void Dockspace();

	void RenderWindow(const std::shared_ptr<FrameBuffer>& fb, bool centered = false);

	void ShowMainMenu();
	void HideMainMenu();
	bool IsMainMenuShown();

	void ShowSecondMenu();
	void HideSecondMenu();
	bool IsSecondMenuShown();
	
	void SetDarkThemeColors();
}
