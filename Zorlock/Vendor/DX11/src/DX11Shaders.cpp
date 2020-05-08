#include "ZLpch.h"
#include "DX11Shaders.h"
#include "DX11Raz.h"
#include <d3dcompiler.h>

DX11Raz::RazShader::RazShader() : m_buffer(0), m_ps(0), m_vs(0)
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



ID3D10Blob* DX11Raz::RazShader::GetBuffer()
{
	return m_buffer;
}


