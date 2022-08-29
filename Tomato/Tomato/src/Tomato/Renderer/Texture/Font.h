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
	private:
		std::array<Character, 128> m_Chars;
	};
}
