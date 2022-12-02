#pragma once
#include "Character.h"

namespace Tomato
{
	class Font
	{
	public:
		Font(std::string_view filePath);
		~Font();

		const Character& operator[](char chr) const;
		const std::array<Character, 128>& GetChars() const;

		Float2 GetSize(std::string_view text, float fontSize = 12.0f) const;

		void RenderText(std::string_view text, const Float3& center = Float3(), const Float4& color = Float4(1.0f, 1.0f, 1.0f, 1.0f), float fontSize = 12.0f, const Float3& rotation = Float3(0.0f)) const;
	private:
		std::array<Character, 128> m_Chars;
	};
}
