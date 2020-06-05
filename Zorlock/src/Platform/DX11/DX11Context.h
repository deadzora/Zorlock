#pragma once
#include "Zorlock/Renderer/GraphicsContext.h"
#include <DX11Raz.h>




namespace Zorlock {

	class DX11Context : public GraphicsContext
	{
	public:
		DX11Context(Ref<DX11Raz::ZWindow> windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		Ref<DX11Raz::ZWindow> m_WindowHandle;
	};

}