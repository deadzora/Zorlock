#pragma once

#include "Zorlock/Renderer/VertexArray.h"


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

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		DX11Raz::RazVertexBuffer* m_RendererID;
		UINT m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}
