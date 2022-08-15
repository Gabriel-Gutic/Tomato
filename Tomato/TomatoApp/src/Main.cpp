#include "Tomato.h"


class FirstLayer : public Tomato::Layer
{
public:
	FirstLayer()
		:m_TriangleColor(Tomato::Float4(1.0f, 1.0f, 1.0f, 1.0f))
	{
		m_Timer = Tomato::Timer();

		m_Triangle1 = std::make_shared<Tomato::Triangle>();
		m_Textures["triangle"] =  Tomato::Texture::Create("assets/images/night.jpg");
		
		m_Quad1 = std::make_shared<Tomato::Quad>();
		m_Cube1 = std::make_shared<Tomato::Cube>();
		m_Polygon = std::make_shared<Tomato::Polygon>(m_PolygonNOS);

		m_Textures["grass_top"] = Tomato::Texture::Create("assets/images/grass_top.jpg");
		m_Textures["grass_side"] = Tomato::Texture::Create("assets/images/grass_side.png");
		m_Textures["grass_bottom"] = Tomato::Texture::Create("assets/images/grass_bottom.png");

		m_Triangle1->SetPosition(Tomato::Float3(1.0f, 0.0f, 0.0f));
		m_Quad1->SetPosition(Tomato::Float3(-3.0f, -1.0f, 0.0f));
		m_Cube1->SetPosition(Tomato::Float3(3.0f, 1.0f, 0.0f));
		m_Polygon->SetPosition(Tomato::Float3(3.0f, 3.0f, 0.0f));

		//Circle
		m_Circle1 = std::make_shared<Tomato::Circle>();
		m_Circle1->SetRadius(1.0f);

		for (Tomato::UInt i = 0; i < 1000; i++)
		{
			m_Triangles.push_back(std::make_unique<Tomato::Triangle>());
			m_Triangles.back()->SetPosition(Tomato::Float3(Tomato::Math::RandomFloat(-2, 2), Tomato::Math::RandomFloat(-2, 2), Tomato::Math::RandomFloat(-2, 2)));
			m_Triangles.back()->SetColor(Tomato::Float3(Tomato::Math::RandomFloat(0.0f, 1.0f), Tomato::Math::RandomFloat(0.0f, 1.0f), Tomato::Math::RandomFloat(0.0f, 1.0f)));
		}
		Tomato::App::GetCurrentCamera()->MoveZ(1.0f);
		Tomato::GUI::ShowDockspace();
		Tomato::GUI::ShowRenderWindow();
	}

	~FirstLayer() {}

	virtual void OnUpdate() override
	{
		Tomato::App::GetCurrentCamera()->SetRotation(m_CameraRotation);
		
		//Tomato::Renderer::Draw(*m_Triangle1, m_Textures["triangle"]);
		//
		//m_Cube1->SetRotation(Tomato::Float3(m_Timer.GetMilliseconds() / 10.0f, m_Timer.GetMilliseconds() / 10.0f, m_Timer.GetMilliseconds() / 10.0f));
		//auto& sides = m_Cube1->GetSides();
		//Tomato::Renderer::Draw(sides[Tomato::CubeSide::Top], m_Textures["grass_top"], m_Cube1->GetTransform());
		//Tomato::Renderer::Draw(sides[Tomato::CubeSide::Bottom], m_Textures["grass_bottom"], m_Cube1->GetTransform());
		//Tomato::Renderer::Draw(sides[Tomato::CubeSide::West], m_Textures["grass_side"], m_Cube1->GetTransform());
		//Tomato::Renderer::Draw(sides[Tomato::CubeSide::East], m_Textures["grass_side"], m_Cube1->GetTransform());
		//Tomato::Renderer::Draw(sides[Tomato::CubeSide::North], m_Textures["grass_side"], m_Cube1->GetTransform());
		//Tomato::Renderer::Draw(sides[Tomato::CubeSide::South], m_Textures["grass_side"], m_Cube1->GetTransform());
		//
		//m_Quad1->SetColor(m_TriangleColor.abc);
		//m_Quad1->SetAlpha(m_TriangleColor.d);
		//Tomato::Renderer::Draw(*m_Quad1);
		//
		Tomato::Renderer::Draw(*m_Circle1);
		//
		//for (Tomato::UInt i = 0; i < 1000; i++)
		//	Tomato::Renderer::Draw(*m_Triangles[i]);

		Tomato::Renderer::Draw(*m_Polygon);

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
		ImGui::ColorPicker4("Quad Color", &m_TriangleColor[0]);
		if (ImGui::SliderInt("Polygon NOS", &m_PolygonNOS, 3, 100))
		{
			m_Polygon->SetNumberOfSides(m_PolygonNOS);
		}
		if (ImGui::SliderFloat("Circle Smoothness", &m_CircleSmoothness, 0.2f, 1.0f))
		{
			m_Circle1->SetSmoothness(m_CircleSmoothness);
		}

		ImGui::End();
	}
private:
	Tomato::Float m_Speed = 0.2f;
	Tomato::Float m_FOV = 45.0f;
	Tomato::Timer m_Timer;
	Tomato::Float3 m_CameraRotation;
	Tomato::Float4 m_TriangleColor;
	Tomato::Int m_PolygonNOS = 6;
	Tomato::Float m_CircleSmoothness = 0.5f;

	std::vector<std::unique_ptr<Tomato::Triangle>> m_Triangles;

	std::unordered_map<std::string, std::shared_ptr<Tomato::Texture>> m_Textures;

	std::shared_ptr<Tomato::Triangle> m_Triangle1;
	std::shared_ptr<Tomato::Quad> m_Quad1;
	std::shared_ptr<Tomato::Polygon> m_Polygon;
	std::shared_ptr<Tomato::Cube> m_Cube1;
	std::shared_ptr<Tomato::Circle> m_Circle1;
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
	TOMATO_BENCHMARKING_FUNCTION();
	return new TomatoApp();
}
