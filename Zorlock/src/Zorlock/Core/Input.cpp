#include "ZLpch.h"
#include "Zorlock/Core/Input.h"
#include "Zorlock/Renderer/RendererAPI.h"
#ifdef ZL_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
	#include "Platform/Windows/WindowsNativeInput.h"
#endif

namespace Zorlock {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
	#ifdef ZL_PLATFORM_WINDOWS
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<WindowsInput>();
		case RendererAPI::API::DX11:	return CreateScope<WindowsNativeInput>();
		}
		
	#else
		ZL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
} 