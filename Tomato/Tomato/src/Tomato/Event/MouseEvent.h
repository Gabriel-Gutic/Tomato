#pragma once
#include "Event.h"


namespace Tomato
{
	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button) :m_Button(button){}

		int GetButton() const { return m_Button; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << this->GetName() << ": " << m_Button;
			return ss.str();
		}
	protected:
		int m_Button;
	};

	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(int button)
			:MouseButtonEvent(button){}

		EVENT_SETUP(MouseButtonPress);
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(int button)
			:MouseButtonEvent(button) {}

		EVENT_SETUP(MouseButtonRelease);
	};

	class WheelEvent : public Event
	{
	public:
		WheelEvent(int value) :m_Value(value){}

		EVENT_SETUP(Wheel);
		int GetValue() const { return m_Value; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << this->GetName() << ": " << m_Value;
			return ss.str();
		}
	private:
		int m_Value;
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(double x, double y) :m_X(x), m_Y(y){}

		EVENT_SETUP(MouseMove);
		double GetX() const { return m_X; }
		double GetY() const { return m_Y; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << this->GetName() << ": (" 
				<< m_X << ", " << m_Y << ")";
			return ss.str();
		}
	private:
		double m_X, m_Y;
	};
}
