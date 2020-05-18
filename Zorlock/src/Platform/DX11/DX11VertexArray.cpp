#include "ZLpch.h"
#include "DX11VertexArray.h"
#include <d3d11.h>
#include <DX11Raz.h>
#include <DX11VBuffer.h>


namespace Zorlock
{

	static DXGI_FORMAT ShaderDataTypeToOpenDXBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Zorlock::ShaderDataType::Float:    return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
		case Zorlock::ShaderDataType::Float2:   return DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
		case Zorlock::ShaderDataType::Float3:   return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
		case Zorlock::ShaderDataType::Float4:   return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
		case Zorlock::ShaderDataType::Mat3:     return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
		case Zorlock::ShaderDataType::Mat4:     return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
		case Zorlock::ShaderDataType::Int:      return DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
		case Zorlock::ShaderDataType::Int2:     return DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT;
		case Zorlock::ShaderDataType::Int3:     return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT;
		case Zorlock::ShaderDataType::Int4:     return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
		case Zorlock::ShaderDataType::Bool:     return DXGI_FORMAT::DXGI_FORMAT_R1_UNORM;
		}

		ZL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
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
		//nothing to do here...since we have a direct reference to the buffer itself no need to make it current for operations
		ZL_PROFILE_FUNCTION();
	}
	void DX11VertexArray::Unbind() const
	{
		//nothing to do here...since we have a direct reference to the buffer itself no need to disable it for operations
		ZL_PROFILE_FUNCTION();
	}
	void DX11VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		ZL_PROFILE_FUNCTION();

		ZL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		if (vertexBuffer->GetLayout().GetElements().size() == 0) return;
		m_RendererID = DX11Raz::RazCreateVertexBuffer();
		vertexBuffer->Bind(m_RendererID);
		const auto& layout = vertexBuffer->GetLayout();
		int index = 0;
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				
				m_RendererID->SetIndex(m_VertexBufferIndex);
				D3D11_INPUT_ELEMENT_DESC& l = m_RendererID->GetLayoutPointer(m_VertexBufferIndex);
				l.SemanticName = element.SemanticName.c_str();				
				l.SemanticIndex = 0;
				l.Format = ShaderDataTypeToOpenDXBaseType(element.Type);
				l.InputSlot = 0;
				l.AlignedByteOffset = layout.GetStride();//(index==0) ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;//element.Offset;
				l.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				l.InstanceDataStepRate = 0;
				m_RendererID->SetIndexValue(m_VertexBufferIndex, l);
				char buffer[100];
				sprintf(buffer, "Layout NAME %s FORMAT %i INDEX %i STRIDE %i \r\n", element.SemanticName.c_str(), l.Format, m_VertexBufferIndex, layout.GetStride());
				OutputDebugStringA(buffer);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					m_RendererID->SetIndex(m_VertexBufferIndex);
					D3D11_INPUT_ELEMENT_DESC& l = m_RendererID->GetLayoutPointer(m_VertexBufferIndex);
					char buffer[100];
					sprintf(buffer, "Layout NAME %s\r\n", element.Name.c_str());
					OutputDebugStringA(buffer);
					l.SemanticName = element.Name.c_str();
					l.SemanticIndex = count;
					l.Format = ShaderDataTypeToOpenDXBaseType(element.Type);
					l.InputSlot = index;
					l.AlignedByteOffset = (sizeof(float) * count * i);
					l.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
					l.InstanceDataStepRate = 0;
					m_RendererID->SetIndexValue(m_VertexBufferIndex, l);
					m_VertexBufferIndex++;
				}
				break;
			}
			default:
				ZL_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
			
			index++;
		}

		vertexBuffer->ApplyLayout();

		m_VertexBuffers.push_back(vertexBuffer);
		
		
		
		//call it after we have layout set in place, need to pass our buffer unlike opengl we are using the same buffer for verts and layout
		vertexBuffer->Bind(m_RendererID);
		ZL_PROFILE_FUNCTION();
	}
	void DX11VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
		ZL_PROFILE_FUNCTION();
	}
}
