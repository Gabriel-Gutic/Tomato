#include "pchTomatoApp.h"
#include "TrianglesLayer.h"


TrianglesLayer::TrianglesLayer()
{
	for (Tomato::UInt i = 0; i < m_TriangleCounter; i++)
	{
		m_Triangles.push_back(std::make_unique<Tomato::Entity>());
		m_Triangles.back()->AddComponent<Tomato::TransformComponent>().Position = Tomato::Float3(Tomato::Math::RandomFloat(-2, 2), Tomato::Math::RandomFloat(-2, 2), Tomato::Math::RandomFloat(-10, -6));
		auto& mesh = m_Triangles.back()->AddComponent<Tomato::MeshRendererComponent>();
		mesh.Color.abc = Tomato::Float3(Tomato::Math::RandomFloat(0.0f, 1.0f), Tomato::Math::RandomFloat(0.0f, 1.0f), Tomato::Math::RandomFloat(0.0f, 1.0f));
		mesh.mesh = Tomato::Mesh::TriangleMesh();
	}
}

void TrianglesLayer::OnUpdate(Tomato::Float dt)
{
	for (Tomato::UInt i = 0; i < m_TriangleCounter; i++)
	{
		Tomato::Renderer::Draw(*m_Triangles[i]);
	}
}
