#include "ZLpch.h"
#include "DXRendererAPI.h"
#include "DX11Graphics.h"

namespace Zorlock {
	
	
	
	
	
	void DX11RendererAPI::SetClearColor(const ZColor color)
	{
		clsColor = color;
		ZorlockDX11::DX11GraphicsEngine::get()->Cls(color.r, color.g, color.b, color.a);
	}

	void DX11RendererAPI::Clear()
	{
		ZorlockDX11::DX11GraphicsEngine::get()->Cls(clsColor.r, clsColor.g, clsColor.b, clsColor.a);
	}

	void DX11RendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
	}

}