#include "ZLpch.h"
#include "DX11Context.h"
#include <DX11DeviceContext.h>


namespace Zorlock
{
	

	DX11Context::DX11Context(DX11Raz::ZWindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		ZL_CORE_ASSERT(windowHandle, "Window handle is null!");

	}

	void DX11Context::Init()
	{
		ZL_PROFILE_FUNCTION();
		DX11Raz::RazDX11CreateContext(m_WindowHandle);

	}

	void DX11Context::SwapBuffers()
	{
		if (m_WindowHandle->GetDeviceContext() != nullptr)
		{
			DX11Raz::RazSetCurrentContext(m_WindowHandle->GetDeviceContext());
			DX11Raz::RazFlip(true);
		}
	}


}
