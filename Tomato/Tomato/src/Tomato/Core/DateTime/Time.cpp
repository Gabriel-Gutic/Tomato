#include "pchTomato.h"
#include "Time.h"


namespace Tomato
{
	Time::Time(int h, int min, int s)
		:Seconds(s),
		Minutes(min),
		Hours(h)
	{
	}

	Time Time::Now()
	{
		time_t now = time(0);

		tm* gmtm = gmtime(&now);

		return Time((gmtm->tm_hour + 3) % 24, gmtm->tm_min, gmtm->tm_sec);
	}

	std::string Time::ToString() const
	{
		char h[3], m[3], s[3];
		if (Hours < 10)
		{
			h[0] = '0';
			h[1] = '0' + Hours % 10;
		}
		else {
			h[0] = '0' + Hours / 10;
			h[1] = '0' + Hours % 10;
		}

		if (Minutes < 10)
		{
			m[0] = '0';
			m[1] = '0' + Minutes % 10;
		}
		else {
			m[0] = '0' + Minutes / 10;
			m[1] = '0' + Minutes % 10;
		}

		if (Seconds < 10)
		{
			s[0] = '0';
			s[1] = '0' + Seconds % 10;
		}
		else {
			s[0] = '0' + Seconds / 10;
			s[1] = '0' + Seconds % 10;
		}

		h[2] = m[2] = s[2] = 0;
		return std::format("{0}:{1}:{2}", h, m, s);
	}
}