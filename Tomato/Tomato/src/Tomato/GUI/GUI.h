#pragma once


namespace Tomato::GUI
{
	struct Data {
		static bool IsDockspaceShown;
	};

	void Initialize();
	void Terminate();

	void Begin();
	void End();

	void ShowDockspace();
	void HideDockspace();
	void Dockspace();
}
