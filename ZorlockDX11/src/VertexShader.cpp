#include "VertexShader.h"
#include "GraphicsEngine.h"
#include "ErrorLogger.h"
#include <d3d11.h>
#include <d3dcompiler.h>


VertexShader::VertexShader()
{
}

void VertexShader::release()
{
	if(m_vs)m_vs->Release();
	delete this;
}


VertexShader::~VertexShader()
{
}
//alternative way
bool VertexShader::init(const wchar_t * filename)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT hr = D3DCompileFromFile(filename, nullptr, nullptr, "vsmain", "vs_5_0", 0, 0, &this->m_buffer, &error_blob);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Compile Vertex Shader");
		return false;
	}
	hr = GraphicsEngine::get()->m_d3d_device->CreateVertexShader(this->m_buffer->GetBufferPointer(), this->m_buffer->GetBufferSize(), NULL, &this->m_vs);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Vertex Shader");
		return false;
	}
	return true;
}



bool VertexShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &this->m_vs);
	if (!SUCCEEDED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Vertex Shader");
		return false;
	}

	return true;
}
