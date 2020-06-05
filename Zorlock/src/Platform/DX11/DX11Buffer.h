#pragma once
#include "Zorlock/Renderer/Buffer.h"


namespace DX11Raz {
	class RazVertexBuffer;
	class RazIndexBuffer;
}

namespace Zorlock {

	class DX11VertexBuffer : public VertexBuffer
	{
	public:
		DX11VertexBuffer();
		DX11VertexBuffer(uint32_t size);
		DX11VertexBuffer(float* vertices, uint32_t size);
		DX11VertexBuffer(void * vertices, uint32_t size);
		DX11VertexBuffer(Vertex* vertices, uint32_t size);
		virtual ~DX11VertexBuffer();

		virtual void Bind() const override;
		virtual void Bind(void* buffer) override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, uint32_t size) override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override;
		virtual void SetLayout(const BufferLayout& layout, Shader * shader) override;
		virtual void ApplyLayout() const override;
		void SetStride(UINT stride);

	private:
		
		Ref<DX11Raz::RazVertexBuffer> m_RendererID;
		BufferLayout m_Layout;
	};

	class DX11IndexBuffer : public IndexBuffer
	{
	public:
		DX11IndexBuffer(uint32_t* indices, uint32_t count);
		DX11IndexBuffer(std::vector<DWORD> indices);
		virtual ~DX11IndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		Ref<DX11Raz::RazIndexBuffer> m_RendererID;
		UINT m_Count;
	};

}