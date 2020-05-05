#include "ZLpch.h"
#include "Zorlock/Core/Input.h"

#ifdef ZL_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Zorlock {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
	#ifdef ZL_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
	#else
		ZL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
} 