#include "pchTomato.h"
#include "Color.h"


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

	ColorInterface::ColorInterface()
	{
		m_Callback = [](const Color&) {/*Default Callback*/};
	}

	ColorInterface::ColorInterface(const ColorInterface& ci)
	{
		m_Callback = ci.m_Callback;
		m_Color = ci.m_Color;
	}

	void ColorInterface::SetColor(const Color& color)
	{
		m_Color = color;
		m_Callback(m_Color);
	}

	void ColorInterface::SetRGB(const Float3& rgb)
	{
		m_Color.rgb = rgb;
		m_Callback(m_Color);
	}

	void ColorInterface::SetRed(Float red)
	{
		m_Color.Red = red;
		m_Callback(m_Color);
	}

	void ColorInterface::SetGreen(Float green)
	{
		m_Color.Green = green;
		m_Callback(m_Color);
	}

	void ColorInterface::SetBlue(Float blue)
	{
		m_Color.Blue = blue;
		m_Callback(m_Color);
	}

	void ColorInterface::SetAlpha(Float alpha)
	{
		m_Color.Alpha = alpha;
		m_Callback(m_Color);
	}

	const Color& ColorInterface::GetColor() const
	{
		return m_Color;
	}

	const Float4& ColorInterface::GetRGBA() const
	{
		return m_Color.rgba;
	}

	const Float3& ColorInterface::GetRGB() const
	{
		return m_Color.rgb;
	}

	Float ColorInterface::GetRed() const
	{
		return m_Color.Red;
	}

	Float ColorInterface::GetGreen() const
	{
		return m_Color.Green;
	}

	Float ColorInterface::GetBlue() const
	{
		return m_Color.Blue;
	}

	Float ColorInterface::GetAlpha() const
	{
		return m_Color.Alpha;
	}

	void ColorInterface::SetCallback(const std::function<void(const Color&)>& func)
	{
		m_Callback = func;
	}


}