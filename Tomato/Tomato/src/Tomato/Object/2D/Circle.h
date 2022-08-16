#pragma once
#include "Object/Object.h"
#include "Object/Transform.h"
#include "Object/Color.h"
#include "Polygon.h"


namespace Tomato
{
	class Circle : public Object, public ColorInterface
	{
	public:
		Circle(const Float3& center = Float3(), Float radius = 0.5f, Float smoothness = 0.5f);
		~Circle() = default;

		void SetRotation(const Float3& rotation);
		const Float3& GetRotation() const;
		void SetCenter(const Float3& center);
		const Float3& GetCenter() const;
		void SetRadius(Float radius);
		Float GetRadius() const;
		void SetSmoothness(Float smoothness);
		Float GetSmoothness() const;

		const Polygon& GetPolygon() const;
	private:
		Float m_Smoothness;
		Polygon m_Polygon;
	};
}
