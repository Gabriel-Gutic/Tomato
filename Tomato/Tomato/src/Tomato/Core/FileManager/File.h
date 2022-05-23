#pragma once


namespace Tomato
{
	class File
	{
	public:
		static std::optional<std::string> Read(std::string_view source);
	};
}
