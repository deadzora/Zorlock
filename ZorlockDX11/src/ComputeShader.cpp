#include "ComputeShader.h"
#include "GraphicsEngine.h"
#include "ErrorLogger.h"
#include <d3d11.h>
#include <d3dcompiler.h>


ComputeShader::ComputeShader()
{
}

void ComputeShader::release()
{
	if (m_cs)m_cs->Release();
	delete this;
}


ComputeShader::~ComputeShader()
{
}

bool ComputeShader::init(const wchar_t * filename)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT hr = D3DCompileFromFile(filename, nullptr, nullptr, "csmain", "ps_5_0", 0, 0, &this->m_buffer, &error_blob);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Compile Compute Shader");
		return false;
	}
	hr = GraphicsEngine::get()->m_d3d_device->CreateComputeShader(this->m_buffer->GetBufferPointer(), this->m_buffer->GetBufferSize(), NULL, &m_cs);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Compute Shader");
		return false;
	}
	return true;
}



bool ComputeShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateComputeShader(shader_byte_code, byte_code_size, nullptr, &m_cs);
	if (!SUCCEEDED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Compute Shader");
		return false;
	}

	return true;
}
