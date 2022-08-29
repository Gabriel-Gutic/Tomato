#pragma once


class AppMenuBar : public Tomato::MenuBar
{
public:
	AppMenuBar();
	
	void MainMenu() override;
	void SecondMenu() override;
};
