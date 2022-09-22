#include "pchTomato.h"
#include "String.h"


namespace Tomato
{
	std::wstring String::ToWString(std::string_view text)
	{
		std::wstring _title(text.size(), L'#');
		mbstowcs(&_title[0], text.data(), text.size());
		return _title;
	}
}