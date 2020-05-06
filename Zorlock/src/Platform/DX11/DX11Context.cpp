#include "ZLpch.h"
#include "DX11Context.h"
#include <DX11Raz.h>
#include <glfw3.h>
#include <glfw3native.h>

namespace Zorlock
{



	DX11Context::DX11Context(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		ZL_CORE_ASSERT(windowHandle, "Window handle is null!");

	}

	void DX11Context::Init()
	{
		ZL_PROFILE_FUNCTION();
		RECT rc;
		
		GetClientRect(glfwGetWin32Window(m_WindowHandle), &rc);
		DX11Raz::DX11GraphicsEngine::Get()->SetContext(glfwGetWin32Window(m_WindowHandle));

	}

	void DX11Context::SwapBuffers()
	{
		//No VSync?
		DX11Raz::DX11GraphicsEngine::Get()->Flip(true);
	}


}
