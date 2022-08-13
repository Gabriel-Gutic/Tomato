#pragma once
#include "Object/Object.h"
#include "Object/Transform.h"


namespace Tomato
{
	class Circle : public Object
	{
	public:
		Circle(const Float3& center = Float3(), Float radius = 1.0f);
		~Circle() = default;

		void SetRotation(const Float3& rotation);
		const Float3& GetRotation() const;
		void SetCenter(const Float3& center);
		const Float3& GetCenter() const;
		void SetRadius(Float radius);
		Float GetRadius() const;
	private:
		Float3 m_Center;
		Float m_Radius;
		Float3 m_Rotation;
	};
}
