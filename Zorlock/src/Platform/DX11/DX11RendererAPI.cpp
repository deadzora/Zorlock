#include "ZLpch.h"
#include "DX11RendererAPI.h"
#include <DX11Raz.h>
#include <DX11Shaders.h>
#include <DX11DeviceContext.h>
#include <D3d11sdklayers.h>
#include "Zorlock/Core/Application.h"
#include "Platform/Windows/WindowNative.h"
#include "DX11VertexArray.h"
namespace Zorlock
{
	DX11RendererAPI::DX11RendererAPI()
	{
		DX11Raz::RazDX11Initialize();
	}

	void DX11RendererAPI::Init()
	{
		
	}

	void DX11RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{

		DX11Raz::RazSetViewport( width, height);
	}

	void DX11RendererAPI::SetClearColor(const COLOR4& color)
	{
		DX11Raz::RazSetCLSColor(DX11Raz::RazGetCurrentContext(), color.x, color.y, color.z, color.w);
	}

	void DX11RendererAPI::Clear()
	{
		DX11Raz::RazCLS(DX11Raz::RazGetCurrentContext());
	}

	void DX11RendererAPI::Release()
	{
		DX11Raz::RazDX11Release();
	}

	void DX11RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{	

		DX11VertexArray * dxvertexarray = static_cast<DX11VertexArray*>(vertexArray.get());
		DX11Raz::RazSetCurrentShader(dxvertexarray->GetShader()->GetShader());
		DX11Raz::RazApplyVertexShaderConstants();
		DX11Raz::RazApplyPixelShaderConstants();
		DX11Raz::RazApplyShader();

		DX11Raz::RazSetBlendState();
		vertexArray->Bind();
		DX11Raz::RazApplyVertexBuffer();
		vertexArray->GetIndexBuffer()->Bind();
		DX11Raz::RazBindIndexBuffer();

		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		DX11Raz::RazDrawIndexed(count, 0, 0);
	}

}
