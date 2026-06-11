#include "pch.h"
#include "LoggingSystem.h"

#include "Reverie/Event/Event.h"
#include "Reverie/Event/Eventbus.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Reverie
{
	LoggingSystem::~LoggingSystem()
	{
	}

	void LoggingSystem::Initialize(Eventbus* eventbus)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stderr_color_mt("Core");
		s_CoreLogger->set_level(spdlog::level::trace);

		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_ClientLogger = spdlog::stderr_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::trace);

		eventbus->Subscribe<WindowCloseEvent>(
			[this](WindowCloseEvent& e) { OnEvent(e); return false; },
			Priority::Lowest   // log last, never consume
		);
		eventbus->Subscribe<WindowResizeEvent>(
			[this](WindowResizeEvent& e) { OnEvent(e); return false; },
			Priority::Lowest
		);
		eventbus->Subscribe<KeyPressedEvent>(
			[this](KeyPressedEvent& e) { OnEvent(e); return false; },
			Priority::Lowest
		);

	}


	void LoggingSystem::OnUpdate()
	{
	}

	void LoggingSystem::Shutdown()
	{
	}
}
