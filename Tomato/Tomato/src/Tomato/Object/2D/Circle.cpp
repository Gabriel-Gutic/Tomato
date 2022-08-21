#include "pchTomato.h"
#include "Circle.h"
#include "Polygon.h"
#include "Component/Transform.h"
#include "Component/Color.h"


namespace Tomato
{
	Circle::Circle(Float smoothness)
	{
		AddComponent(std::make_shared<Transform>());
		AddComponent(std::make_shared<Color>());
		SetSmoothness(smoothness);
	}

	Circle::Circle(const Circle& other)
	{
		m_Components = other.m_Components;
		m_Vertices = other.m_Vertices;
		m_Smoothness = other.m_Smoothness;
	}

	void Circle::SetSmoothness(Float smoothness)
	{
		m_Smoothness = smoothness;
		if (m_Smoothness < 0.2f)
			m_Smoothness = 0.2f;
		if (m_Smoothness > 1.0f)
			m_Smoothness = 1.0f;

		TOMATO_BENCHMARKING_FUNCTION();

		UInt nr = static_cast<UInt>(m_Smoothness * static_cast<Float>(c_SmoothnessMultiply));

		m_Vertices.resize(nr + 1);

		auto vec = Polygon::GenerateCoords(nr);
		for (UInt i = 0; i <= nr; i++)
		{
			m_Vertices[i].Coords.xy = vec[i];
		}
	}

	Float Circle::GetSmoothness() const
	{
		return m_Smoothness;
	}

	std::vector<Vertex> Circle::GetVertices()
	{
		return m_Vertices;
	}

	const std::vector<Vertex>& Circle::GetVertices() const
	{
		return m_Vertices;
	}

	std::vector<UInt> Circle::GetIndices() const
	{
		TOMATO_BENCHMARKING_FUNCTION();

		UInt nr = static_cast<UInt>(m_Smoothness * c_SmoothnessMultiply);

		std::vector<UInt> indices;
		indices.reserve(3 * nr);
		for (UInt i = 0; i < nr; i++)
		{
			indices.push_back(0);
			indices.push_back(i + 1);
			if (i + 2 > nr)
				indices.push_back(1);
			else
				indices.push_back(i + 2);
		}

		return indices;
	}
}