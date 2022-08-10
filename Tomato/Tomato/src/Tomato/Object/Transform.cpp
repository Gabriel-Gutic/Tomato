#include "pchTomato.h"
#include "Transform.h"


namespace Tomato
{
	void TransformInterface::SetPosition(const Float3& position)
	{
		m_Transform.Position = position;
	}

	void TransformInterface::SetScale(const Float3& scale)
	{
		m_Transform.Scale = scale;
	}

	void TransformInterface::SetRotation(const Float3& rotation)
	{
		m_Transform.Rotation = rotation;
	}

	const Float3& TransformInterface::GetPosition() const
	{
		return m_Transform.Position;
	}

	const Float3& TransformInterface::GetScale() const
	{
		return m_Transform.Scale;
	}

	const Float3& TransformInterface::GetRotation() const
	{
		return m_Transform.Rotation;
	}

	Float3 TransformInterface::TransformCoords(const Float3& vector) const
	{
		// Translate * Rotate * Scale
		Float3 new_coords = Quaternion::Rotate(vector, m_Transform.Rotation);
		new_coords = (Math::Scale(m_Transform.Scale) * Math::Translate(m_Transform.Position) * Float4(new_coords, 1.0f)).xyz;

		return new_coords;
	}
}


