#include "ZLpch.h"
#include "Zorlock/Core/Window.h"
#include "Zorlock/Renderer/RendererAPI.h"
#ifdef ZL_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
	#include "Platform/Windows/WindowNative.h"
#endif

namespace Zorlock
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
	#ifdef ZL_PLATFORM_WINDOWS
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL:
		{
			return CreateScope<WindowsWindow>(props);
			break;
		}
		case RendererAPI::API::DX11:
		{
			return CreateScope<WindowsNative>(props);
			break;
		}
		}
		ZL_CORE_ASSERT(false, "Unknown Rendering platform!");
		return nullptr;
	#else
		ZL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}


