#include "pchTomato.h"
#include "File.h"


namespace Tomato
{
	std::optional<std::string> File::Read(std::string_view source)
	{
		std::ifstream file(source.data());

		if (!file)
		{
			return {};
		}

		std::stringstream ss;
		ss << file.rdbuf();
		file.close();

		return ss.str();
	}
}


