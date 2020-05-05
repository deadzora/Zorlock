#include "ZLpch.h"
#include "Zorlock/Renderer/VertexArray.h"

#include "Zorlock/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Zorlock {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}