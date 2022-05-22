#include "pchTomato.h"
#include "DateTime.h"


namespace Tomato
{
	DateTime::DateTime()
		:date(Date()),
		time(Time())
	{
	}

	DateTime DateTime::Now()
	{
		auto dt = DateTime();
		dt.date = Date::Today();
		dt.time = Time::Now();
		return dt;
	}

	std::string DateTime::ToString() const
	{
		return std::format("{0} {1}", date.ToString(), time.ToString());
	}
}