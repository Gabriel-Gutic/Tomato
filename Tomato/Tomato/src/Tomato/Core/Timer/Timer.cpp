#include "pchTomato.h"
#include "Timer.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


namespace Tomato
{
	Timer::Timer()
		:isStopped(false)
	{
		this->start();
	}

	Timer::~Timer()
	{
	}

	void Timer::start()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	void Timer::Wait(unsigned long long ms)
	{
		Sleep(static_cast<unsigned long>(ms));
	}

	unsigned long long Timer::GetMicroseconds() const
	{
		double seconds = GetSeconds(6);
		return (unsigned long long)(seconds * 1000000);
	}

	double Timer::GetMilliseconds(unsigned int precision) const
	{
		double seconds = GetSeconds(precision + 3);
		return seconds * 1000;
	}

	double Timer::GetSeconds(unsigned int precision) const
	{
		auto end = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> duration = end - m_Start;

		double power = std::pow(10, precision);
		return (duration.count() * power) / power;
	}

	std::string Timer::MicrosecondsToString() const
	{
		return Math::ToString(GetMicroseconds()) + (char)230 + "s";
	}

	std::string Timer::MillisecondsToString(unsigned int precision) const
	{
		return Math::ToString(GetMilliseconds(precision)) + "ms";
	}

	std::string Timer::SecondsToString(unsigned int precision) const
	{
		return Math::ToString(GetSeconds(precision)) + "s";
	}
}