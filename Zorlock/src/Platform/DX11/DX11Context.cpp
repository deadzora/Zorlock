#include "ZLpch.h"
#include "DX11Context.h"
#include "DX11Graphics.h"


namespace Zorlock
{
	


	DX11Context::DX11Context(ZorlockDX11::DirectX11Window* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ZL_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void DX11Context::Init()
	{
		//DX11 requires the WM_CREATE callback from windows to create context
		//For now Zorlock DX11 only supports 1 context. 
		//Context creation happens automatically, to get info from it we need to pass a callback.
		//ContextCallback p = this->DX11LoadDXLoader;
		//m_WindowHandle->SetContextCallback(p); //this->DX11LoadDXLoader);

	}

	void DX11Context::SwapBuffers()
	{
		//graphics engine flip swap chain
	}

}
