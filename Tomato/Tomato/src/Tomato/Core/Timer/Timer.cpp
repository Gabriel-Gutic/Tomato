#include "pchTomato.h"
#include "Timer.h"


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

	ULong Timer::GetMicroseconds(UInt precision) const
	{
		Double seconds = GetSeconds(precision + 6);
		return ULong(seconds * 1000000);
	}

	Double Timer::GetMilliseconds(UInt precision) const
	{
		Double seconds = GetSeconds(precision + 3);
		return seconds * 1000;
	}

	Double Timer::GetSeconds(UInt precision) const
	{
		auto end = std::chrono::high_resolution_clock::now();

		std::chrono::duration<Double> duration = end - m_Start;

		Double power = std::pow(10, precision);
		return ULong(duration.count() * power) / power;
	}

	std::string Timer::MicrosecondsToString(UInt precision) const
	{
		return Math::ToString(GetMicroseconds(precision)) + (char)230 + "s";
	}

	std::string Timer::MillisecondsToString(UInt precision) const
	{
		return Math::ToString(GetMilliseconds(precision)) + "ms";
	}

	std::string Timer::SecondsToString(UInt precision) const
	{
		return Math::ToString(GetSeconds(precision)) + "s";
	}

}