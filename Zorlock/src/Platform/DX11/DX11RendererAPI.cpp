#include "ZLpch.h"
#include "DX11RendererAPI.h"
#include <DX11Raz.h>
#include <D3d11sdklayers.h>
namespace Zorlock
{
	void DX11MessageCallback(
		D3D11_MESSAGE_CATEGORY  type,
		D3D11_MESSAGE_SEVERITY  severity,
		D3D11_MESSAGE_ID        id,
		const char* message,
		SIZE_T length)
	{
		switch (severity)
		{
		case D3D11_MESSAGE_SEVERITY_ERROR:         ZL_CORE_CRITICAL(message); return;
		case D3D11_MESSAGE_SEVERITY_WARNING:       ZL_CORE_ERROR(message); return;
		case D3D11_MESSAGE_SEVERITY_INFO:          ZL_CORE_WARN(message); return;
		case D3D11_MESSAGE_SEVERITY_MESSAGE: ZL_CORE_TRACE(message); return;
		}

		ZL_CORE_ASSERT(false, "Unknown severity level!");
	}

	void DX11RendererAPI::Init()
	{

		DX11Raz::DX11GraphicsEngine::Get()->Initialize();

	}

	void DX11RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		//DX11Raz::DX11GraphicsEngine::Get()->SetViewport(0, 0, 1280, 720);
	}

	void DX11RendererAPI::SetClearColor(const glm::vec4& color)
	{
		//DX11Raz::DX11GraphicsEngine::Get()->Cls(color.r, color.g, color.b, color.a);
	}

	void DX11RendererAPI::Clear()
	{
		//DX11Raz::DX11GraphicsEngine::Get()->Cls();
	}

	void DX11RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		//not yet
	}

}
