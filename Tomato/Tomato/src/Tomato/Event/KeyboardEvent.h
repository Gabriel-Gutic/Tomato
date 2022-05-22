#pragma once
#include "Event.h"


namespace Tomato
{
	class KeyboardEvent : public Event
	{
	public:
		KeyboardEvent(int key) :m_Key(key) {}

		int GetKey() const { return m_Key; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << this->GetName() << ": " << (char)m_Key;
			return ss.str();
		}
	protected:
		int m_Key;
	};

	class KeyPressEvent : public KeyboardEvent
	{
	public:
		KeyPressEvent(int key) :KeyboardEvent(key){}
		EVENT_SETUP(KeyPress);
	};

	class KeyReleaseEvent : public KeyboardEvent
	{
	public:
		KeyReleaseEvent(int key) :KeyboardEvent(key) {}
		EVENT_SETUP(KeyRelease);
	};

	class KeyRepeatEvent : public KeyboardEvent
	{
	public:
		KeyRepeatEvent(int key) :KeyboardEvent(key) {}
		EVENT_SETUP(KeyRepeat);
	};

	class CharEvent : public Event
	{
	public:
		CharEvent(int chr) :m_Char(chr){}
		EVENT_SETUP(Char);

		int GetChar() const { return m_Char; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << this->GetName() << ": " << (char)m_Char;
			return ss.str();
		}
	private:
		unsigned int m_Char;
	};
}
