#include "ConstantPixelBuffer.h"
#include "GraphicsEngine.h"
#include "Math.h"
#include "ErrorLogger.h"
#include <d3d11.h>
#include <DirectXMath.h>

/*

bool ConstantPixelBuffer::create()
{
	if (this->m_buffer)this->m_buffer->Release();
	if (this->m_abuffer)this->m_abuffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DYNAMIC;
	buff_desc.ByteWidth = sizeof(CB_PS_PixelShader) + (16 - (sizeof(CB_PS_PixelShader) % 16));
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buff_desc.MiscFlags = 0;
	buff_desc.StructureByteStride = 0;

	//D3D11_SUBRESOURCE_DATA init_data = {};
	//init_data.pSysMem = list_constants;
	//CB_PS_AmbientShader
	//m_size_constant = size_constant;

	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, 0, &this->m_buffer);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Pixel Buffer");
		return false;
	}

	this->m_psd = new CB_PS_PixelShader;

	buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DYNAMIC;
	buff_desc.ByteWidth = sizeof(CB_PS_AmbientShader) + (16 - (sizeof(CB_PS_AmbientShader) % 16));
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buff_desc.MiscFlags = 0;
	buff_desc.StructureByteStride = 0;

	hr = GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, 0, &this->m_abuffer);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Ambient Buffer");
		return false;
	}

	this->m_asd = new CB_PS_AmbientShader;


	buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DYNAMIC;
	buff_desc.ByteWidth = sizeof(CB_PS_LIGHTS);// +(16 - (sizeof(CB_PS_LIGHTSTRENGTH) % 16));
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buff_desc.MiscFlags = 0;
	buff_desc.StructureByteStride = 0;

	hr = GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, 0, &this->m_lsbuffer);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Light Strength Buffer");
		return false;
	}
	
	this->m_lsd = new CB_PS_LIGHTS;


	return true;
}

bool ConstantPixelBuffer::release()
{
	if (this->m_buffer)this->m_buffer->Release();
	delete this->m_psd;
	delete this;
	return true;
}

bool ConstantPixelBuffer::apply()
{

	D3D11_MAPPED_SUBRESOURCE init_data = {};
	//ZeroMemory(&init_data, sizeof(D3D11_MAPPED_SUBRESOURCE));

	if (!this->m_buffer)
	{
		ErrorLogger::Log("Pixel Buffer not Initialized");
		return false;
	}
	if (!this->m_abuffer)
	{
		ErrorLogger::Log("Ambient Buffer not Initialized");
		return false;
	}

	HRESULT hr = this->m_device_context->Map(this->m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Set Initial Data Pixel");
		return false;
	}
	//find a way to pass struct types

	
	CopyMemory(init_data.pData, this->m_psd, sizeof(CB_PS_PixelShader));

	
	this->m_device_context->Unmap(this->m_buffer, 0);
	this->m_device_context->PSSetConstantBuffers(1, 1, &this->m_buffer);

	//ambient
	hr = this->m_device_context->Map(this->m_abuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Set Initial Data Ambient");
		return false;
	}

	CopyMemory(init_data.pData, this->m_asd, sizeof(CB_PS_AmbientShader));


	this->m_device_context->Unmap(this->m_abuffer, 0);
	this->m_device_context->PSSetConstantBuffers(2, 1, &this->m_abuffer);

	//dynamic lights
	hr = this->m_device_context->Map(this->m_lsbuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Set Initial Data Light Strength");
		return false;
	}

	CopyMemory(init_data.pData, this->m_lsd, sizeof(CB_PS_LIGHTS));


	this->m_device_context->Unmap(this->m_lsbuffer, 0);
	this->m_device_context->PSSetConstantBuffers(3, 1, &this->m_lsbuffer);

	return true;
}

void ConstantPixelBuffer::setalpha(float a)
{
	this->m_psd->alpha = a;
}

void ConstantPixelBuffer::setlightcolor(int lightnum, float r, float g, float b)
{
	this->m_lsd->lights[lightnum].lightcolor = { r,g,b};
}

void ConstantPixelBuffer::setlightbright(int lightnum, float b)
{
	this->m_lsd->lights[lightnum].strength = b;
}

void ConstantPixelBuffer::setlightpos(int lightnum, const DirectX::XMFLOAT3 & pos)
{
	this->m_lsd->lights[lightnum].lightpos = pos;
}

void ConstantPixelBuffer::setlightattenuation(int lightnum, float a, float b, float c)
{
	//hard code these values for now
	//this->m_asd->dynamiclightattenuation_a[lightnum] = a;
	//this->m_asd->dynamiclightattenuation_b[lightnum] = b;
	//this->m_asd->dynamiclightattenuation_c[lightnum] = c;
}

void ConstantPixelBuffer::setlightradius(int lightnum, float radius)
{
	this->m_lsd->lights[lightnum].radius = radius;
}

ConstantPixelBuffer::ConstantPixelBuffer()
{
}

ConstantPixelBuffer::ConstantPixelBuffer(ID3D11DeviceContext * device_context, ID3D11Device * d3d_device)
{
	this->m_device_context = device_context;
	this->m_d3d_device = d3d_device;
}


ConstantPixelBuffer::~ConstantPixelBuffer()
{
}

*/
