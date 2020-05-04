#pragma once

#include "Zorlock/Renderer/Buffer.h"
#include "Zorlock/Renderer/Shader.h"

namespace Zorlock {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	private:
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

	template <class T>
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		virtual ~OpenGLUniformBuffer() {}

		OpenGLUniformBuffer(std::string buffername, T * uniformblob, Shader * shader)
		{
			m_SceneData = uniformblob;
			uint32_t ptr = reinterpret_cast<uint32_t>(shader->m_RendererID);
			GLuint blockIndex = glGetUniformBlockIndex(ptr, buffername);
			GLuint uboHandle;
			glGenBuffers(1, &uboHandle);
			glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(T), m_SceneData,GL_DYNAMIC_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, uboHandle);

			//send to shader
			//glUniformBlockBinding(ptr, glGetUniformBlockIndex(ptr, buffername), 0);
		};

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;
	private:
		uint32_t m_RendererID;
		T* m_SceneData;
	};



}