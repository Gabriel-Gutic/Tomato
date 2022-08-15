#include "MainLayer.h"

MainLayer::MainLayer()
	:m_TriangleColor(Tomato::Float4(1.0f, 1.0f, 1.0f, 1.0f))
{
	m_Triangle1 = std::make_shared<Tomato::Triangle>();
	m_Textures["triangle"] = Tomato::Texture::Create("assets/images/night.jpg");

	m_Quad1 = std::make_shared<Tomato::Quad>();
	m_Polygon = std::make_shared<Tomato::Polygon>(m_PolygonNOS);

	m_Triangle1->SetPosition(Tomato::Float3(1.0f, -1.0f, 0.0f));
	m_Quad1->SetPosition(Tomato::Float3(-2.0f, -1.0f, 0.0f));
	m_Polygon->SetPosition(Tomato::Float3(2.0f, 2.0f, 0.0f));

	//Circle
	m_Circle1 = std::make_shared<Tomato::Circle>();
	m_Circle1->SetRadius(1.0f);
}

void MainLayer::OnUpdate()
{

	Tomato::Renderer::Draw(*m_Triangle1, m_Textures["triangle"]);

	m_Quad1->SetColor(m_TriangleColor.abc);
	m_Quad1->SetAlpha(m_TriangleColor.d);
	Tomato::Renderer::Draw(*m_Quad1);

	Tomato::Renderer::Draw(*m_Circle1);

	Tomato::Renderer::Draw(*m_Polygon);
}

void MainLayer::OnGUI()
{
	ImGui::Begin("Main Layer Menu");
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
