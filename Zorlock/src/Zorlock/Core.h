#pragma once

#ifdef ZL_PLATFORM_WINDOWS
	#ifdef ZL_BUILD_DLL
		#define ZORLOCK_API __declspec(dllexport)
	#else
		#define ZORLOCK_API __declspec(dllimport)
	#endif
#else
	#error Zorlock only supports Windows!
#endif

#ifdef ZL_ENABLE_ASSERTS
	#define ZL_ASSERT(x, ...) {if(!(x)){ZL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define ZL_CORE_ASSERT(x, ...) {if(!(x)){ZL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define ZL_ASSERT(x, ...)
	#define ZL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)