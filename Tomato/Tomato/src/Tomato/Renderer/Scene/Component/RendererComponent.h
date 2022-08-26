#pragma once


namespace Tomato
{
	struct RendererComponent
	{
		std::string Sprite;
		Float4 Color;

		RendererComponent(std::string_view sprite = "None", const Float4& color = Float4(1.0f, 1.0f, 1.0f, 1.0f));
		RendererComponent(const RendererComponent&) = default;
		~RendererComponent() = default;
	};
}