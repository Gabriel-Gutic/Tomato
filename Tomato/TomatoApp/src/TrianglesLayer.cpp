#include "TrianglesLayer.h"


TrianglesLayer::TrianglesLayer()
{
	for (Tomato::UInt i = 0; i < m_TriangleCounter; i++)
	{
		m_Triangles.push_back(std::make_unique<Tomato::Entity>());
		m_Triangles.back()->AddComponent<Tomato::Component::Transform>().Position = Tomato::Float3(Tomato::Math::RandomFloat(-2, 2), Tomato::Math::RandomFloat(-2, 2), Tomato::Math::RandomFloat(-10, -6));
		m_Triangles.back()->AddComponent<Tomato::Component::Renderer>().Color.abc = Tomato::Float3(Tomato::Math::RandomFloat(0.0f, 1.0f), Tomato::Math::RandomFloat(0.0f, 1.0f), Tomato::Math::RandomFloat(0.0f, 1.0f));
	}
}

void TrianglesLayer::OnUpdate()
{
	for (Tomato::UInt i = 0; i < m_TriangleCounter; i++)
	{
		Tomato::Renderer::DrawTriangle(*m_Triangles[i]);
	}
}
