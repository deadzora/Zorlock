#include "ZLpch.h"
#include "DX11IBuffer.h"
#include "DX11Raz.h"

DX11Raz::RazIndexBuffer::RazIndexBuffer() : m_buffer(0)
{
	DX11GraphicsEngine::Get()->AddIndexBuffer(RAZPTR<RazIndexBuffer>(this));
}

void DX11Raz::RazIndexBuffer::Release()
{
	if(m_buffer!=nullptr)m_buffer->Release();
	
}

void DX11Raz::RazIndexBuffer::SetIndexes(UINT* indices, UINT count)
{
	if (this->m_buffer!=nullptr)this->m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = sizeof(UINT) * count;
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = indices;

	this->m_size_index = sizeof(UINT);
	this->m_size_list = count;
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, &init_data, &this->m_buffer);
	if (FAILED(hr))
	{
		printf("Failed to Create Index Buffer");
		OutputDebugStringW(L"Failed to Create Index Buffer");

		return;
	}

}

void DX11Raz::RazIndexBuffer::SetIndexes(std::vector<DWORD> indices)
{
	if (this->m_buffer!=nullptr)this->m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = sizeof(DWORD) * indices.size();
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;


	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = indices.data();

	this->m_size_index = sizeof(DWORD);
	this->m_size_list = indices.size();
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, &init_data, &this->m_buffer);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Index Buffer");

		return;
	}

}

DX11Raz::RazIndexBuffer::~RazIndexBuffer()
{
	
}
