#pragma once


namespace Tomato
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		void start();

		ULong GetMicroseconds(UInt precision = 2) const;
		Double GetMilliseconds(UInt precision = 2) const;
		Double GetSeconds(UInt precision = 2) const;
		std::string MicrosecondsToString(UInt precision = 2) const;
		std::string MillisecondsToString(UInt precision = 2) const;
		std::string SecondsToString(UInt precision = 2) const;
		
		static void Wait(Double ms);
	private:
		Bool isStopped;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};
}

#define SLEEP(ms) Tomato::Timer::Wait(ms)
