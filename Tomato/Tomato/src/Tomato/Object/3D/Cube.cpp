#include "pchTomato.h"
#include "Cube.h"


namespace Tomato
{
	Cube::Cube()
	{
		//Bottom
		m_Sides[CubeSide::Bottom] = Quad();
		m_Sides[CubeSide::Bottom].SetRotation(Float3(90.0f,  0.0f, 0.0f));
		m_Sides[CubeSide::Bottom].SetPosition(Float3(0.0f, -0.5f, 0.0f));
		m_Sides[CubeSide::Bottom].SetColor(Float3(1.0f, 0.5f, 0.5f));
		
		//Top
		m_Sides[CubeSide::Top] = Quad();
		m_Sides[CubeSide::Top].SetRotation(Float3(90.0f, 0.0f, 0.0f));
		m_Sides[CubeSide::Top].SetPosition(Float3(0.0f, 0.5f, 0.0f));
		m_Sides[CubeSide::Top].SetColor(Float3(0.0f, 1.0f, 1.0f));
		
		//East
		m_Sides[CubeSide::East] = Quad();
		m_Sides[CubeSide::East].SetRotation(Float3(0.0f, 90.0f, 0.0f));
		m_Sides[CubeSide::East].SetPosition(Float3(0.5f, 0.0f, 0.0f));
		m_Sides[CubeSide::East].SetColor(Float3(0.0f, 0.0f, 1.0f));

		//West
		m_Sides[CubeSide::West] = Quad();
		m_Sides[CubeSide::West].SetRotation(Float3(0.0f, 90.0f, 0.0f));
		m_Sides[CubeSide::West].SetPosition(Float3(-0.5f, 0.0f, 0.0f));
		m_Sides[CubeSide::West].SetColor(Float3(0.0f, 1.0f, 0.0f));

		//North
		m_Sides[CubeSide::North] = Quad();
		m_Sides[CubeSide::North].SetPosition(Float3(0.0f, 0.0f, -0.5f));
		m_Sides[CubeSide::North].SetColor(Float3(1.0f, 0.0f, 1.0f));

		//South
		m_Sides[CubeSide::South] = Quad();
		m_Sides[CubeSide::South].SetPosition(Float3(0.0f, 0.0f, 0.5f));
		m_Sides[CubeSide::South].SetColor(Float3(1.0f, 1.0f, 0.0f));
	}

	std::unordered_map<CubeSide, Quad>& Cube::GetSides()
	{
		return m_Sides;
	}

	const std::unordered_map<CubeSide, Quad>& Cube::GetSides() const
	{
		return m_Sides;
	}
}


