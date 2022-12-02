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
	private:
		std::array<Character, 128> m_Chars;
	};
}
