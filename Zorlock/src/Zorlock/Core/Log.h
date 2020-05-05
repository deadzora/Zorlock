#pragma once

#include "Zorlock/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Zorlock {

	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define ZL_CORE_TRACE(...)    ::Zorlock::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZL_CORE_INFO(...)     ::Zorlock::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZL_CORE_WARN(...)     ::Zorlock::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZL_CORE_ERROR(...)    ::Zorlock::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZL_CORE_CRITICAL(...) ::Zorlock::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ZL_TRACE(...)         ::Zorlock::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZL_INFO(...)          ::Zorlock::Log::GetClientLogger()->info(__VA_ARGS__)
#define ZL_WARN(...)          ::Zorlock::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZL_ERROR(...)         ::Zorlock::Log::GetClientLogger()->error(__VA_ARGS__)
#define ZL_CRITICAL(...)      ::Zorlock::Log::GetClientLogger()->critical(__VA_ARGS__)