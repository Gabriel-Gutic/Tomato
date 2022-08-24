#include "pchTomato.h"
#include "Object.h"


namespace Tomato
{
	std::string Object::ToString() const
	{
		return "<Tomato::Object>";
	}

	std::ostream& operator<<(std::ostream& os, const Object& obj)
	{
		os << obj.ToString();
		return os;
	}
}


