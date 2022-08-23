#include "pchTomato.h"
#include "Color.h"

#include <imgui/imgui.h>


namespace Tomato
{
	Color::Color(Float r, Float g, Float b, Float a)
		:Red(r), Green(g), Blue(b), Alpha(a)
	{
	}

	Color::Color(const Float3& rgb)
		:rgba(Float4(rgb, 1.0f))
	{
	}

	Color::Color(const Float4& rgba)
		:rgba(rgba)
	{
	}

	Color::Color(const Color& other)
	{
		rgba = other.rgba;
	}

	Color& Color::operator=(const Color& other)
	{
		// Guard self assignment
		if (this == &other)
			return *this;

		this->rgba = other.rgba;
		return *this;
	}

	void Color::ToImGui()
	{
		if (ImGui::CollapsingHeader("Color"))
		{
			ImGui::ColorPicker4("", rgba.ToPtr());
		}
	}

	Float* Color::ToPtr()
	{
		return rgba.ToPtr();
	}
}