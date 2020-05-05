#include "ZLpch.h"
#include "Zorlock/Renderer/GraphicsContext.h"

#include "Zorlock/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Zorlock {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}