#pragma once
#include <DirectX11Buffer.h>
#include "Zorlock/Renderer/Buffer.h"

namespace Zorlock {

	class DX11VertexBuffer : public VertexBuffer
	{
	public:
		DX11VertexBuffer(float* vertices, uint32_t size);
		virtual ~DX11VertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
		ZorlockDX11::DirectX11Buffer* m_vertexbuffer;
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class DX11IndexBuffer : public IndexBuffer
	{
	public:
		DX11IndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~DX11IndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		ZorlockDX11::DirectX11Buffer* m_indexbuffer;
		uint32_t m_RendererID;
		uint32_t m_Count;
	};



};