#pragma once


namespace Tomato
{
	struct Date
	{
		int Day;
		int Month;
		int Year;
		int WeekDay;
		int YearDay;

		Date(int d = 1, int m = 1, int y = 0, int wd = 1, int yd = 1);
		static Date Today();

		std::string ToString() const;
	};
}
