#pragma once


namespace Tomato::GUI
{
	struct Data {
		static bool IsDockspaceShown;
	};

	void Init();
	void Destroy();

	void Begin();
	void End();

	void ShowDockspace();
	void HideDockspace();
	void Dockspace();
}
