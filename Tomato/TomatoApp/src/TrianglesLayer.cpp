#include "TrianglesLayer.h"


TrianglesLayer::TrianglesLayer()
{
	for (Tomato::UInt i = 0; i < 1000; i++)
	{
		m_Triangles.push_back(std::make_unique<Tomato::Triangle>());
		m_Triangles.back()->SetPosition(Tomato::Float3(Tomato::Math::RandomFloat(-2, 2), Tomato::Math::RandomFloat(-2, 2), Tomato::Math::RandomFloat(-10, -6)));
		m_Triangles.back()->SetColor(Tomato::Float3(Tomato::Math::RandomFloat(0.0f, 1.0f), Tomato::Math::RandomFloat(0.0f, 1.0f), Tomato::Math::RandomFloat(0.0f, 1.0f)));
	}
}

void TrianglesLayer::OnUpdate()
{
	for (Tomato::UInt i = 0; i < 1000; i++)
		Tomato::Renderer::Draw(*m_Triangles[i]);
}