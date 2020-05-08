#include "ZLpch.h"
#include "DX11Context.h"
#include <DX11DeviceContext.h>


namespace Zorlock
{
	

	DX11Context::DX11Context(DX11Raz::ZWindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		ZL_CORE_ASSERT(windowHandle, "Window handle is null!");
		//We have the Window!
	}

	void DX11Context::Init()
	{
		ZL_PROFILE_FUNCTION();
		DX11Raz::RazDX11CreateContext(m_WindowHandle);

	}

	void DX11Context::SwapBuffers()
	{
		m_WindowHandle->GetDeviceContext()->Flip(true);
		//No VSync?
		//DX11Raz::DX11GraphicsEngine::Get()->Flip(true);
	}


}
