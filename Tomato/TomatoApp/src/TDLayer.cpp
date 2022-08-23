#include "TDLayer.h"

TDLayer::TDLayer()
{
	m_Timer = Tomato::Timer();
	m_Cube = std::make_shared<Tomato::Cube>();
	m_Cube->AddComponent<Tomato::Transform>();

	m_Textures["grass_top"] = Tomato::Texture::Create("assets/images/grass_top.jpg");
	m_Textures["grass_side"] = Tomato::Texture::Create("assets/images/grass_side.png");
	m_Textures["grass_bottom"] = Tomato::Texture::Create("assets/images/grass_bottom.png");
}

void TDLayer::OnUpdate()
{
	auto& tran = m_Cube->GetComponent<Tomato::Transform>();
	tran.Rotation = Tomato::Float3(m_Timer.GetMilliseconds() / 10.0f, m_Timer.GetMilliseconds() / 10.0f, m_Timer.GetMilliseconds() / 10.0f);

	auto& sides = m_Cube->GetSides();
	auto mat = tran.Get();
	Tomato::Renderer::Draw(sides[Tomato::CubeSide::Top], m_Textures["grass_top"], mat);
	Tomato::Renderer::Draw(sides[Tomato::CubeSide::Bottom], m_Textures["grass_bottom"], mat);
	Tomato::Renderer::Draw(sides[Tomato::CubeSide::West], m_Textures["grass_side"], mat);
	Tomato::Renderer::Draw(sides[Tomato::CubeSide::East], m_Textures["grass_side"], mat);
	Tomato::Renderer::Draw(sides[Tomato::CubeSide::North], m_Textures["grass_side"], mat);
	Tomato::Renderer::Draw(sides[Tomato::CubeSide::South], m_Textures["grass_side"], mat);
}
