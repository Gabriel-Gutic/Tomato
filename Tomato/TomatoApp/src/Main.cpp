#include "Tomato.h"


class FirstLayer : public Tomato::Layer
{
public:
	FirstLayer()
	{
		Tomato::GUI::HideDockspace();
	}

	~FirstLayer() {}

	virtual void OnUpdate()
	{
		auto& camera = Tomato::App::GetCurrentCamera();
		if (Tomato::Input::Keyboard(TOMATO_KEY_LEFT))
			camera->MoveX(-m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_RIGHT))
			camera->MoveX(m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_UP))
			camera->MoveY(m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_DOWN))
			camera->MoveY(-m_Speed);
	}

	virtual void OnEvent(Tomato::Event& e)
	{

	}

	virtual void OnGUI()
	{
		ImGui::Begin("First ImGui Window");
		ImGui::Text("Hello world!");
		ImGui::End();
	}
private:
	Tomato::Float m_Speed = 0.2f;
};


class TomatoApp : public Tomato::App
{
public:
	TomatoApp()
	{
		PushLayer(new FirstLayer());
	}

	~TomatoApp()
	{

	}
private:
};


Tomato::App* Tomato::App::Create()
{
	return new TomatoApp();
}
