#include "pchTomato.h"
#include "Polygon.h"


namespace Tomato
{
	Polygon::Polygon(UInt numberOfSides)
	{
		SetNumberOfSides(numberOfSides);
	}

	void Polygon::SetNumberOfSides(UInt numberOfSides)
	{
		TOMATO_BENCHMARKING_FUNCTION();
		TOMATO_ASSERT(m_NumberOfSides >= 3, "You can't create a polygon with {0} sides", m_NumberOfSides);
		m_NumberOfSides = numberOfSides;
		Float angle = 360.0f / static_cast<Float>(numberOfSides);
		
		m_Vertices.clear();
		m_Vertices.reserve(numberOfSides + 1);

		m_Vertices.emplace_back(Float3());
		m_Vertices.emplace_back(Float3(0.0f, 0.5f, 0.0f));

		Float radius = 0.5f;
		Float3 center = Float3();
		Float t = acosf((m_Vertices[1].Coords.x - center.x) / radius);

		for (UInt i = 1; i < numberOfSides; i++)
		{
			Float3 coords = Float3(center.x + radius * cosf(t - Math::Radians(angle)), center.y + radius * sinf(t - Math::Radians(angle)), 0.0f);
			m_Vertices.emplace_back(coords);
			t -= Math::Radians(angle);
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

}