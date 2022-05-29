#include "Tomato.h"


class FirstLayer : public Tomato::Layer
{
public:
	FirstLayer()
	{
		Tomato::Timer T;

		const int n = 10;
		Tomato::Matrix<Tomato::Float, n, n> M(1);
		
		std::ifstream input("assets/matrix.txt");
		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				input >> M[i][j];
		
		input.close();
		
		PRINT(M.GetDeterminant());

		PRINT(T.SecondsToString());
		PRINT(T.MillisecondsToString());
		PRINT(T.MicrosecondsToString());
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
