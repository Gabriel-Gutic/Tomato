#include "Tomato.h"


class FirstLayer : public Tomato::Layer
{
public:
	FirstLayer()
	{

	}
	~FirstLayer() {}

	virtual void OnUpdate()
	{

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
