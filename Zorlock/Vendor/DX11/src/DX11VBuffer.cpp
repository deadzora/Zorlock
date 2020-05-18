#include "ZLpch.h"
#include "DX11VBuffer.h"
#include "DX11Vertex.h"
#include "DX11Raz.h"

DX11Raz::RazVertexBuffer::RazVertexBuffer() :m_layout(0), m_buffer(0), m_size_vertex(0), m_size_list(0)
{
}

bool DX11Raz::RazVertexBuffer::SetLayout()
{
	//Bind without Shader, very unoptimized way to bind layouts, data may get reinterpreted wrong with different shaders if the inputs do not match exactly.
	size_t size_layout = vlayout.size();
	char buffer[100];
	sprintf(buffer, "LayoutSize %zi \r\n", vlayout.size());

	OutputDebugStringA(buffer);
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateInputLayout(vlayout.data(),vlayout.size(), NULL, 0, &this->m_layout);
	if (FAILED(hr))
	{
		OutputDebugString(L"Failed to Create Input Layout\r\n");
		ZL_CORE_ASSERT(true, "Failed to Create Input Layout");
		this->m_layout = 0;
		return false;
	}
	return true;
}

bool DX11Raz::RazVertexBuffer::SetLayout(ID3D10Blob* vshader)
{
	//Bind without Shader, very unoptimized way to bind layouts, data may get reinterpreted wrong with different shaders if the inputs do not match exactly.
	size_t size_layout = vlayout.size();
	char buffer[100];
	sprintf(buffer, "LayoutSize %zi \r\n", vlayout.size());

	OutputDebugStringA(buffer);
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateInputLayout(vlayout.data(), vlayout.size(), vshader->GetBufferPointer(), vshader->GetBufferSize(), &this->m_layout);
	if (FAILED(hr))
	{
		OutputDebugString(L"Failed to Create Input Layout\r\n");
		ZL_CORE_ASSERT(true, "Failed to Create Input Layout");
		this->m_layout = 0;
		return false;
	}
	return true;
}



void DX11Raz::RazVertexBuffer::Release()
{
	if(this->m_buffer!=0)this->m_buffer->Release();
	m_buffer = 0;
	if(this->m_layout!=0)this->m_layout->Release();
	m_layout = 0;
	delete this;
}


void DX11Raz::RazVertexBuffer::SetIndex(uint32_t index)
{
	if (index + 1 > vlayout.size())
	{
		D3D11_INPUT_ELEMENT_DESC e;
		vlayout.resize(index + 1,e);
	}


}

void DX11Raz::RazVertexBuffer::SetIndexValue(UINT index, D3D11_INPUT_ELEMENT_DESC& value)
{
	vlayout[index] = value;
}

void DX11Raz::RazVertexBuffer::SetVertices(uint32_t size)
{

	//no;

}

void DX11Raz::RazVertexBuffer::SetVertices(float* vertices, UINT size)
{
	if (this->m_buffer!=0) this->m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = sizeof(float) * size;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices;

	this->m_size_vertex = sizeof(float);
	this->m_size_list = size;

	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, &init_data, &this->m_buffer);
	if (FAILED(hr))
	{
		m_buffer = 0;
		OutputDebugStringW(L"Failed to Create Vertex Buffer");
		return;
	}

}

void DX11Raz::RazVertexBuffer::SetVertices(void* vertices, UINT size)
{
	//assuming raz vertex list
	//std::vector<DX11Raz::RazVertex>* verts = static_cast<std::vector<DX11Raz::RazVertex>*>(vertices);
	if (this->m_buffer != 0) this->m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices;

	this->m_size_vertex = size;


	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, &init_data, &this->m_buffer);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Vertex Buffer");
		return;
	}


}

void DX11Raz::RazVertexBuffer::SetVertices(std::vector<RazVertex>& v)
{
	if (this->m_buffer!=0)this->m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = sizeof(RazVertex) * (UINT)v.size();
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = v.data();

	this->m_size_vertex = sizeof(RazVertex);
	this->m_size_list = (UINT)v.size();

	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, &init_data, &this->m_buffer);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Vertex Buffer");
		return;
	}
}

D3D11_INPUT_ELEMENT_DESC& DX11Raz::RazVertexBuffer::GetLayoutPointer(UINT index)
{
	D3D11_INPUT_ELEMENT_DESC * layout = new D3D11_INPUT_ELEMENT_DESC();
	vlayout[index] = *layout;
	return *layout;
}

UINT DX11Raz::RazVertexBuffer::GetVertexListSize()
{
	return m_size_list;
}

DX11Raz::RazVertexBuffer::~RazVertexBuffer()
{

}
