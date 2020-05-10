#include "ZLpch.h"
#include "DX11Shaders.h"
#include "DX11Raz.h"
#include "DX11DeviceContext.h"
#include <d3dcompiler.h>

DX11Raz::RazShader::RazShader() : m_buffer(0), m_ps(0), m_vs(0), pc_buffer(0), vc_buffer(0)
{
}

DX11Raz::RazShader::~RazShader()
{
}

void DX11Raz::RazShader::Release()
{
	if (m_buffer != 0)m_buffer->Release();
	if (m_ps != 0)m_ps->Release();
	if (m_vs != 0)m_vs->Release();
	for (size_t i = 0; i < pc_buffer.size(); i++)
	{
		delete pdata[i];
		pc_buffer[i]->Release();
		
	}
	pdata.clear();
	pc_buffer.clear();
	pbsize.clear();
	for (size_t i = 0; i < vc_buffer.size(); i++)
	{
		delete vdata[i];
		vc_buffer[i]->Release();
	}
	vdata.clear();
	vc_buffer.clear();
	vbsize.clear();
	delete this;
}

bool DX11Raz::RazShader::InitVertex(const wchar_t* filename)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT hr = D3DCompileFromFile(filename, nullptr, nullptr, "vsmain", "vs_5_0", 0, 0, &this->m_buffer, &error_blob);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Compile Vertex Shader");
		return false;
	}
	hr = DX11GraphicsEngine::Get()->GetDevice()->CreateVertexShader(this->m_buffer->GetBufferPointer(), this->m_buffer->GetBufferSize(), NULL, &this->m_vs);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Vertex Shader");
		return false;
	}
	return true;
}

bool DX11Raz::RazShader::InitVertex(const std::string shadertext)
{
	ID3DBlob* error_blob = nullptr;
	LPCSTR shader = shadertext.c_str();
	HRESULT hr = D3DCompile(&shader, shadertext.size(), NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "vsmain", "vs_5_0", 0, 0, &this->m_buffer, &error_blob);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Compile Vertex Shader");
		return false;
	}
	hr = DX11GraphicsEngine::Get()->GetDevice()->CreateVertexShader(this->m_buffer->GetBufferPointer(), this->m_buffer->GetBufferSize(), NULL, &this->m_vs);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Vertex Shader");
		return false;
	}
	return true;
}

bool DX11Raz::RazShader::InitVertex(const void* shader_byte_code, size_t byte_code_size)
{
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &this->m_vs);
	if (!SUCCEEDED(hr))
	{
		OutputDebugStringW(L"Failed to Create Vertex Shader");
		return false;
	}

	return true;
}

bool DX11Raz::RazShader::InitPixel(const wchar_t* filename)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT hr = D3DCompileFromFile(filename, nullptr, nullptr, "psmain", "ps_5_0", 0, 0, &this->m_buffer, &error_blob);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Compile Pixel Shader");
		return false;
	}
	hr = DX11GraphicsEngine::Get()->GetDevice()->CreatePixelShader(this->m_buffer->GetBufferPointer(), this->m_buffer->GetBufferSize(), NULL, &m_ps);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Pixel Shader");
		return false;
	}
	return true;
}

bool DX11Raz::RazShader::InitPixel(const std::string shadertext)
{
	ID3DBlob* error_blob = nullptr;
	LPCSTR shader = shadertext.c_str();
	HRESULT hr = D3DCompile(&shader, shadertext.size(), NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "vsmain", "vs_5_0", 0, 0, &this->m_buffer, &error_blob);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Compile Vertex Shader");
		return false;
	}
	hr = DX11GraphicsEngine::Get()->GetDevice()->CreatePixelShader(this->m_buffer->GetBufferPointer(), this->m_buffer->GetBufferSize(), NULL, &m_ps);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Pixel Shader");
		return false;
	}
	return true;
}

bool DX11Raz::RazShader::InitPixel(const void* shader_byte_code, size_t byte_code_size)
{
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps);
	if (!SUCCEEDED(hr))
	{
		OutputDebugStringW(L"Failed to Create Pixel Shader");
		return false;
	}
	return true;
}

UINT DX11Raz::RazShader::CreateVertexCB(void* bufferdata, UINT buffersize)
{
	


	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DYNAMIC;
	buff_desc.ByteWidth = buffersize + (16 - (buffersize % 16));
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buff_desc.MiscFlags = 0;
	buff_desc.StructureByteStride = 0;
	ID3D11Buffer* v;

	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, 0, &v);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Vertex Constant Buffer");
		return -1;
	}
	vc_buffer.push_back(v);
	vdata.push_back(bufferdata);
	vbsize.push_back(buffersize);
	return vdata.size()-1;
}

