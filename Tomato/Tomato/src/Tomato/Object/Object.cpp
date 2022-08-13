#include "pchTomato.h"
#include "Object.h"


namespace Tomato
{
	Object::Object(std::string_view name)
		:m_Name(name)
	{
	}

	void Object::SetName(std::string_view name)
	{
		m_Name = name;
	}

	const std::string& Object::GetName() const
	{
		return m_Name;
	}


}

