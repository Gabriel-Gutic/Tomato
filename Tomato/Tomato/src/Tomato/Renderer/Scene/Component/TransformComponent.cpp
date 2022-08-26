#include "pchTomato.h"
#include "TransformComponent.h"

#include <imgui/imgui.h>


namespace Tomato
{
	TransformComponent::TransformComponent(const Float3& position, const Float3& scale, const Float3& rotation)
		:Position(position), Scale(scale), Rotation(rotation)
	{}

	Mat4 TransformComponent::Get() const
	{
		// Translate * Scale * Rotate
		Mat4 tran = Quaternion::Rotation(Rotation).ToMat4();
		tran = Math::Scale(Scale) * tran;
		tran = Math::Translate(Position) * tran;
		return tran;
	}

	void TransformComponent::ToImGui()
	{
		if (ImGui::CollapsingHeader("Transform"))
		{
			ImGui::DragFloat3("Position", Position.ToPtr(), 0.1f);
			ImGui::DragFloat3("Scale", Scale.ToPtr(), 0.1f);
			ImGui::DragFloat3("Rotation", Rotation.ToPtr(), 0.1f);
		}
	}
}


