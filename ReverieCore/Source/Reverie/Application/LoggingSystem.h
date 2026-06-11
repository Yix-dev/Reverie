#pragma once
#include <spdlog/spdlog.h>
#include "Reverie/Log.h"
#include "System.h"

namespace Reverie
{
	class LoggingSystem : public System
	{
	public:
		LoggingSystem() : System(){}
		~LoggingSystem() override;

		void Initialize(Eventbus* eventbus) override;
		void OnUpdate() override;
		void Shutdown() override;

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		template<typename TEvent>
		void OnEvent(TEvent& e)
		{
			CORE_INFO(e.ToString());
		}
	private:
		inline static std::shared_ptr<spdlog::logger> s_ClientLogger;
		inline static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}
