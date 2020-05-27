#include "ZLpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <glfw3.h>
#include <glad/glad.h>

namespace Zorlock {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ZL_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		ZL_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ZL_CORE_ASSERT(status, "Failed to initialize Glad!");

		ZL_CORE_INFO("OpenGL Info:");
		ZL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		ZL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		ZL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	#ifdef ZL_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
		ZL_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Zorlock requires at least OpenGL version 4.5!");
	#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		ZL_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
