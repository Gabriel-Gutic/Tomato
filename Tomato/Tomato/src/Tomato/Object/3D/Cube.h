#pragma once
#include "Object/2D/Quad.h"


namespace Tomato
{
	enum class CubeSide
	{
		Bottom, Top, North, South, East, West
	};

	class Cube : public Object
	{
	public:
		Cube();
		virtual ~Cube() = default;

		std::unordered_map<CubeSide, Quad>& GetSides();
		const std::unordered_map<CubeSide, Quad>& GetSides() const;
	protected:
		std::unordered_map<CubeSide, Quad> m_Sides;
	};
}

