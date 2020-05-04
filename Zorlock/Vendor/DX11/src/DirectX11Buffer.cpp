#include "ZLpch.h"
#include "DirectX11Buffer.h"
#include "DX11Graphics.h"
namespace ZorlockDX11
{

	bool DirectX11Buffer::Bind(void* m_list, unsigned int m_size)
	{
		if (this->m_buffer)this->m_buffer->Release();
		if (this->m_layout)this->m_layout->Release();

		D3D11_BUFFER_DESC buff_desc = {};
		buff_desc.Usage = D3D11_USAGE_DEFAULT;
		buff_desc.ByteWidth = m_size;
		buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buff_desc.CPUAccessFlags = 0;
		buff_desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA init_data = {};
		init_data.pSysMem = m_list;
		this->m_size = m_size;
		HRESULT hr = ZorlockDX11::DX11GraphicsEngine::get()->GetD3D11Device->CreateBuffer(&buff_desc, &init_data, &this->m_buffer);
		if (FAILED(hr))
		{
			ZL_CORE_INFO("Failed to Create Vertex Buffer");
			return false;
		}
		return false;
	}




}
