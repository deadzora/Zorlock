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