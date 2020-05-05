#include "ZLpch.h"
#include "Zorlock/Core/Window.h"

#ifdef ZL_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Zorlock
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
	#ifdef ZL_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
	#else
		ZL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}