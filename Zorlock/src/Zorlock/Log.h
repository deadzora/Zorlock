#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Zorlock
{
	class ZORLOCK_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core Log Macros
#define ZL_CORE_TRACE(...) ::Zorlock::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZL_CORE_INFO(...)  ::Zorlock::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZL_CORE_WARN(...)  ::Zorlock::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZL_CORE_ERROR(...) ::Zorlock::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZL_CORE_FATAL(...) ::Zorlock::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define ZL_TRACE(...) ::Zorlock::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZL_INFO(...)  ::Zorlock::Log::GetClientLogger()->info(__VA_ARGS__)
#define ZL_WARN(...)  ::Zorlock::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZL_ERROR(...) ::Zorlock::Log::GetClientLogger()->error(__VA_ARGS__)
#define ZL_FATAL(...) ::Zorlock::Log::GetClientLogger()->fatal(__VA_ARGS__)