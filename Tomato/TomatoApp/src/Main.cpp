#include "Tomato.h"


class FirstLayer : public Tomato::Layer
{
public:
	FirstLayer()
	{
		Tomato::Matrix<Tomato::Float, 2, 5> M1(1);
		Tomato::Matrix<Tomato::Float, 2, 5> M2(5);

		M1[1][3] = -1;
		M2[1][3] = -1;

		PRINT((M1 + M2).ToString());
		PRINT((M1 - M2).ToString());
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
