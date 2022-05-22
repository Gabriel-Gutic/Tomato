#pragma once


namespace Tomato
{
	struct Time
	{
		int Seconds;
		int Minutes;
		int Hours;

		Time(int h = 0, int min = 0, int s = 0);
		static Time Now();

		std::string ToString() const;
	};
}
