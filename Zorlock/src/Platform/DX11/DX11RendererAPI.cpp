#include "ZLpch.h"
#include "DX11RendererAPI.h"
#include <DX11Raz.h>
#include <D3d11sdklayers.h>
#include "Zorlock/Core/Application.h"
#include "Platform/Windows/WindowNative.h"
namespace Zorlock
{
	DX11RendererAPI::DX11RendererAPI()
	{
		DX11Raz::RazDX11Initialize();
	}
	/*
	bool DX11MessageCallback(void* p)
	{
		ID3D11InfoQueue* pInfoQueue = PID3D11InfoQueue(p);
		SIZE_T messageLength = 0;
		HRESULT hr = pInfoQueue->GetMessage(0, NULL, &messageLength);
		D3D11_MESSAGE* pMessage = (D3D11_MESSAGE*)malloc(messageLength);
		hr = pInfoQueue->GetMessage(0, pMessage, &messageLength);
		switch (pMessage->Severity)
		{
		case D3D11_MESSAGE_SEVERITY::D3D11_MESSAGE_SEVERITY_ERROR:         ZL_CORE_CRITICAL(pMessage); return true;
		case D3D11_MESSAGE_SEVERITY::D3D11_MESSAGE_SEVERITY_WARNING:       ZL_CORE_ERROR(pMessage); return false;
		case D3D11_MESSAGE_SEVERITY::D3D11_MESSAGE_SEVERITY_INFO:          ZL_CORE_WARN(pMessage); return false;
		case D3D11_MESSAGE_SEVERITY::D3D11_MESSAGE_SEVERITY_MESSAGE: ZL_CORE_TRACE(pMessage); return true;
		}

		
		return true;
	}
	*/
	void DX11RendererAPI::Init()
	{
		
	}

	void DX11RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{

		DX11Raz::RazSetViewport( width, height);
	}

	void DX11RendererAPI::SetClearColor(const glm::vec4& color)
	{
		Window& win = Application::Get().GetWindow();
		//Need to make all this shit a macro

		WindowsNative* whandle = static_cast<WindowsNative*>(&win);
		DX11Raz::ZWindow* zhandle = static_cast<DX11Raz::ZWindow*>(whandle->GetNativeWindow());

		DX11Raz::RazSetCLSColor(zhandle->GetDeviceContext(), color.r, color.g, color.b, color.a);
	}

	void DX11RendererAPI::Clear()
	{
		Window& win = Application::Get().GetWindow();
		//Need to make all this shit a macro

		WindowsNative* whandle = static_cast<WindowsNative*>(&win);
		DX11Raz::ZWindow* zhandle = static_cast<DX11Raz::ZWindow*>(whandle->GetNativeWindow());

		DX11Raz::RazCLS(zhandle->GetDeviceContext());
	}

	void DX11RendererAPI::Release()
	{
		DX11Raz::RazDX11Release();
	}

	void DX11RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		//not yet
	}

}
