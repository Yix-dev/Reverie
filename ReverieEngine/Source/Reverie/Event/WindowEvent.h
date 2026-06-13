#pragma once
#include "EventBase.h"

namespace Reverie
{
	class WindowResizeEvent : public EventBase
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) :m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			return fmt::format("WindowResizeEvent: {}, {}", m_Width, m_Height);
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryWindow | EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public EventBase
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryWindow | EventCategoryApplication)
	};

	class WindowFocusEvent : public EventBase
	{
	public:
		WindowFocusEvent() = default;
		EVENT_CLASS_TYPE(WindowFocus)
		EVENT_CLASS_CATEGORY(EventCategoryWindow | EventCategoryApplication)
	};

	class WindowLostFocusEvent : public EventBase
	{
	public:
		WindowLostFocusEvent() = default;
		EVENT_CLASS_TYPE(WindowLostFocus)
		EVENT_CLASS_CATEGORY(EventCategoryWindow | EventCategoryApplication)
	};
}
