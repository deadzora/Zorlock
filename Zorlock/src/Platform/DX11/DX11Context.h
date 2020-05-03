#pragma once

#include "Zorlock/Renderer/GraphicsContext.h"
#include <DirectX11Window.h>

namespace Zorlock {

	class DX11Context : public GraphicsContext
	{
	public:
		DX11Context(ZorlockDX11::DirectX11Window* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		bool DX11LoadDXLoader(int status);
		ZorlockDX11::DirectX11Window* m_WindowHandle;
		
	};
}

