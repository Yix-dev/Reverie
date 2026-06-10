#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/format.h>

#include "Reverie/Utility.h"


namespace Reverie
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender, AppPause, AppResume,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
		EventCategoryWindow = BIT(5)

	};

#define EVENT_CLASS_TYPE(Type) static EventType GetStaticType() {return EventType::##Type;}\
							   virtual EventType GetEventType() const override {return GetStaticType();}\
							   virtual const char* GetName() const override{return #Type;}
#define EVENT_CLASS_CATEGORY(Category) virtual int GetCategoryFlags() const override{return Category;}


	class Event
	{
	public:
		virtual ~Event() = default;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

		bool m_Handled = false;
		
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
