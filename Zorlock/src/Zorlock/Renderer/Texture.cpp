#include "ZLpch.h"
#include "Zorlock/Renderer/Texture.h"

#include "Zorlock/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Platform/DX11/DX11Texture.h"

namespace Zorlock {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height);
			case RendererAPI::API::DX11:	return CreateRef<DX11Texture2D>(width, height);
		}

		ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, uint32_t color)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height, color);
		case RendererAPI::API::DX11:	return CreateRef<DX11Texture2D>(width, height, color);
		}

		ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, uint32_t color, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height, color, size);
		case RendererAPI::API::DX11:	return CreateRef<DX11Texture2D>(width, height, color, size);
		}

		ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    ZL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
			case RendererAPI::API::DX11:	return CreateRef<DX11Texture2D>(path);
		}

		ZL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}