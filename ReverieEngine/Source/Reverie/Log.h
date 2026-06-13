#pragma once
//Core Log macros
#define CORE_TRACE(...) ::Reverie::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...) ::Reverie::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...) ::Reverie::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...) ::Reverie::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) ::Reverie::Logger::GetCoreLogger()->critical(__VA_ARGS__)

//App Log macros
#define TRACE(...) ::Reverie::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define INFO(...) ::Reverie::Logger::GetClientLogger()->info(__VA_ARGS__)
#define WARN(...) ::Reverie::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define ERROR(...) ::Reverie::Logger::GetClientLogger()->error(__VA_ARGS__)
#define CRITICAL(...) ::Reverie::Logger::GetClientLogger()->critical(__VA_ARGS__)