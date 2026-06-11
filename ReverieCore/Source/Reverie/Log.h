#pragma once
//Core Log macros
#define CORE_TRACE(...) ::Reverie::LoggingSystem::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...) ::Reverie::LoggingSystem::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...) ::Reverie::LoggingSystem::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...) ::Reverie::LoggingSystem::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) ::Reverie::LoggingSystem::GetCoreLogger()->critical(__VA_ARGS__)