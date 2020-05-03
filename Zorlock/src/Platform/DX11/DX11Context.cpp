#include "ZLpch.h"
#include "DX11Context.h"

namespace Zorlock
{
	Zorlock::DX11Context::DX11Context(ZorlockDX11::DirectX11Window* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ZL_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void Zorlock::DX11Context::Init()
	{
		//DX11 requires the WM_CREATE callback from windows to create context
		//For now Zorlock DX11 only supports 1 context. 
		//Context creation happens automatically, to get info from it we need to pass a callback.

		m_WindowHandle->SetContextCallback(this->DX11LoadDXLoader);

	}

	void Zorlock::DX11Context::SwapBuffers()
	{
	}

	bool DX11Context::DX11LoadDXLoader(int status)
	{
		if (!status)
		{
			ZL_CORE_ASSERT(status, "Failed to initialize Glad!");
			return false;
		}
		ZL_CORE_INFO("DX11 Info:");
		ZL_CORE_INFO(" Vendor: Zorlock DX11 Engine");
		ZL_CORE_INFO(" Vendor: Written by: Landon Ritchie");
		return true;
	}
}
