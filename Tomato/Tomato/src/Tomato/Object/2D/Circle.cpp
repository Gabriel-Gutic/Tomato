#include "pchTomato.h"
#include "Circle.h"


namespace Tomato
{
	Circle::Circle(const Float3& center, Float radius)
		:m_Center(center), m_Radius(radius)
	{
	}

	void Circle::SetRotation(const Float3& rotation)
	{
		m_Rotation = rotation;
	}

	const Float3& Circle::GetRotation() const
	{
		return m_Rotation;
	}

	void Circle::SetCenter(const Float3& center)
	{
		m_Center = center;
	}

	const Float3& Circle::GetCenter() const
	{
		return m_Center;
	}

	void Circle::SetRadius(Float radius)
	{
		m_Radius = radius;
	}

	Float Circle::GetRadius() const
	{
		return m_Radius;
	}
}