#pragma once
#include <typeindex>

#include "Event.h"

namespace Reverie
{
	namespace Priority
	{
		constexpr int Highest = 1000;
		constexpr int High = 100;
		constexpr int Normal = 0;
		constexpr int Low = -100;
		constexpr int Lowest = -1000;

	};

	struct SubscriberEntry
	{
		uint32_t ID;
		std::function<bool(Event&)> Callback;
		int Priority;

		bool operator<(const SubscriberEntry& s) const
		{
			return Priority < s.Priority;
		}
		bool operator>(const SubscriberEntry& s) const
		{
			return Priority > s.Priority;
		}
		bool operator==(const SubscriberEntry& s) const
		{
			return Priority == s.Priority;
		}
	};

	struct SubscriberHandle
	{
		uint32_t ID = 0;
		std::type_index EventType;

		bool IsValid()
		{
			return ID != 0;
		}

	};

	class Eventbus
	{
	public:
		Eventbus() = default;
		~Eventbus() = default;

		Eventbus(const Eventbus& bus) = delete;
		Eventbus& operator=(const Eventbus& bus) = delete;

		template<typename TEvent>
		SubscriberHandle Subscribe(std::function<bool(TEvent&)> callback, int priority = Priority::Normal)
		{
			//TODO own assert
			static_assert(std::is_base_of_v<Event, TEvent>, "Invalid Event");

			uint32_t ID = m_NextID++;

			auto& wrapper = [callback](Event& e) -> bool
				{
					return callback(static_cast<TEvent&>(e));
				};

			auto& list = m_SubscriberList[typeid(TEvent)];
			list.emplace_back(ID, priority, std::move(wrapper));

			std::sort(list.begin(), list.end(), [](const SubscriberEntry& a, const SubscriberEntry& b)
			{
					return a > b;
			});
			return { ID, typeid(TEvent) };
		}

		void Unsubscribe(SubscriberHandle& handle)
		{
			if (!handle.IsValid())
				return;
			auto it = m_SubscriberList.find(handle.EventType);
			if (it == m_SubscriberList.end())
				return;
			auto& list = it->second;
			std::erase_if(list, [handle](const SubscriberEntry& s)
				{
					return s.ID == handle.ID;
				});

			handle.ID = 0;
		}

		template<typename TEvent>
		void Publish(TEvent& e)
		{
			//TODO own assert
			static_assert(std::is_base_of_v<Event, TEvent>, "Invalid Event");

			auto it = m_SubscriberList.find(typeid(e));
			if (it == m_SubscriberList.end())
				return;
			auto& list = it->second;
			for (auto& subscriber : list)
			{
				if (subscriber.Callback(e))
				{
					e.m_Handled = true;
					break;
				}
			}
		}
		template<typename TEvent>
		void Publish(TEvent&& e)
		{
			Publish(e);
		}

	private:
		std::unordered_map<std::type_index, std::vector<SubscriberEntry>> m_SubscriberList;
		uint32_t m_NextID = 1;

	};
}
