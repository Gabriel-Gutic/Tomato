#include "pchTomato.h"
#include "Date.h"


namespace Tomato
{
	Date::Date(int d, int m, int y, int wd, int yd)
		:Day(d),
		Month(m),
		Year(y),
		WeekDay(wd),
		YearDay(yd)
	{
	}

	Date Date::Today()
	{
		time_t now = time(0);

		tm* gmtm = gmtime(&now);

		return Date(
			gmtm->tm_mday + 1,
			gmtm->tm_mon + 1,
			gmtm->tm_year + 1900,
			gmtm->tm_wday + 1,
			gmtm->tm_yday + 1
		);
	}

	std::string Date::ToString() const
	{
		char  m[3];
		if (Month < 10)
		{
			m[0] = '0';
			m[1] = '0' + Month % 10;
		}
		else {
			m[0] = '0' + Month / 10;
			m[1] = '0' + Month % 10;
		}
		m[2] = 0;
		
		const char* days[7] = { "Sunday", 
			"Monday", "Tuesday",
			"Wednesday", "Thursday", 
			"Friday", "Saturday"
		};

		return std::format("{0} {1}.{2}.{3}", days[WeekDay - 1], Day, m, Year);
	}
}