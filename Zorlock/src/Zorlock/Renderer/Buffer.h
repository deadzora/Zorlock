#pragma once
#include "Shader.h"

namespace Zorlock {

	

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Bind(void * i) = 0;
		virtual void Unbind() const = 0;
		virtual void SetData(const void* data, uint32_t size) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual void SetLayout(const BufferLayout& layout,  Shader * shader) = 0;
		virtual void ApplyLayout() const = 0;
		virtual Shader* GetShader() {
			return vertexshader;
		};
		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
		static Ref<VertexBuffer> Create(Vertex* vertices, uint32_t size);
		static Ref<VertexBuffer> Create(void* vertices, uint32_t size);
	protected:
		Shader* vertexshader;
	};

	// Currently Zorlock only supports 32-bit index buffers
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};

}