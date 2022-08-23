#include "pchTomato.h"
#include "Cube.h"
#include "Component/Transform.h"
#include "Component/Color.h"


namespace Tomato
{
	Cube::Cube()
	{
		//Bottom
		{
			m_Sides[CubeSide::Bottom] = Quad();
			auto& tran = m_Sides[CubeSide::Bottom].AddComponent<Transform>();
			tran.Rotation = Float3(90.0f, 0.0f, 0.0f);
			tran.Position = Float3(0.0f, -0.5f, 0.0f);
			m_Sides[CubeSide::Bottom].AddComponent<Color>().rgba = Float4(1.0f, 0.5f, 0.5f, 1.0f);
		}

		//Top
		{
			m_Sides[CubeSide::Top] = Quad();
			auto& tran = m_Sides[CubeSide::Top].AddComponent<Transform>();
			tran.Rotation = Float3(90.0f, 0.0f, 0.0f);
			tran.Position = Float3( 0.0f, 0.5f, 0.0f);
			m_Sides[CubeSide::Top].AddComponent<Color>().rgba = Float4(1.0f, 1.0f, 0.5f, 1.0f);
		}
		
		//East
		{
			m_Sides[CubeSide::East] = Quad();
			auto& tran = m_Sides[CubeSide::East].AddComponent<Transform>();
			tran.Rotation = Float3(0.0f, 90.0f, 0.0f);
			tran.Position = Float3(0.5f,  0.0f, 0.0f);
			m_Sides[CubeSide::East].AddComponent<Color>().rgba = Float4(0.0f, 0.0f, 1.0f, 1.0f);
		}

		//West
		{
			m_Sides[CubeSide::West] = Quad();
			auto& tran = m_Sides[CubeSide::West].AddComponent<Transform>();
			tran.Rotation = Float3(0.0f, 90.0f, 0.0f);
			tran.Position = Float3(-0.5f, 0.0f, 0.0f);
			m_Sides[CubeSide::West].AddComponent<Color>().rgba = Float4(0.0f, 1.0f, 0.0f, 1.0f);
		}

		//North
		{
			m_Sides[CubeSide::North] = Quad();
			auto& tran = m_Sides[CubeSide::North].AddComponent<Transform>();
			tran.Position = Float3(0.0f, 0.0f, -0.5f);
			m_Sides[CubeSide::North].AddComponent<Color>().rgba = Float4(1.0f, 0.0f, 1.0f, 1.0f);
		}

		//South
		{
			m_Sides[CubeSide::South] = Quad();
			auto& tran = m_Sides[CubeSide::South].AddComponent<Transform>();
			tran.Position = Float3(0.0f, 0.0f, 0.5f);
			m_Sides[CubeSide::South].AddComponent<Color>().rgba = Float4(1.0f, 1.0f, 0.0f, 1.0f);
		}
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


