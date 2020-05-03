#include "PixelShader.h"
#include "GraphicsEngine.h"
#include "ErrorLogger.h"
#include <d3d11.h>
#include <d3dcompiler.h>

PixelShader::PixelShader()
{
}

void PixelShader::release()
{
	if (m_ps)m_ps->Release();
	delete this;
}


PixelShader::~PixelShader()
{
}

bool PixelShader::init(const wchar_t * filename)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT hr = D3DCompileFromFile(filename, nullptr, nullptr, "psmain", "ps_5_0", 0, 0, &this->m_buffer, &error_blob);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Compile Pixel Shader");
		return false;
	}
	hr = GraphicsEngine::get()->m_d3d_device->CreatePixelShader(this->m_buffer->GetBufferPointer(), this->m_buffer->GetBufferSize(), NULL, &m_ps);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Pixel Shader");
		return false;
	}
	return true;
}



bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps);
	if (!SUCCEEDED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Pixel Shader");
		return false;
	}

	return true;
}