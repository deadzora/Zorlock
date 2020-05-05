#include "ZLpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/DX11/DX11Buffer.h"

namespace Zorlock {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
		case RendererAPI::API::DX11: return new DX11VertexBuffer(vertices, size);
		}

		ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(indices, size);
		case RendererAPI::API::DX11: return new DX11IndexBuffer(indices, size);
		}

		ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}



}