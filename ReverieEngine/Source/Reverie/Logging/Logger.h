#pragma once
#include <spdlog/spdlog.h>
#include "Reverie/Log.h"
#include "../System.h"

namespace Reverie
{
	class Logger
	{
	public:
		Logger() = default;
		~Logger() = default;

		static void Initialize(Eventbus* eventbus);
		static void OnUpdate();
		static void Shutdown();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		template<typename TEvent>
		static void OnEvent(TEvent& e)
		{
			CORE_INFO(e.ToString());
		}
	private:
		inline static std::shared_ptr<spdlog::logger> s_ClientLogger;
		inline static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}
