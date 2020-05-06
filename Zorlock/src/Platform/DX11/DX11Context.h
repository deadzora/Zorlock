#pragma once

#include "Zorlock/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Zorlock {

	class DX11Context : public GraphicsContext
	{
	public:
		DX11Context(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}