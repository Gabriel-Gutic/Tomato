#pragma once
#include "spdlog/spdlog.h"


namespace Tomato
{
	class Logger
	{
		Logger(){}
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger> GetCore();
		static std::shared_ptr<spdlog::logger> GetClient();
	private:
		static std::shared_ptr<spdlog::logger> s_Core;
		static std::shared_ptr<spdlog::logger> s_Client;
	};
}
