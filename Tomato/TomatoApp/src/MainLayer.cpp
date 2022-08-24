#include "MainLayer.h"


MainLayer::MainLayer()
	:m_Scene(Tomato::App::GetScenes()["Main Scene"])
{
	if (!m_Scene->Contains("triangle"))
		m_Scene->PushEntity("triangle", std::make_shared<Tomato::Triangle>());

	if (!m_Scene->Contains("quad"))
		m_Scene->PushEntity("quad", std::make_shared<Tomato::Quad>());
	auto quad = m_Scene->GetEntity<Tomato::Quad>("quad");

	if (!m_Scene->Contains("poly"))
	{
		m_Scene->PushEntity("poly", std::make_shared<Tomato::Polygon>(m_PolygonNOS));
	}
	else m_PolygonNOS = m_Scene->GetEntity<Tomato::Polygon>("poly")->GetNumberOfSides();

	if (!m_Scene->Contains("circle"))
		m_Scene->PushEntity("circle", std::make_shared<Tomato::Circle>());
	else
		m_CircleSmoothness = m_Scene->GetEntity<Tomato::Circle>("circle")->GetSmoothness();
	
	m_Textures["triangle"] = Tomato::Texture::Create("assets/images/night.jpg");
	m_Tilemap = std::make_shared<Tomato::Tilemap>("assets/images/Terrain (32x32).png", 32, 32);

	Tomato::App::GetWindow()->SetVSync(false);
}

void MainLayer::OnUpdate()
{
	Tomato::Renderer::Draw(*m_Scene->GetEntity<Tomato::Triangle>("triangle"), m_Textures["triangle"]);
	Tomato::Renderer::Draw(*m_Scene->GetEntity<Tomato::Circle>("circle"));
	Tomato::Renderer::Draw(*m_Scene->GetEntity<Tomato::Quad>("quad"), m_Tilemap, 1, 1, 3, 3);
	Tomato::Renderer::Draw(*m_Scene->GetEntity<Tomato::Polygon>("poly"));
}

void MainLayer::OnGUI()
{
	ImGui::Begin("Main Layer Menu");
	ImGui::ColorPicker4("Circle Color", m_Scene->GetEntity<Tomato::Circle>("circle")->GetComponent<Tomato::Color>().ToPtr());
	if (ImGui::SliderInt("Polygon NOS", &m_PolygonNOS, 3, 100))
	{
		m_Scene->GetEntity<Tomato::Polygon>("poly")->SetNumberOfSides(m_PolygonNOS);
	}
	if (ImGui::SliderFloat("Circle Smoothness", &m_CircleSmoothness, 0.2f, 1.0f))
	{
		m_Scene->GetEntity<Tomato::Circle>("circle")->SetSmoothness(m_CircleSmoothness);
	}

	if (m_Scene->GetEntities()["quad"]->HasComponent<Tomato::Transform>())
	{
		m_Scene->GetEntities()["quad"]->GetComponent<Tomato::Transform>().ToImGui();
	}

	ImGui::End();
}
