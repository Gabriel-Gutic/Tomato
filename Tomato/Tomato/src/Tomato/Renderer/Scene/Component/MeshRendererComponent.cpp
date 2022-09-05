#include "pchTomato.h"
#include "MeshRendererComponent.h"

#include <imgui/imgui.h>


namespace Tomato
{
	MeshRendererComponent::MeshRendererComponent(std::string_view sprite, const Float4& color, const Mesh& mesh)
		:Sprite(sprite), Color(color), mesh(mesh)
	{

	}

	void MeshRendererComponent::ToImGui()
	{
		if (ImGui::CollapsingHeader("Mesh Renderer"))
		{
			ImGui::Text(("Sprite: " + Sprite).c_str());
			ImGui::ColorEdit4("Color", Color.ToPtr());
		}
	}
}
