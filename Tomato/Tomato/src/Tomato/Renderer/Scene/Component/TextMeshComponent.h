#pragma once


namespace Tomato
{
	class TextMeshComponent
	{
	public:
		std::string Text;

		TextMeshComponent(std::string_view text = "New Text");
		TextMeshComponent(const TextMeshComponent&) = default;
		~TextMeshComponent() = default;

		void ToImGui();
	};
}
