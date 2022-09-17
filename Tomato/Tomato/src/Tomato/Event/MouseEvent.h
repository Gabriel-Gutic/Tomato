#pragma once
#include "Event.h"


namespace Tomato
{
	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button) :m_Button(button){}

		int GetButton() const { return m_Button; }

		virtual std::string ToString() const override;
	protected:
		int m_Button;
	private:
		static const std::unordered_map<int, std::string> s_ButtonNames;
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
		WheelEvent(float value) :m_Value(value){}

		EVENT_SETUP(Wheel);
		float GetValue() const { return m_Value; }

		virtual std::string ToString() const override;
	private:
		float m_Value;
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y) :m_X(x), m_Y(y){}

		EVENT_SETUP(MouseMove);
		float GetX() const { return m_X; }
		float GetY() const { return m_Y; }

		virtual std::string ToString() const override;
	private:
		float m_X, m_Y;
	};
}
