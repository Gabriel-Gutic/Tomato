#pragma once


namespace Tomato
{
	class String
	{
	public:
		static std::wstring ToWString(std::string_view text);
	};
}
