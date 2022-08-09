#include "Tomato.h"


class FirstLayer : public Tomato::Layer
{
public:
	FirstLayer()
	{
		m_Triangle1 = std::make_shared<Tomato::Triangle>();
		m_Quad1 = std::make_shared<Tomato::Quad>();
		m_Cube1 = std::make_shared<Tomato::Cube>();

		//m_Triangle1->SetPosition(Tomato::Float3(1.0f, 0.0f, 0.0f));
		//m_Triangle1->SetScale(Tomato::Float3(100.0f, 100.0f, 1.0f));

		//m_Quad1->SetScale(Tomato::Float3(10.0f, 10.0f, 1.0f));

		Tomato::GUI::HideDockspace();
	}

	~FirstLayer() {}

	virtual void OnUpdate() override
	{
		//Tomato::Renderer::Draw(*m_Triangle1);
		Tomato::Renderer::Draw(*m_Quad1);

		//for (const auto& [name, side] : m_Cube1->GetSides())
		//{
		//	PRINT(side.GetPosition().ToString());
		//	Tomato::Renderer::Draw(side);
		//}

		const auto& camera = Tomato::App::GetCurrentCamera();
		const auto& window = Tomato::App::GetWindow();

		//camera->SetPerspectiveProjection(m_FOV, window->GetAspectRatio(), 0.1f, 100.0f);
		camera->SetOrthographicProjection(-window->GetAspectRatio(), window->GetAspectRatio(), -1.0f, 1.0f, 0.1f, 100.0f);

		if (Tomato::Input::Keyboard(TOMATO_KEY_LEFT))
			camera->MoveX(-m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_RIGHT))
			camera->MoveX(m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_UP))
			camera->MoveY(m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_DOWN))
			camera->MoveY(-m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_KP_8))
			camera->MoveZ(m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_KP_2))
			camera->MoveZ(-m_Speed);
	}

	virtual void OnEvent(const Tomato::Event& e) override
	{
		if (e.GetType() == Tomato::EventType::Wheel)
		{
			auto ev = Tomato::Event::Cast<Tomato::WheelEvent>(e);

			m_FOV += (Tomato::Float)ev.GetValue();
		}
	}

	virtual void OnGUI() override
	{
		ImGui::Begin("First ImGui Window");
		ImGui::Text("Hello world!");
		ImGui::End();
	}
private:
	Tomato::Float m_Speed = 0.2f;
	Tomato::Float m_FOV = 45.0f;

	std::shared_ptr<Tomato::Triangle> m_Triangle1;
	std::shared_ptr<Tomato::Quad> m_Quad1;
	std::shared_ptr<Tomato::Cube> m_Cube1;
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
