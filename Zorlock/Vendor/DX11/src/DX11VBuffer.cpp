#include "ZLpch.h"
#include "DX11VBuffer.h"
#include "DX11Vertex.h"
#include "DX11Shaders.h"
#include "DX11Raz.h"

DX11Raz::RazVertexBuffer::RazVertexBuffer() :m_layout(0), m_buffer(0), m_size_vertex(0), m_size_list(0), stride(0)
{
	DX11GraphicsEngine::Get()->AddVertexBuffer(RAZPTR<RazVertexBuffer>(this));

}

bool DX11Raz::RazVertexBuffer::SetLayout()
{
	//Bind without Shader, very unoptimized way to bind layouts, data may get reinterpreted wrong with different shaders if the inputs do not match exactly.
	/*
	this->stride = 0;
	for (size_t i = 0; i < vlayout.size(); i++)
	{
		stride += vlayout[i].AlignedByteOffset;
	}
	*/
	

	ID3D11InputLayout* ilayout;
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateInputLayout(vlayout.data(),vlayout.size(), NULL, 0, &ilayout);
	if (FAILED(hr))
	{
		OutputDebugString(L"Failed to Create Input Layout\r\n");
		ZL_CORE_ASSERT(true, "Failed to Create Input Layout");
		this->m_layout = 0;
		return false;
	}
	m_layout = RAZPTR<ID3D11InputLayout>(ilayout);
	return true;
}

bool DX11Raz::RazVertexBuffer::SetLayout(RAZPTR<ID3D10Blob> vshader)
{
	
	size_t size_layout = vlayout.size();
	char buffer[100];

	/*
	this->stride = 0;
	for (size_t i = 0; i < vlayout.size(); i++)
	{
		stride += vlayout[i].AlignedByteOffset;
	}
	
	
	*/
	ID3D11InputLayout* ilayout;
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateInputLayout(vlayout.data(), vlayout.size(), vshader->GetBufferPointer(), vshader->GetBufferSize(), &ilayout);
	if (FAILED(hr))
	{
		OutputDebugString(L"Failed to Create Input Layout\r\n");
		ZL_CORE_ASSERT(true, "Failed to Create Input Layout");
		m_layout = nullptr;
		return false;
	}
	m_layout = RAZPTR<ID3D11InputLayout>(ilayout);
	return true;
}



void DX11Raz::RazVertexBuffer::Release()
{
	if (this->m_buffer!=nullptr)
	{
		this->m_buffer->Release();
	}
	//m_buffer = 0;
	if (this->m_layout!=nullptr)
	{
		this->m_layout->Release();
	}
	//m_layout = 0;
	//delete this;
}

void DX11Raz::RazVertexBuffer::SetStride(UINT s)
{
	stride = s;
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

void DX11Raz::RazVertexBuffer::SetVertices(UINT size)
{
	// we're not going to create a buffer until we have actual data, by then we will have the stride from the shader.
	this->m_buffer = 0;

}

void DX11Raz::RazVertexBuffer::SetVertices(float* vertices, UINT size)
{
	if (this->m_buffer!=0) this->m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = sizeof(float)*size;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices;

	//this->m_size_vertex = sizeof(float);
	this->m_size_list = size;
	this->m_size_vertex = sizeof(float);

	//printf("Stride is actually %u and size is %u !!", m_size_vertex, size);
	ID3D11Buffer* ibuff;
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, &init_data, &ibuff);
	if (FAILED(hr))
	{
		m_buffer = nullptr;
		OutputDebugStringW(L"Failed to Create Vertex Buffer");
		return;
	}
	m_buffer = RAZPTR<ID3D11Buffer>(ibuff);

}

void DX11Raz::RazVertexBuffer::SetVertices(void* vertices, UINT bytewidth, UINT size)
{
	if (this->m_buffer != 0) this->m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = bytewidth;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices;

	//this->m_size_vertex = sizeof(float);
	this->m_size_list = size;
	this->m_size_vertex = bytewidth;

	ID3D11Buffer* ibuff;
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, &init_data, &ibuff);
	if (FAILED(hr))
	{
		m_buffer = nullptr;
		OutputDebugStringW(L"Failed to Create Vertex Buffer");
		return;
	}
	m_buffer = RAZPTR<ID3D11Buffer>(ibuff);
}


void DX11Raz::RazVertexBuffer::SetVertices(void* vertices, UINT size)
{

	if (this->m_buffer != 0) this->m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertices;
	//this->m_size_vertex = sizeof(float);
	this->m_size_list = size/stride;
	this->m_size_vertex = stride;
	//printf("Vertices size: %u list size %u byte width: %u \n",size, this->m_size_list, this->m_size_vertex);
	//printf("Stride is actually %u and size is %u !!", m_size_vertex, size);
	ID3D11Buffer* ibuff;
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, &init_data, &ibuff);
	if (FAILED(hr))
	{
		m_buffer = nullptr;
		printf("Failed to Create Vertex Buffer !!");
		OutputDebugStringW(L"Failed to Create Vertex Buffer");
		return;
	}

	m_buffer = RAZPTR<ID3D11Buffer>(ibuff);
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

	//this->m_size_vertex = sizeof(RazVertex);
	this->m_size_list = (UINT)v.size();
	this->m_size_vertex = sizeof(RazVertex);

	ID3D11Buffer* ibuff;
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, &init_data, &ibuff);
	if (FAILED(hr))
	{
		m_buffer = nullptr;
		OutputDebugStringW(L"Failed to Create Vertex Buffer");
		return;
	}
	m_buffer = RAZPTR<ID3D11Buffer>(ibuff);
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
