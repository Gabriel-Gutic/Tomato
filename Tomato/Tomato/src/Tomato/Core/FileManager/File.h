#pragma once


namespace Tomato
{
	class File
	{
	public:
		static bool Exist(std::string_view path);
		static std::optional<std::string> Read(std::string_view source);
	};
}
