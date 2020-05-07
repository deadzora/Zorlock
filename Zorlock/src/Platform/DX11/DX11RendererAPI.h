#pragma once
#include <D3d11sdklayers.h>
#include "Zorlock/Renderer/RendererAPI.h"

namespace Zorlock {

	class DX11RendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};


	void DX11MessageCallback(D3D11_MESSAGE_CATEGORY type, D3D11_MESSAGE_SEVERITY severity, D3D11_MESSAGE_ID id, const char* message, SIZE_T length);

}