#include "pchTomatoApp.h"
#include "MainLayer.h"


MainLayer::MainLayer()
	:m_Scene(Tomato::App::GetScene("Main Scene"))
{
	m_Font = std::make_unique<Tomato::Font>("assets/Fonts/OpenSans/OpenSans/OpenSans-Regular.ttf");

	if (!m_Scene->Contains("triangle"))
	{
		const auto & entity = m_Scene->PushEntity("triangle", std::make_shared<Tomato::Entity>());
		auto& mesh = entity->GetComponent<Tomato::MeshRendererComponent>();
		mesh.Sprite = "Triangle";
		mesh.mesh = Tomato::Mesh::TriangleMesh();
	}

	if (!m_Scene->Contains("quad"))
	{
		const auto& entity = m_Scene->PushEntity("quad", std::make_shared<Tomato::Entity>());
		auto& mesh = entity->GetComponent<Tomato::MeshRendererComponent>();
		mesh.Sprite = "Quad";
		mesh.mesh = Tomato::Mesh::QuadMesh();
	}

	if (!m_Scene->Contains("poly"))
	{
		const auto& entity = m_Scene->PushEntity("poly", std::make_shared<Tomato::Entity>());
		auto& mesh = entity->GetComponent<Tomato::MeshRendererComponent>();
		mesh.Sprite = "Polygon";
		mesh.mesh = Tomato::Mesh::PolygonMesh(m_PolygonNOS);
	}

	if (!m_Scene->Contains("circle"))
	{
		const auto& entity = m_Scene->PushEntity("circle", std::make_shared<Tomato::Entity>());
		auto& mesh = entity->GetComponent<Tomato::MeshRendererComponent>();
		mesh.Sprite = "Circle";
		mesh.mesh = Tomato::Mesh::CircleMesh(m_CircleSmoothness);
	}
	m_Textures["triangle"] = Tomato::Texture::Create("assets/images/bricks.jfif");
	m_Tilemap = std::make_shared<Tomato::Tilemap>("assets/images/Terrain (32x32).png", 32, 32);

	Tomato::App::GetWindow()->SetVSync(true);
}

void MainLayer::OnUpdate(float dt)
{
	//TOMATO_PRINT(Tomato::Input::MouseWorldCoords().ToString());

	Tomato::Renderer::DrawText("abcdefghijklmnopqrstuvwxyz0123456789", *m_Font);
	Tomato::Renderer::Draw(*m_Scene->GetEntity("triangle"), m_Textures["triangle"]);
	Tomato::Renderer::Draw(*m_Scene->GetEntity("quad"), m_Tilemap, 1, 1, 3, 3);
	Tomato::Renderer::Draw(*m_Scene->GetEntity("poly"));
	Tomato::Renderer::Draw(*m_Scene->GetEntity("circle"));
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
