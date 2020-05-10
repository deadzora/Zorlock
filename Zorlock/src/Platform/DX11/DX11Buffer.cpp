#include "ZLpch.h"
#include "DX11Buffer.h"
#include "DX11VBuffer.h"
#include "DX11IBuffer.h"
#include "DX11Vertex.h"
#include "DX11Raz.h"


namespace Zorlock
{
	DX11VertexBuffer::DX11VertexBuffer() : m_RendererID(0)
	{
	}
	DX11VertexBuffer::DX11VertexBuffer(uint32_t size) : m_RendererID(0)
	{
		//this function basically just checks the vector list 
		//for the index, if its below the size, then it resizes. 
		//so we pass -1 because the resize +1.
		uint32_t newsize = size - 1;
		m_RendererID = DX11Raz::RazCreateVertexBuffer();
		m_RendererID->SetVertices(newsize);
		ZL_PROFILE_FUNCTION();
	}

	DX11VertexBuffer::DX11VertexBuffer(float* vertices, uint32_t size)
	{
		m_RendererID = DX11Raz::RazCreateVertexBuffer();
		m_RendererID->SetVertices(vertices, size);
		ZL_PROFILE_FUNCTION();
	}

	DX11VertexBuffer::DX11VertexBuffer(void* vertices, uint32_t size)
	{
		//std::vector<DX11Raz::RazVertex>* v = static_cast<std::vector<DX11Raz::RazVertex>*>(vertices);
		m_RendererID = DX11Raz::RazCreateVertexBuffer();
		m_RendererID->SetVertices(vertices, size);
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
		m_RendererID->Release();

		ZL_PROFILE_FUNCTION();
	}

	void DX11VertexBuffer::Bind() const
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11VertexBuffer::Bind(void* buffer)
	{
		m_RendererID = static_cast<DX11Raz::RazVertexBuffer*>(buffer);
	}



	void DX11VertexBuffer::Unbind() const
	{
		
		ZL_PROFILE_FUNCTION();
	}

	void DX11VertexBuffer::SetData(const void* data, uint32_t size)
	{
		ZL_PROFILE_FUNCTION();
		//have no idea what the hell i'm gonna cast to. 
	}

	/////////////////////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////


	DX11IndexBuffer::DX11IndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
	{
		m_RendererID = DX11Raz::RazCreateIndexBuffer();
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
		ZL_PROFILE_FUNCTION();
	}

	void DX11IndexBuffer::Unbind() const
	{

		ZL_PROFILE_FUNCTION();
	}

}
