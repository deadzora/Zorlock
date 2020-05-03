#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "Math.h"
#include "ErrorLogger.h"

VertexBuffer::VertexBuffer():m_layout(0),m_buffer(0)
{
}

bool VertexBuffer::load(void * list_vertices, UINT size_vertex, UINT size_list)
{
	if (this->m_buffer)this->m_buffer->Release();
	if (this->m_layout)this->m_layout->Release();


	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;


	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	this->m_size_vertex = size_vertex;
	this->m_size_list = size_list;
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &this->m_buffer);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Vertex Buffer");
		return false;
	}
	return true;
}



bool VertexBuffer::setlayout(void * shader_byte_code, UINT size_byte_shader)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//Semantic name -	semantic index -	format-							input slot -					aligned byte offset -	input slot class -				instamce data step rate
		{"POSITION",		0,					DXGI_FORMAT_R32G32B32_FLOAT,	0,								0,						D3D11_INPUT_PER_VERTEX_DATA,		0},
		{"NORMAL",			0,					DXGI_FORMAT_R32G32B32_FLOAT,	0,								D3D11_APPEND_ALIGNED_ELEMENT,						D3D11_INPUT_PER_VERTEX_DATA,		0},
		{"COLOR",			0,					DXGI_FORMAT_R32G32B32_FLOAT,	0,								D3D11_APPEND_ALIGNED_ELEMENT,						D3D11_INPUT_PER_VERTEX_DATA,		0},
		{"TEXCOORD",		0,					DXGI_FORMAT_R32G32B32_FLOAT,	0,								D3D11_APPEND_ALIGNED_ELEMENT,						D3D11_INPUT_PER_VERTEX_DATA,		0}
	};
	UINT size_layout = ARRAYSIZE(layout);
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &this->m_layout);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Input Layout");
		return false;
	}
	return true;
}

bool VertexBuffer::load(void* list_vertices,UINT size_vertex,UINT size_list,void* shader_byte_code,UINT size_byte_shader)
{
	if(this->m_buffer)this->m_buffer->Release();
	if(this->m_layout)this->m_layout->Release();


	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;


	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	this->m_size_vertex = size_vertex;
	this->m_size_list = size_list;
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &this->m_buffer);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Vertex Buffer");
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//Semantic name -	semantic index -	format-							input slot -					aligned byte offset -	input slot class -				instance data step rate
		{"POSITION",		0,					DXGI_FORMAT_R32G32B32_FLOAT,	0,								0,													D3D11_INPUT_PER_VERTEX_DATA,		0},
		{"NORMAL",			0,					DXGI_FORMAT_R32G32B32_FLOAT,	0,								D3D11_APPEND_ALIGNED_ELEMENT,						D3D11_INPUT_PER_VERTEX_DATA,		0},
		{"COLOR",			0,					DXGI_FORMAT_R32G32B32_FLOAT,	0,								D3D11_APPEND_ALIGNED_ELEMENT,						D3D11_INPUT_PER_VERTEX_DATA,		0},
		{"TEXCOORD",		0,					DXGI_FORMAT_R32G32B32_FLOAT,	0,								D3D11_APPEND_ALIGNED_ELEMENT,						D3D11_INPUT_PER_VERTEX_DATA,		0}
	};
	UINT size_layout = ARRAYSIZE(layout);
	hr = GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &this->m_layout);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Input Layout");
		return false;
	}

	return true;
}






bool VertexBuffer::setlayout(const D3D11_INPUT_ELEMENT_DESC * layout, UINT size_layout, void * shader_byte_code, UINT size_byte_shader)
{

	//UINT size_layout = ARRAYSIZE(layout);
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &this->m_layout);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Input Layout");
		return false;
	}
	return true;

}


bool VertexBuffer::load(D3D11_INPUT_ELEMENT_DESC * layout, UINT size_layout, void * list_vertices, UINT size_vertex, UINT size_list, void * shader_byte_code, UINT size_byte_shader)
{
	if (this->m_buffer)this->m_buffer->Release();
	if (this->m_layout)this->m_layout->Release();


	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;


	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	this->m_size_vertex = size_vertex;
	this->m_size_list = size_list;

	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &this->m_buffer);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Vertex Buffer");
		return false;
	}

	//UINT size_layout = ARRAYSIZE(layout);
	hr = GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &this->m_layout);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Input Layout");
		return false;
	}

	return true;
}


UINT VertexBuffer::GetVertexListSize()
{
	return this->m_size_list;
}

bool VertexBuffer::release()
{
	this->m_buffer->Release();
	this->m_layout->Release();
	
	delete this;
	return true;
}


VertexBuffer::~VertexBuffer()
{
}
