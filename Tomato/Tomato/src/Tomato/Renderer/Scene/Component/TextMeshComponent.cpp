#include "pchTomato.h"
#include "TextMeshComponent.h"

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>


namespace Tomato
{
	TextMeshComponent::TextMeshComponent(std::string_view text)
		:Text(text)
	{
	}

	void TextMeshComponent::ToImGui()
	{
		if (ImGui::CollapsingHeader("TextMesh"))
		{
			ImGui::InputText("Input", &Text);
		}
	}
}


