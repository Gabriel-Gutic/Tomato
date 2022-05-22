#pragma once
#include "Event.h"

namespace Tomato
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(){}

		EVENT_SETUP(WindowClose);

		virtual std::string ToString() const override
		{
			return this->GetName();
		}
	};

	class WindowMinimizeEvent : public Event
	{
	public:
		WindowMinimizeEvent(bool isMinimized): isMinimized(isMinimized) {}

		EVENT_SETUP(WindowMinimize);

		bool IsMinimized() const { return isMinimized; }

		virtual std::string ToString() const override
		{
			const char* c;
			if (isMinimized)
				c = "True";
			else c = "False";
			std::stringstream ss;
			ss << this->GetName() << ": " << c;
			return ss.str();
		}
	private:
		bool isMinimized;
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		WindowMaximizeEvent(bool isMaximized):isMaximized(isMaximized) {}

		EVENT_SETUP(WindowMaximize);

		bool IsMaximized() const { return isMaximized; }

		virtual std::string ToString() const override
		{
			const char* c;
			if (isMaximized)
				c = "True";
			else c = "False";
			std::stringstream ss;
			ss << this->GetName() << ": " << c;
			return ss.str();
		}
	private:
		bool isMaximized;
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
		:m_Width(width), m_Height(height) {}

		EVENT_SETUP(WindowResize);

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << this->GetName() << ": "
				<< "(" << m_Width << ", " << m_Height << ")";
			return ss.str();
		}
	private:
		int m_Width, m_Height;
	};
}
