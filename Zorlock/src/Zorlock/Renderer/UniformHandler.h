#pragma once
#include "Zorlock/Core.h"
#include "Zorlock/Renderer/RendererAPI.h"
#include "Zorlock/Renderer/UniformBuffer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"
#include "Platform/DX11/DX11UniformBuffer.h"
#include <string>

namespace Zorlock
{



	template <class A, class T>
	static UniformBuffer<A>* CreateUniformBuffer(std::string buffername, T* uniformblob, unsigned int index)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new UniformBuffer<A>(buffername, uniformblob, index);
		case RendererAPI::API::DX11:	return new UniformBuffer<A>(buffername, uniformblob, index);
		}

		ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	};

}