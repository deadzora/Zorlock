#include "ZLpch.h"
#include "DX11Buffer.h"

namespace Zorlock
{


	DX11VertexBuffer::DX11VertexBuffer(uint32_t size)
	{
		ZL_PROFILE_FUNCTION();
	}

	DX11VertexBuffer::DX11VertexBuffer(float* vertices, uint32_t size)
	{
		ZL_PROFILE_FUNCTION();
	}

	DX11VertexBuffer::~DX11VertexBuffer()
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11VertexBuffer::Bind() const
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11VertexBuffer::Unbind() const
	{
		ZL_PROFILE_FUNCTION();
	}

	void DX11VertexBuffer::SetData(const void* data, uint32_t size)
	{
	}

	DX11IndexBuffer::DX11IndexBuffer(uint32_t* indices, uint32_t count)
	{
		ZL_PROFILE_FUNCTION();
	}

	DX11IndexBuffer::~DX11IndexBuffer()
	{
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
