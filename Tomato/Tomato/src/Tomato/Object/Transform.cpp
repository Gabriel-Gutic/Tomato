#include "pchTomato.h"
#include "Transform.h"

#include <imgui/imgui.h>


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

	void TransformInterface::SetTransform(const Transform& tran)
	{
		m_Transform = tran;
	}

	Transform& TransformInterface::GetTransform()
	{
		return m_Transform;
	}

	const Transform& TransformInterface::GetTransform() const
	{
		return m_Transform;
	}

	Float3 TransformInterface::TransformCoords(const Float3& vector) const
	{
		return m_Transform.Apply(vector);
	}

	Float3 Transform::Apply(const Float3& vector) const
	{
		// Translate * Rotate * Scale
		Float3 new_coords = Quaternion::Rotate(vector, Rotation);
		new_coords = (Math::Translate(Position) * Math::Scale(Scale) * Float4(new_coords, 1.0f)).xyz;

		return new_coords;
	}

	void Transform::GUI(std::string_view headerName)
	{
		if (ImGui::CollapsingHeader(headerName.data()))
		{
			ImGui::DragFloat3("Position", Position.ToPtr());
			ImGui::DragFloat3("Scale", Scale.ToPtr());
			ImGui::DragFloat3("Rotation", Rotation.ToPtr());
		}
	}
}


