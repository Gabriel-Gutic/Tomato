#include "pchTomato.h"
#include "MouseEvent.h"

#include "MouseCodes.h"


namespace Tomato
{
	const std::unordered_map<int, std::string> MouseButtonEvent::s_ButtonNames =
	{
		{ TOMATO_MOUSE_BUTTON_LEFT, "Left Button" },
		{ TOMATO_MOUSE_BUTTON_RIGHT, "Right Button" },
		{ TOMATO_MOUSE_BUTTON_MIDDLE, "Middle Button" },
	};

	std::string MouseButtonEvent::ToString() const
	{
		std::stringstream ss;
		ss << this->GetName() << ": ";
		if (s_ButtonNames.find(m_Button) == s_ButtonNames.end())
			ss << m_Button + 1;
		else ss << s_ButtonNames.at(m_Button);
		return ss.str();
	}

	std::string WheelEvent::ToString() const
	{
		std::stringstream ss;
		ss << this->GetName() << ": " << m_Value;
		return ss.str();
	}

	std::string MouseMoveEvent::ToString() const
	{
		std::stringstream ss;
		ss << this->GetName() << ": ("
			<< m_X << ", " << m_Y << ")";
		return ss.str();
	}
}