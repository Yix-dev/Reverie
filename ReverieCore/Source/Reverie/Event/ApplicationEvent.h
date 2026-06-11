#pragma once

#include "EventBase.h"

namespace Reverie
{

	class AppTickEvent : public EventBase
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public EventBase
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : public EventBase
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppPauseEvent : public EventBase 
	{
	public:
		AppPauseEvent() = default;
		EVENT_CLASS_TYPE(AppPause)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppResumeEvent : public EventBase 
	{
	public:
		AppResumeEvent() = default;
		EVENT_CLASS_TYPE(AppResume)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	
}
