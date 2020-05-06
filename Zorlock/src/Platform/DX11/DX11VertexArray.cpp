#include "ZLpch.h"
#include "DX11VertexArray.h"
#include <d3d11.h>


namespace Zorlock
{

	static DXGI_FORMAT ShaderDataTypeToOpenDXBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Zorlock::ShaderDataType::Float:    return DXGI_FORMAT_R32_FLOAT;
		case Zorlock::ShaderDataType::Float2:   return DXGI_FORMAT_R32G32_FLOAT;
		case Zorlock::ShaderDataType::Float3:   return DXGI_FORMAT_R32G32B32_FLOAT;
		case Zorlock::ShaderDataType::Float4:   return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case Zorlock::ShaderDataType::Mat3:     return DXGI_FORMAT_R32G32B32_FLOAT;
		case Zorlock::ShaderDataType::Mat4:     return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case Zorlock::ShaderDataType::Int:      return DXGI_FORMAT_R32_SINT;
		case Zorlock::ShaderDataType::Int2:     return DXGI_FORMAT_R32G32_SINT;
		case Zorlock::ShaderDataType::Int3:     return DXGI_FORMAT_R32G32B32_SINT;
		case Zorlock::ShaderDataType::Int4:     return DXGI_FORMAT_R32G32B32A32_SINT;
		case Zorlock::ShaderDataType::Bool:     return DXGI_FORMAT_R1_UNORM;
		}

		ZL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return DXGI_FORMAT_UNKNOWN;
	}

	DX11VertexArray::DX11VertexArray()
	{
		ZL_PROFILE_FUNCTION();

	}
	DX11VertexArray::~DX11VertexArray()
	{
		ZL_PROFILE_FUNCTION();
	}
	void DX11VertexArray::Bind() const
	{
		ZL_PROFILE_FUNCTION();
	}
	void DX11VertexArray::Unbind() const
	{
		ZL_PROFILE_FUNCTION();
	}
	void DX11VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		ZL_PROFILE_FUNCTION();
	}
	void DX11VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		ZL_PROFILE_FUNCTION();
	}
}
