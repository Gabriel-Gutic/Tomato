#include "MainLayer.h"

MainLayer::MainLayer()
	:m_CircleColor(Tomato::Float4(1.0f, 1.0f, 1.0f, 1.0f))
{
	m_Triangle = std::make_shared<Tomato::Triangle>();
	m_Textures["triangle"] = Tomato::Texture::Create("assets/images/night.jpg");

	m_Polygon = std::make_shared<Tomato::Polygon>(m_PolygonNOS);

	m_Triangle->SetPosition(Tomato::Float3(1.0f, -1.0f, 0.0f));
	m_Polygon->SetPosition(Tomato::Float3(2.0f, 2.0f, 0.0f));

	//Circle
	m_Circle = std::make_shared<Tomato::Circle>();
	m_Circle->SetRadius(1.0f);

	//Tilemap
	m_Quad = std::make_shared<Tomato::Quad>();
	m_Quad->SetPosition(Tomato::Float3(-2.0f, -1.0f, 0.0f));

	m_Tilemap = std::make_shared<Tomato::Tilemap>("assets/images/Terrain (32x32).png", 32, 32);
}

void MainLayer::OnUpdate()
{
	Tomato::Renderer::Draw(*m_Triangle, m_Textures["triangle"]);

	m_Circle->SetColor(m_CircleColor);
	Tomato::Renderer::Draw(*m_Quad, m_Tilemap, 1, 1, 3, 3);

	Tomato::Renderer::Draw(*m_Circle);

	Tomato::Renderer::Draw(*m_Polygon);
}

void MainLayer::OnGUI()
{
	ImGui::Begin("Main Layer Menu");
	ImGui::ColorPicker4("Quad Color", &m_CircleColor[0]);
	if (ImGui::SliderInt("Polygon NOS", &m_PolygonNOS, 3, 100))
	{
		m_Polygon->SetNumberOfSides(m_PolygonNOS);
	}
	if (ImGui::SliderFloat("Circle Smoothness", &m_CircleSmoothness, 0.2f, 1.0f))
	{
		m_Circle->SetSmoothness(m_CircleSmoothness);
	}
	ImGui::End();
}
