#include "ZLpch.h"
#include "DX11RendererAPI.h"
#include <DX11Raz.h>

void Zorlock::DX11RendererAPI::Init()
{
	DX11Raz::DX11GraphicsEngine::get();
}

void Zorlock::DX11RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
}

void Zorlock::DX11RendererAPI::SetClearColor(const glm::vec4& color)
{
}

void Zorlock::DX11RendererAPI::Clear()
{
}

void Zorlock::DX11RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
{
}
