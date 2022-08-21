#include "pchTomato.h"
#include "Transform.h"

#include <imgui/imgui.h>


namespace Tomato
{
	Transform::Transform(const Float3& position, const Float3& scale, const Float3& rotation)
		:m_Position(position), m_Scale(scale), m_Rotation(rotation)
	{}

	void Transform::SetPosition(const Float3& position)
	{
		m_Position = position;
	}

	void Transform::SetScale(const Float3& scale)
	{
		m_Scale = scale;
	}

	void Transform::SetRotation(const Float3& rotation)
	{
		m_Rotation = rotation;
	}

	const Float3& Transform::GetPosition() const
	{
		return m_Position;
	}

	const Float3& Transform::GetScale() const
	{
		return m_Scale;
	}

	const Float3& Transform::GetRotation() const
	{
		return m_Rotation;
	}

	Float3& Transform::GetPosition()
	{
		return m_Position;
	}

	Float3& Transform::GetScale()
	{
		return m_Scale;
	}

	Float3& Transform::GetRotation()
	{
		return m_Rotation;
	}

	Float3 Transform::Apply(const Float3& vector) const
	{
		// Translate * Rotate * Scale
		Float3 new_coords = Quaternion::Rotate(vector, m_Rotation);
		new_coords = (Math::Translate(m_Position) * Math::Scale(m_Scale) * Float4(new_coords, 1.0f)).xyz;

		return new_coords;
	}

	void Transform::ToImGui()
	{
		if (ImGui::CollapsingHeader("Transform"))
		{
			ImGui::DragFloat3("Position", m_Position.ToPtr(), 0.1f);
			ImGui::DragFloat3("Scale", m_Scale.ToPtr(), 0.1f);
			ImGui::DragFloat3("Rotation", m_Rotation.ToPtr(), 0.1f);
		}
	}

	std::string Transform::GetType() const
	{
		return "Transform";
	}
}


