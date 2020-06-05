#pragma once

#include "Zorlock/Renderer/VertexArray.h"
#include "DX11Shader.h"

namespace DX11Raz {
	class RazVertexBuffer;
}


namespace Zorlock {

	class DX11VertexArray : public VertexArray
	{
	public:
		DX11VertexArray();
		virtual ~DX11VertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		void DX11Bind();
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
		Ref<DX11Raz::RazVertexBuffer> GetVertexBuffer()
		{
			return m_RendererID;
		}
		DX11Shader* GetShader()
		{
			return dxvertexshader;
		}
	private:
		Ref<DX11Raz::RazVertexBuffer> m_RendererID;
		UINT m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		DX11Shader* dxvertexshader;
	};

}
