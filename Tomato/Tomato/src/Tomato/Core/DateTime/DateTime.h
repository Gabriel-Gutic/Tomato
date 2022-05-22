#pragma once
#include "Date.h"
#include "Time.h"


namespace Tomato
{
	struct DateTime
	{
		union {
			struct {
				Date date;
				Time time;
			};
			struct {
				int Day;
				int Month;
				int Year;
				int WeekDay;
				int YearDay;
				int Seconds;
				int Minutes;
				int Hours;
			};
		};

		DateTime();
		static DateTime Now();

		std::string ToString() const;
	};
}
