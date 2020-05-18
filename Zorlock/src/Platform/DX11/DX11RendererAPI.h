#pragma once
#include <D3d11sdklayers.h>
#include "Zorlock/Renderer/RendererAPI.h"

namespace Zorlock {

	class DX11RendererAPI : public RendererAPI
	{
	public:
		DX11RendererAPI();
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(const COLOR4& color) override;
		virtual void Clear() override;
		virtual void Release() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};

	//bool DX11MessageCallback(void* pInfoQueue);

}