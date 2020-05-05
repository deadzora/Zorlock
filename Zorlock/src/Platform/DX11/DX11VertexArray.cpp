#include "ZLpch.h"
#include "DX11VertexArray.h"
#include <vector>
namespace Zorlock {

	static DXGI_FORMAT ShaderDataTypeToOpenDXBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Zorlock::ShaderDataType::Float:    return DXGI_FORMAT_R32_FLOAT;
		case Zorlock::ShaderDataType::Float2:   return DXGI_FORMAT_R32G32_FLOAT;
		case Zorlock::ShaderDataType::Float3:   return DXGI_FORMAT_R32G32B32_FLOAT;
		case Zorlock::ShaderDataType::Float4:   return DXGI_FORMAT_R32G32B32A32_FLOAT;
		//case Zorlock::ShaderDataType::Mat3:     return GL_FLOAT; //Must use Stream
		//case Zorlock::ShaderDataType::Mat4:     return GL_FLOAT; //Must Use Stream
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
		this->m_varray = ZorlockDX11::DX11GraphicsEngine::get()->DX11CreateVertexArray();
	}

	DX11VertexArray::~DX11VertexArray()
	{
		ZorlockDX11::DX11GraphicsEngine::get()->DX11DeleteVertexArray(this->m_varray);
		this->m_varray = 0;
	}

	void DX11VertexArray::Bind() const
	{
		//Not implemented
	}

	void DX11VertexArray::Unbind() const
	{
		//Not implemented
	}

	void DX11VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		ZL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();

		uint32_t layoutsize = layout.GetSize();

		D3D11_INPUT_ELEMENT_DESC** dxlayout = new D3D11_INPUT_ELEMENT_DESC * [layoutsize];

		//std::vector<D3D11_INPUT_ELEMENT_DESC[]> dxlayout;
		for (const auto& element : layout)
		{
			//glEnableVertexAttribArray(index);

			//Second Value = Semantic Index: The semantic index for the element. A semantic index modifies a semantic, with an integer index number. 
			//A semantic index is only needed in a case where there is more than one element with the same semantic. For example, a 4x4 matrix would 
			//have four components each with the semantic name
			dxlayout[index] = new D3D11_INPUT_ELEMENT_DESC[7]
			{ element.Name.c_str(),	0,	ShaderDataTypeToOpenDXBaseType(element.Type),0,	element.Offset,	D3D11_INPUT_PER_VERTEX_DATA,0 };



			

			index++;
		}
		UINT size_layout = sizeof(dxlayout);
		m_VertexBuffers.push_back(vertexBuffer);

	}

	void DX11VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
	}

}