#include "pchTomatoApp.h"
#include "MainLayer.h"


MainLayer::MainLayer()
	:m_Scene(Tomato::App::GetScene("Main Scene"))
{
	m_Font = std::make_unique<Tomato::Font>("assets/Fonts/OpenSans/OpenSans/OpenSans-Bold.ttf");

	if (!m_Scene->Contains("triangle"))
	{
		const auto & entity = m_Scene->PushEntity("triangle", std::make_shared<Tomato::Entity>());
		entity->GetComponent<Tomato::MeshRendererComponent>().Sprite = "Triangle";
	}

	if (!m_Scene->Contains("quad"))
	{
		const auto& entity = m_Scene->PushEntity("quad", std::make_shared<Tomato::Entity>());
		entity->GetComponent<Tomato::MeshRendererComponent>().Sprite = "Quad";
	}

	if (!m_Scene->Contains("poly"))
	{
		const auto& entity = m_Scene->PushEntity("poly", std::make_shared<Tomato::Entity>());
		entity->GetComponent<Tomato::MeshRendererComponent>().Sprite = "Polygon";
	}

	//if (!m_Scene->Contains("circle"))
	//	m_Scene->PushEntity("circle", std::make_shared<Tomato::Entity>());
	
	m_Textures["triangle"] = Tomato::Texture::Create("assets/images/bricks.jfif");
	m_Tilemap = std::make_shared<Tomato::Tilemap>("assets/images/Terrain (32x32).png", 32, 32);

	Tomato::App::GetWindow()->SetVSync(true);
}

void MainLayer::OnUpdate(Tomato::Float dt)
{
	//TOMATO_PRINT(Tomato::Input::MouseWorldCoords().ToString());

	Tomato::Renderer::DrawText("0123456789abcdefghijklmnopqrstuvwxyz", *m_Font);
	Tomato::Renderer::DrawTriangle(*m_Scene->GetEntity("triangle"), m_Textures["triangle"]);
	//Tomato::Renderer::Draw(*m_Scene->GetEntity("circle"));
	Tomato::Renderer::DrawQuad(*m_Scene->GetEntity("quad"), m_Tilemap, 1, 1, 3, 3);
	Tomato::Renderer::DrawPolygon(*m_Scene->GetEntity("poly"));
}

void MainLayer::OnGUI()
{
	//ImGui::Begin("Main Layer Menu");
	//ImGui::ColorPicker4("Circle Color", m_Scene->GetEntity<Tomato::Circle>("circle")->GetComponent<Tomato::Color>().ToPtr());
	//if (ImGui::SliderInt("Polygon NOS", &m_Scene->GetEntity("poly")->GetComponent<Tomato::IntComponent>().Value, 3, 100));
	//if (ImGui::SliderFloat("Circle Smoothness", &m_CircleSmoothness, 0.2f, 1.0f))
	//{
	//	m_Scene->GetEntity<Tomato::Circle>("circle")->SetSmoothness(m_CircleSmoothness);
	//}

	//ImGui::End();
}
