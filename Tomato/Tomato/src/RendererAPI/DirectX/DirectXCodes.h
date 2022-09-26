#pragma once

#ifdef TOMATO_PLATFORM_WINDOWS

namespace Tomato
{
	class DirectXCodes
	{
	public:
		static void Setup();
		static int Cast(uint64_t directXCode);
		static uint64_t CastBack(int tomatoCode);
	private:
		static std::unordered_map<uint64_t, int> s_Data;
	};
}

#endif // TOMATO_PLATFORM_WINDOWS