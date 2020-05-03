#include "ConstantBuffer2D.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "Math.h"
#include "ErrorLogger.h"

/*
ConstantBuffer2D::ConstantBuffer2D()
{
}

ConstantBuffer2D::ConstantBuffer2D(ID3D11DeviceContext * device_context, ID3D11Device * d3d_device) {
	this->m_device_context = device_context;
	this->m_d3d_device = d3d_device;
}

bool ConstantBuffer2D::create()
{
	if (m_buffer)m_buffer->Release();


	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DYNAMIC;
	buff_desc.ByteWidth = sizeof(CB_VS_VertexShader) + (16 - (sizeof(CB_VS_VertexShader) % 16));
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buff_desc.MiscFlags = 0;
	buff_desc.StructureByteStride = 0;

	//D3D11_SUBRESOURCE_DATA init_data = {};
	//init_data.pSysMem = list_constants;

	//m_size_constant = size_constant;

	this->m_vsd = new CB_VS_VertexShader;
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, 0, &this->m_buffer);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Constant Buffer");
		return false;
	}



	return true;
}

bool ConstantBuffer2D::apply()
{


	if (!this->m_buffer)
	{
		ErrorLogger::Log("2D Buffer not Initialized");
		return false;
	}
	D3D11_MAPPED_SUBRESOURCE init_data = {};
	//ZeroMemory(&init_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT hr;
	hr = this->m_device_context->Map(this->m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Could not Map Initial Data");
		return false;
	}
	//find a way to pass struct types


	CopyMemory(init_data.pData, this->m_vsd, sizeof(CB_VS_VertexShader));


	this->m_device_context->Unmap(this->m_buffer, 0);
	this->m_device_context->VSSetConstantBuffers(0, 1, &this->m_buffer);
	return true;
}


ConstantBuffer2D::~ConstantBuffer2D()
{
}

*/
