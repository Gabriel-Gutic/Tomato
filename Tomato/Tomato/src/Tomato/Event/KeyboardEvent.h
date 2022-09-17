#pragma once
#include "Event.h"


namespace Tomato
{
	class KeyboardEvent : public Event
	{
	public:
		struct Code
		{
		public:
			int Value;

			Code(int value);

			friend bool operator==(const Code& code, int scancode);
			friend bool operator==(int scancode, const Code& code);
			friend bool operator!=(const Code& code, int scancode);
			friend bool operator!=(int scancode, const Code& code);
		};
	public:
		KeyboardEvent(int key) :m_Key(key) {}

		Code GetKey() const { return m_Key; }

		virtual std::string ToString() const override;
	protected:
		Code m_Key;
	private:
		static std::unordered_map<int, std::string> s_KeyNames;
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

		virtual std::string ToString() const override;
	private:
		unsigned int m_Char;
	};
}
