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

	Mat4 TransformInterface::GetTransform() const
	{
		// Translate * Rotate * Scale
		Mat4 result = Math::Translate(m_Transform.Position);
		result = result * Math::Rotate(90.0f);
		result = result * Math::Scale(m_Transform.Scale);

		return result;
	}
}


