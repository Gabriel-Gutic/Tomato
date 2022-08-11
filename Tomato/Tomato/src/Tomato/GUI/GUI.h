#pragma once


namespace Tomato::GUI
{
	struct Data {
		static bool IsDockspaceShown;
		static bool IsRenderWindowShown;
	};

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
}
