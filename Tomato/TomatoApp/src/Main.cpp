#include "Tomato.h"


class FirstLayer : public Tomato::Layer
{
public:
	FirstLayer()
		:m_TriangleColor(Tomato::Float4(1.0f, 1.0f, 1.0f, 1.0f))
	{
		m_Timer = Tomato::Timer();

		m_Triangle1 = std::make_shared<Tomato::Triangle>();
		m_Quad1 = std::make_shared<Tomato::Quad>();
		m_Cube1 = std::make_shared<Tomato::Cube>();

		m_Triangle1->SetPosition(Tomato::Float3(1.0f, 0.0f, 0.0f));

		//m_Quad1->SetScale(Tomato::Float3(10.0f, 10.0f, 1.0f));

		Tomato::GUI::HideDockspace();

	}

	~FirstLayer() {}

	virtual void OnUpdate() override
	{
		Tomato::App::GetCurrentCamera()->SetRotation(m_CameraRotation);
		
		m_Triangle1->SetColor(m_TriangleColor.abc);
		m_Triangle1->SetAlpha(m_TriangleColor.d);
		Tomato::Renderer::Draw(*m_Triangle1);

		m_Cube1->SetRotation(Tomato::Float3(m_Timer.GetMilliseconds() / 10.0f, m_Timer.GetMilliseconds() / 10.0f, m_Timer.GetMilliseconds() / 10.0f));
		Tomato::Renderer::Draw(*m_Cube1);

		const auto& camera = Tomato::App::GetCurrentCamera();
		const auto& window = Tomato::App::GetWindow();

		camera->SetPerspectiveProjection(m_FOV, window->GetAspectRatio(), 0.1f, 100.0f);
		//camera->SetOrthographicProjection(-window->GetAspectRatio(), window->GetAspectRatio(), -1.0f, 1.0f, 0.1f, 100.0f);

		if (Tomato::Input::Keyboard(TOMATO_KEY_LEFT))
			camera->MoveX(-m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_RIGHT))
			camera->MoveX(m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_UP))
			camera->MoveY(m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_DOWN))
			camera->MoveY(-m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_KP_8))
			camera->MoveZ(-m_Speed);
		if (Tomato::Input::Keyboard(TOMATO_KEY_KP_2))
			camera->MoveZ(m_Speed);
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
		
		ImGui::SliderFloat3("Camera Rotation", &m_CameraRotation[0], -90.0f, 90.0f);
		ImGui::ColorPicker4("Triangle Color", &m_TriangleColor[0]);

		ImGui::End();
	}
private:
	Tomato::Float m_Speed = 0.2f;
	Tomato::Float m_FOV = 45.0f;
	Tomato::Timer m_Timer;
	Tomato::Float3 m_CameraRotation;
	Tomato::Float4 m_TriangleColor;

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
