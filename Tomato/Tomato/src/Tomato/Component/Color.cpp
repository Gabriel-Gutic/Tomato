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
			ImGui::ColorPicker4("", rgba.ToPtr(), 0.1f);
		}
	}

	std::string Color::GetType() const
	{
		return "Color";
	}

	Float* Color::ToPtr()
	{
		return rgba.ToPtr();
	}

	void Color::SetRGBA(const Float4& rgba)
	{
		this->rgba = rgba;
	}

	void Color::SetRGB(const Float3& rgb)
	{
		this->rgb = rgb;
	}

	void Color::SetRed(Float red)
	{
		this->Red = red;
	}

	void Color::SetGreen(Float green)
	{
		this->Green = green;
	}

	void Color::SetBlue(Float blue)
	{
		this->Blue = blue;
	}

	void Color::SetAlpha(Float alpha)
	{
		this->Alpha = alpha;
	}

	const Float4& Color::GetRGBA() const
	{
		return this->rgba;
	}

	const Float3& Color::GetRGB() const
	{
		return this->rgb;
	}

	Float Color::GetRed() const
	{
		return this->Red;
	}

	Float Color::GetGreen() const
	{
		return this->Green;
	}

	Float Color::GetBlue() const
	{
		return this->Blue;
	}

	Float Color::GetAlpha() const
	{
		return this->Alpha;
	}
}