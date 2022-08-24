#pragma once


namespace Tomato::Component
{
	struct Renderer
	{
		std::string Sprite;
		Float4 Color;

		Renderer(std::string_view sprite = "None", const Float4& color = Float4(1.0f, 1.0f, 1.0f, 1.0f));
	};
}