UINT DX11Raz::RazShader::CreatePixelCB(void* bufferdata, UINT buffersize)
{



	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DYNAMIC;
	buff_desc.ByteWidth = buffersize + (16 - (buffersize % 16));
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buff_desc.MiscFlags = 0;
	buff_desc.StructureByteStride = 0;
	ID3D11Buffer* p; 

	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, 0, &p);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Pixel Constant Buffer");
		return -1;
	}
	pc_buffer.push_back(p);
	pdata.push_back(bufferdata);
	pbsize.push_back(buffersize);
	return 1;
}

bool DX11Raz::RazShader::UpdateVertexCB(void* bufferdata, UINT buffersize, UINT index)
{
	vdata[index] = bufferdata;
	vbsize[index] = buffersize;

	return true;
}

bool DX11Raz::RazShader::UpdatePixelCB(void* bufferdata, UINT buffersize, UINT index)
{
	pdata[index] = bufferdata;
	pbsize[index] = buffersize;
	return true;
}

bool DX11Raz::RazShader::ApplyVertexCB(void* bufferdata, UINT buffersize, UINT index)
{
	if (!this->vc_buffer[index])
	{
		OutputDebugStringW(L"Vertex ConstantBuffer Buffer Pointer was Null");
		return false;
	}



	D3D11_MAPPED_SUBRESOURCE init_data = {};
	//ZeroMemory(&init_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT hr;
	hr = DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Map(this->vc_buffer[index], 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Could not Map Vertex Shader Data");
		return false;
	}
	vdata[index] = bufferdata;
	vbsize[index] = buffersize;

	CopyMemory(init_data.pData, bufferdata, buffersize);


	DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Unmap(this->vc_buffer[index], 0);
	DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->VSSetConstantBuffers(index, 1, &this->vc_buffer[index]);
	
	return true;
}

bool DX11Raz::RazShader::ApplyPixelCB(void* bufferdata, UINT buffersize, UINT index)
{
	if (!this->pc_buffer[index])
	{
		OutputDebugStringW(L"Pixel ConstantBuffer Buffer Pointer was Null");
		return false;
	}
	pdata[index] = bufferdata;
	pbsize[index] = buffersize;

	D3D11_MAPPED_SUBRESOURCE init_data = {};
	//ZeroMemory(&init_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT hr;
	hr = DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Map(this->pc_buffer[index], 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Could not Map Pixel Shader Data");
		return false;
	}


	CopyMemory(init_data.pData, bufferdata, buffersize);


	DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Unmap(this->pc_buffer[index], 0);
	DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->PSSetConstantBuffers(index, 1, &this->pc_buffer[index]);

	return true;
}

void* DX11Raz::RazShader::GetPixelCBData(UINT index)
{
	return pdata[index];
}

void* DX11Raz::RazShader::GetVertexCBData(UINT index)
{
	return vdata[index];
}

bool DX11Raz::RazShader::ApplyAllVertexCB()
{
	bool noerror = true;
	for (size_t i = 0; i < this->vc_buffer.size(); i++)
	{


		if (!this->vc_buffer[i])
		{
			//OutputDebugStringW(L"Vertex ConstantBuffer Buffer Pointer was Null");
			continue;
		}


		D3D11_MAPPED_SUBRESOURCE init_data = {};
		//ZeroMemory(&init_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
		HRESULT hr;
		hr = DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Map(this->vc_buffer[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
		if (FAILED(hr))
		{
			OutputDebugStringW(L"Could not Map Vertex Shader Data");
			noerror = false;
			continue;
		}


		CopyMemory(init_data.pData, vdata[i], vbsize[i]);


		DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Unmap(this->vc_buffer[i], 0);
		DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->VSSetConstantBuffers(i, 1, &this->vc_buffer[i]);
	}
	return noerror;
}

bool DX11Raz::RazShader::ApplyAllPixelCB()
{
	bool noerror = true;
	for (size_t i = 0; i < this->pc_buffer.size(); i++)
	{


		if (!this->pc_buffer[i])
		{
			//OutputDebugStringW(L"Pixel ConstantBuffer Buffer Pointer was Null");
			continue;
		}

		D3D11_MAPPED_SUBRESOURCE init_data = {};
		//ZeroMemory(&init_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
		HRESULT hr;
		hr = DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Map(this->pc_buffer[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
		if (FAILED(hr))
		{
			OutputDebugStringW(L"Could not Map Pixel Shader Data");
			noerror = false;
			continue;
		}


		CopyMemory(init_data.pData, pdata[i], pbsize[i]);


		DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Unmap(this->pc_buffer[i], 0);
		DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->PSSetConstantBuffers(i, 1, &this->pc_buffer[i]);
	}
	return noerror;
}



ID3D10Blob* DX11Raz::RazShader::GetBuffer()
{
	return m_buffer;
}


