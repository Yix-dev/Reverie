#pragma once
#include "Event.h"
namespace Reverie
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keyCode) :m_KeyCode(keyCode){}
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount):KeyEvent(keyCode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() { return m_RepeatCount; }

		std::string ToString() const override
		{
			return spdlog::fmt_lib::format("KeyPressedEvent: {} ({} repeats)", m_KeyCode, m_RepeatCount);
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode) :KeyEvent(keyCode) {}

		std::string ToString() const override
		{
			return fmt::format("KeyReleasedEvent: {}", m_KeyCode);
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
