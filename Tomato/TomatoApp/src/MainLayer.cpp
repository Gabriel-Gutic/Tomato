#include "MainLayer.h"

MainLayer::MainLayer()
	:m_CircleColor(Tomato::Float4(1.0f, 1.0f, 1.0f, 1.0f)),
	m_Scene(Tomato::App::GetScenes()["Main Scene"])
{
	m_Scene->PushObject("triangle", std::make_shared<Tomato::Triangle>());
	auto triangle = m_Scene->GetObject<Tomato::Triangle>("triangle");
	triangle->SetPosition(Tomato::Float3(1.0f, -1.0f, 0.0f));

	m_Scene->PushObject("quad", std::make_shared<Tomato::Quad>());
	auto quad = m_Scene->GetObject<Tomato::Quad>("quad");
	quad->SetPosition(Tomato::Float3(-2.0f, -1.0f, 0.0f));

	m_Scene->PushObject("poly", std::make_shared<Tomato::Polygon>(m_PolygonNOS));
	auto poly = m_Scene->GetObject<Tomato::Polygon>("poly");
	poly->SetPosition(Tomato::Float3(2.0f, 2.0f, 0.0f));

	m_Scene->PushObject("circle", std::make_shared<Tomato::Circle>());
	auto circle = m_Scene->GetObject<Tomato::Circle>("circle");
	circle->SetRadius(1.0f);

	m_Textures["triangle"] = Tomato::Texture::Create("assets/images/night.jpg");
	m_Tilemap = std::make_shared<Tomato::Tilemap>("assets/images/Terrain (32x32).png", 32, 32);
}

void MainLayer::OnUpdate()
{
	Tomato::Renderer::Draw(*m_Scene->GetObject<Tomato::Triangle>("triangle"), m_Textures["triangle"]);

	auto circle = m_Scene->GetObject<Tomato::Circle>("circle");
	circle->SetColor(m_CircleColor);
	Tomato::Renderer::Draw(*circle);

	Tomato::Renderer::Draw(*m_Scene->GetObject<Tomato::Quad>("quad"), m_Tilemap, 1, 1, 3, 3);

	Tomato::Renderer::Draw(*m_Scene->GetObject<Tomato::Polygon>("poly"));
}

void MainLayer::OnGUI()
{
	ImGui::Begin("Main Layer Menu");
	ImGui::ColorPicker4("Quad Color", &m_CircleColor[0]);
	if (ImGui::SliderInt("Polygon NOS", &m_PolygonNOS, 3, 100))
	{
		m_Scene->GetObject<Tomato::Polygon>("poly")->SetNumberOfSides(m_PolygonNOS);
	}
	if (ImGui::SliderFloat("Circle Smoothness", &m_CircleSmoothness, 0.2f, 1.0f))
	{
		m_Scene->GetObject<Tomato::Circle>("circle")->SetSmoothness(m_CircleSmoothness);
	}
	ImGui::End();
}
