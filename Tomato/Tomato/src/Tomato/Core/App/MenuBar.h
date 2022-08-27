#pragma once


namespace Tomato
{
	class MenuBar
	{
	public:
		MenuBar() = default;
		~MenuBar() = default;
		virtual void MainMenu(){}
		virtual void SecondMenu(){}
	};
}
