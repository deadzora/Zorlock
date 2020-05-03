#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include "ErrorLogger.h"

IndexBuffer::IndexBuffer()
{
}

bool IndexBuffer::load(void* list_index, UINT size_index, UINT size_list)
{
	if (this->m_buffer)this->m_buffer->Release();
	


	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_index * size_list;
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_index;

	this->m_size_index = size_index;
	this->m_size_list = size_list;
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &this->m_buffer);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Index Buffer");
		return false;
	}

	return true;
}

UINT IndexBuffer::GetIndexListSize()
{
	return this->m_size_list;
}

bool IndexBuffer::release()
{
	if (this->m_buffer)this->m_buffer->Release();
	delete this;
	return true;
}


IndexBuffer::~IndexBuffer()
{
}
