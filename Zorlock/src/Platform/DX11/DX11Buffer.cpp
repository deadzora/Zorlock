#include "ZLpch.h"
#include "DX11Buffer.h"
#include "DX11VBuffer.h"
#include "DX11IBuffer.h"
#include "DX11Vertex.h"
#include "DX11Raz.h"
#include "DX11Shaders.h"
#include <DX11DeviceContext.h>

namespace Zorlock
{
	DX11VertexBuffer::DX11VertexBuffer() : m_RendererID(0)
	{
		m_RendererID = DX11Raz::RazCreateVertexBuffer();
	}
	DX11VertexBuffer::DX11VertexBuffer(uint32_t size) : m_RendererID(0)
	{
		//this function basically just checks the vector list 
		//for the index, if its below the size, then it resizes. 
		//so we pass -1 because the resize +1.
		ZL_PROFILE_FUNCTION();
		m_RendererID = DX11Raz::RazCreateVertexBuffer();
		DX11Raz::RazSetCurrentVertexBuffer(m_RendererID);
		DX11Raz::RazBindVertices(size);


	}

	DX11VertexBuffer::DX11VertexBuffer(float* vertices, uint32_t size)
	{
		ZL_PROFILE_FUNCTION();
		m_RendererID = DX11Raz::RazCreateVertexBuffer();
		DX11Raz::RazBindVertices(m_RendererID, vertices, size);

	}

	DX11VertexBuffer::DX11VertexBuffer(void* vertices, uint32_t size)
	{
		ZL_PROFILE_FUNCTION();
		m_RendererID = DX11Raz::RazCreateVertexBuffer();
		DX11Raz::RazBindVertices(m_RendererID,vertices, size);

	}
	/*
	DX11VertexBuffer::DX11VertexBuffer(void* vertices)
	{
		std::vector<DX11Raz::RazVertex>* v = static_cast<std::vector<DX11Raz::RazVertex>*>(vertices);
		m_RendererID->SetVertices(*v);
	}
	*/


	DX11VertexBuffer::~DX11VertexBuffer()
	{
		ZL_PROFILE_FUNCTION();
		RazDeleteVertexBuffer(m_RendererID);

	}

	void DX11VertexBuffer::Bind() const
	{
		ZL_PROFILE_FUNCTION();
		DX11Raz::RazSetCurrentVertexBuffer(m_RendererID);

	}

	void DX11VertexBuffer::Bind(void* buffer)
	{
		ZL_PROFILE_FUNCTION();
		//m_RendererID = static_cast<DX11Raz::RazVertexBuffer*>(buffer);
		DX11Raz::RazSetCurrentVertexBuffer(m_RendererID);
		
	}

	void DX11VertexBuffer::Unbind() const
	{
		ZL_PROFILE_FUNCTION();
		DX11Raz::RazSetCurrentVertexBuffer(0);

	}

	void DX11VertexBuffer::SetData(const void* data, uint32_t size)
	{
		ZL_PROFILE_FUNCTION();
		void* a = const_cast<void*>(data);
		DX11Raz::RazBindVertices(m_RendererID, a, size);
	}

	void DX11VertexBuffer::SetLayout(const BufferLayout& layout)
	{
		ZL_PROFILE_FUNCTION();
		m_Layout = layout; 
		DX11Raz::RazSetLayout(m_RendererID);

	}

	void DX11VertexBuffer::SetLayout(const BufferLayout& layout, Shader* shader)
	{
		ZL_PROFILE_FUNCTION();
		m_Layout = layout;
		vertexshader = shader;

	}

	void DX11VertexBuffer::ApplyLayout() const
	{
		ZL_PROFILE_FUNCTION();
		if (m_RendererID != 0)
		{
			DX11Raz::RazSetLayout(m_RendererID);
		}
		
	}

	void DX11VertexBuffer::SetStride(UINT stride)
	{
		m_RendererID->SetStride(stride);
	}

	/////////////////////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////


	DX11IndexBuffer::DX11IndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
	{
		m_RendererID = DX11Raz::RazCreateIndexBuffer();
		DX11Raz::RazSetCurrentIndexBuffer(m_RendererID);

		m_RendererID->SetIndexes(indices,count);
		ZL_PROFILE_FUNCTION();
	}

	DX11IndexBuffer::DX11IndexBuffer(std::vector<DWORD> indices)
	{
		m_RendererID = DX11Raz::RazCreateIndexBuffer();
	}

	DX11IndexBuffer::~DX11IndexBuffer()
	{
		m_RendererID->Release();
		ZL_PROFILE_FUNCTION();
	}

	void DX11IndexBuffer::Bind() const
	{
		DX11Raz::RazSetCurrentIndexBuffer(m_RendererID);
		
		ZL_PROFILE_FUNCTION();
	}

	void DX11IndexBuffer::Unbind() const
	{

		ZL_PROFILE_FUNCTION();
	}

}
