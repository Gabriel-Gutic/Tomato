#pragma once

namespace Tomato
{
	class DirectXCodes
	{
	public:
		static void Setup();
		static int Cast(uint64_t code);
	private:
		static std::unordered_map<uint64_t, int> s_Data;
	};
}