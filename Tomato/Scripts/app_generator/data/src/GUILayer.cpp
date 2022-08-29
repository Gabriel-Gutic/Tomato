#include "pch{ProjectName}.h"
#include "GUILayer.h"

GUILayer::GUILayer()
{
	Tomato::GUI::ShowDockspace();
	Tomato::GUI::HideRenderWindow();
}

void GUILayer::OnUpdate(Tomato::Float dt)
{
}

void GUILayer::OnGUI()
{
}

void GUILayer::OnEvent(const Tomato::Event& e)
{
}
