#include "pchTomato.h"
#include "Circle.h"


namespace Tomato
{
	Circle::Circle(const Float3& center, Float radius, Float smoothness)
		:m_Smoothness(smoothness)
	{
		if (m_Smoothness < 0.2f)
			m_Smoothness = 0.2f;
		if (m_Smoothness > 1.0f)
			m_Smoothness = 1.0f;

		m_Polygon = Polygon(static_cast<UInt>(100 * m_Smoothness));
		m_Polygon.SetPosition(center);
		m_Polygon.SetScale(Float3(2 * radius, 2 * radius, 0.0f));
	
		SetCallback([this](const Color& color) {
			m_Polygon.SetColor(color);
		});
	}

	void Circle::SetRotation(const Float3& rotation)
	{
		m_Polygon.SetRotation(rotation);
	}

	const Float3& Circle::GetRotation() const
	{
		return m_Polygon.GetRotation();
	}

	void Circle::SetCenter(const Float3& center)
	{
		m_Polygon.SetPosition(center);
	}

	const Float3& Circle::GetCenter() const
	{
		return m_Polygon.GetPosition();
	}

	void Circle::SetRadius(Float radius)
	{
		m_Polygon.SetScale(Float3(2 * radius, 2 * radius, 0.0f));
	}

	Float Circle::GetRadius() const
	{
		return m_Polygon.GetScale()[0] / 2.0f;
	}

	void Circle::SetSmoothness(Float smoothness)
	{
		m_Smoothness = smoothness;
		if (m_Smoothness < 0.2f)
			m_Smoothness = 0.2f;
		if (m_Smoothness > 1.0f)
			m_Smoothness = 1.0f;

		const Float3 center = GetCenter();
		Float radius = GetRadius();

		m_Polygon = Polygon(static_cast<UInt>(100 * m_Smoothness));
		m_Polygon.SetPosition(center);
		m_Polygon.SetScale(Float3(2 * radius, 2 * radius, 0.0f));
	}

	Float Circle::GetSmoothness() const
	{
		return m_Smoothness;
	}

	const Polygon& Circle::GetPolygon() const
	{
		return m_Polygon;
	}
}