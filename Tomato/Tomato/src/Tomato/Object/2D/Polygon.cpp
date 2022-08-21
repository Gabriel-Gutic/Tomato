#include "pchTomato.h"
#include "Polygon.h"
#include "Component/Transform.h"
#include "Component/Color.h"


namespace Tomato
{
	Polygon::Polygon(UInt numberOfSides)
	{
		AddComponent(std::make_shared<Transform>());
		AddComponent(std::make_shared<Color>());
		SetNumberOfSides(numberOfSides);
	}

	void Polygon::SetNumberOfSides(UInt numberOfSides)
	{
		TOMATO_BENCHMARKING_FUNCTION();
		m_NumberOfSides = numberOfSides;

		m_Vertices.resize(numberOfSides + 1);

		auto vec = GenerateCoords(numberOfSides);
		for (UInt i = 0; i <= numberOfSides; i++)
		{
			m_Vertices[i].Coords.xy = vec[i];
		}
	}
	 
	UInt Polygon::GetNumberOfSides() const
	{
		return m_NumberOfSides;
	}

	std::vector<Vertex> Polygon::GetVertices()
	{
		return m_Vertices;
	}

	const std::vector<Vertex>& Polygon::GetVertices() const
	{
		return m_Vertices;
	}

	std::vector<UInt> Polygon::GetIndices() const
	{
		TOMATO_BENCHMARKING_FUNCTION();

		std::vector<UInt> indices;
		indices.reserve(3 * m_NumberOfSides);
		for (UInt i = 0; i < m_NumberOfSides; i++)
		{
			indices.push_back(0);
			indices.push_back(i + 1);
			if (i + 2 > m_NumberOfSides)
				indices.push_back(1);
			else
				indices.push_back(i + 2);
		}

		return indices;
	}

	std::vector<Float2> Polygon::GenerateCoords(UInt numberOfSides)
	{
		TOMATO_BENCHMARKING_FUNCTION();
		TOMATO_ASSERT(numberOfSides >= 3, "You can't create a polygon with {0} sides", numberOfSides);
		Float angle = 360.0f / static_cast<Float>(numberOfSides);

		std::vector<Float2> vec;
		vec.reserve(numberOfSides + 1);

		vec.emplace_back();
		vec.emplace_back(0.0f, 0.5f);

		Float radius = 0.5f;
		Float2 center = Float2();
		Float t = acosf((vec[1].x - center.x) / radius);

		for (UInt i = 1; i < numberOfSides; i++)
		{
			vec.emplace_back(center.x + radius * cosf(t - Math::Radians(angle)), center.y + radius * sinf(t - Math::Radians(angle)));
			t -= Math::Radians(angle);
		}

		return vec;
	}

}