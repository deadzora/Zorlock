#pragma once

#include "Zorlock/Renderer/Buffer.h"

namespace Zorlock {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(void* vertices, uint32_t size);
		OpenGLVertexBuffer(Vertex* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Bind(void* i) override;
		virtual void Unbind() const override;
		
		virtual void SetData(const void* data, uint32_t size) override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual void SetLayout(const BufferLayout& layout,  Shader * shader) override
		{
			m_Layout = layout;
			vertexshader = shader;
		}
		virtual void ApplyLayout() const override
		{

		};
	private:
		Shader * vertexshader;
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}