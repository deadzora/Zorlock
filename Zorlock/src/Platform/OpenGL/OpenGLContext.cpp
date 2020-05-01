#include "ZLpch.h"
#include "OpenGLContext.h"

#include <glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Zorlock
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ZL_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ZL_CORE_ASSERT(status, "Failed to initialize Glad!");
		ZL_CORE_INFO("OpenGL Info:");
		ZL_CORE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		ZL_CORE_INFO(" Vendor: {0}", glGetString(GL_RENDERER));
		ZL_CORE_INFO(" Vendor: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}


}