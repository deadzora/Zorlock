#include "ZLpch.h"
#include "DX11Context.h"
#include <DX11Raz.h>

namespace Zorlock
{



	DX11Context::DX11Context(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		ZL_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void DX11Context::Init()
	{
		ZL_PROFILE_FUNCTION();

	}

	void DX11Context::SwapBuffers()
	{
	}


}
