#pragma once
#include <memory>
#include "Zorlock/Renderer/Buffer.h"

namespace Zorlock {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}
		[[deprecated("Bind is now in Buffers")]]
		virtual void Bind() const = 0;
		[[deprecated("Unbind is now in Buffers")]]
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}