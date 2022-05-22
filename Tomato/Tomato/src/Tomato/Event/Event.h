#pragma once


namespace Tomato
{
	enum class EventType
	{
		KeyPress, KeyRelease, KeyRepeat, Char,
		MouseButtonPress, MouseButtonRelease, Wheel, MouseMove,
		WindowClose, WindowMinimize, WindowMaximize, WindowResize
	};

	class Event
	{
	public:
		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const = 0;

		template<typename E>
		static E Cast(Event& e);
	};

#define	EVENT_SETUP(type) \
	virtual EventType GetType() const override { return EventType::type; } \
	virtual const char* GetName() const override { return #type; } 
	
	template<typename E>
	inline E Event::Cast(Event& e)
	{
		return *dynamic_cast<E*>(&e);
	}
}
