#include "ZLpch.h"
#include "DX11Shaders.h"
#include "DX11Raz.h"
#include "DX11DeviceContext.h"
#include "DX11Textures.h"
#include <d3dcompiler.h>

DX11Raz::RazShader::RazShader() : mv_buffer(0), mp_buffer(0), m_ps(0), m_vs(0), pc_buffer(0), vc_buffer(0)
{
	DX11GraphicsEngine::Get()->AddShader(RAZPTR<RazShader>(this));
}

DX11Raz::RazShader::~RazShader()
{
}

void DX11Raz::RazShader::Release()
{
	if (mv_buffer != nullptr)
	{
		mv_buffer->Release();
	}
	if (mp_buffer != nullptr)
	{
		mp_buffer->Release();
	}
	if (m_ps != nullptr)
	{
		m_ps->Release();
	}
	if (m_vs != nullptr)
	{
		m_vs->Release();
	}
	for (size_t i = 0; i < pc_buffer.size(); i++)
	{
		
		pc_buffer[i]->Release();

		
	}
	//pc_buffer.clear();

	for (size_t i = 0; i < vc_buffer.size(); i++)
	{
		vc_buffer[i]->Release();

	}
	//vc_buffer.clear();

}

bool DX11Raz::RazShader::InitVertex(const wchar_t* filename)
{
	ID3DBlob* error_blob = nullptr;
	ID3D10Blob * bbuffer = nullptr;
	HRESULT hr = D3DCompileFromFile(filename, nullptr, nullptr, "vsmain", "vs_5_0", D3DCOMPILE_PACK_MATRIX_ROW_MAJOR, 0, &bbuffer, &error_blob);
	if (FAILED(hr))
	{
		error_blob->Release();
		OutputDebugStringW(L"Failed to Compile Vertex Shader from file \n");
		return false;
	}
	mv_buffer = RAZPTR<ID3D10Blob>(bbuffer);
	ID3D11VertexShader* bvs;
	hr = DX11GraphicsEngine::Get()->GetDevice()->CreateVertexShader(this->mv_buffer->GetBufferPointer(), this->mv_buffer->GetBufferSize(), NULL, &bvs);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Vertex Shader from file \n");
		return false;
	}
	m_vs = RAZPTR<ID3D11VertexShader>(bvs);
	return true;
}

bool DX11Raz::RazShader::InitVertex(const std::string shadertext)
{
	ID3DBlob* error_blob = nullptr;
	LPCSTR shader = shadertext.c_str();
	ID3D10Blob* bbuffer = nullptr;
	HRESULT hr = D3DCompile(shader, shadertext.size(), "VertexShader", NULL, NULL, "main", "vs_5_0", D3DCOMPILE_PACK_MATRIX_ROW_MAJOR, 0, &bbuffer, &error_blob);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Compile Vertex Shader from text \n");
		
		HRESULT hrr = D3DWriteBlobToFile(
			error_blob,
			L"vertexshadererror.txt",
			true
		);
		return false;
	}
	mv_buffer = RAZPTR<ID3D10Blob>(bbuffer);
	ID3D11VertexShader* bvs;
	hr = DX11GraphicsEngine::Get()->GetDevice()->CreateVertexShader(this->mv_buffer->GetBufferPointer(), this->mv_buffer->GetBufferSize(), NULL, &bvs);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Vertex Shader \n");
		return false;
	}
	m_vs = RAZPTR<ID3D11VertexShader>(bvs);
	return true;
}

bool DX11Raz::RazShader::InitVertex(const void* shader_byte_code, size_t byte_code_size)
{
	ID3D11VertexShader* bvs;
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &bvs);
	if (!SUCCEEDED(hr))
	{
		OutputDebugStringW(L"Failed to Create Vertex Shader from void* \n");
		return false;
	}
	m_vs = RAZPTR<ID3D11VertexShader>(bvs);
	return true;
}

bool DX11Raz::RazShader::InitPixel(const wchar_t* filename)
{
	ID3DBlob* error_blob = nullptr;
	ID3D10Blob* bbuffer = nullptr;
	HRESULT hr = D3DCompileFromFile(filename, nullptr, nullptr, "main", "ps_5_0", D3DCOMPILE_PACK_MATRIX_ROW_MAJOR, 0, &bbuffer, &error_blob);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Compile Pixel Shader from file \n");
		return false;
	}
	mp_buffer = RAZPTR<ID3D10Blob>(bbuffer);
	ID3D11PixelShader* bps;
	hr = DX11GraphicsEngine::Get()->GetDevice()->CreatePixelShader(this->mp_buffer->GetBufferPointer(), this->mp_buffer->GetBufferSize(), NULL, &bps);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Pixel Shader");
		return false;
	}
	m_ps = RAZPTR<ID3D11PixelShader>(bps);
	return true;
}

bool DX11Raz::RazShader::InitPixel(const std::string shadertext)
{
	ID3DBlob* error_blob = nullptr;
	LPCSTR shader = shadertext.c_str();
	ID3D10Blob* bbuffer = nullptr;
	HRESULT hr = D3DCompile(shader, shadertext.size(), "PixelShader", NULL, NULL, "main", "ps_5_0", D3DCOMPILE_PACK_MATRIX_ROW_MAJOR, 0, &bbuffer, &error_blob);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Compile Pixel Shader from text \n");
		
		HRESULT hrr = D3DWriteBlobToFile(
			error_blob,
			L"pixelshadererror.txt",
			true
		);
		return false;
	}
	mp_buffer = RAZPTR<ID3D10Blob>(bbuffer);
	ID3D11PixelShader* bps;
	hr = DX11GraphicsEngine::Get()->GetDevice()->CreatePixelShader(this->mp_buffer->GetBufferPointer(), this->mp_buffer->GetBufferSize(), NULL, &bps);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Pixel Shader \n");
		return false;
	}
	m_ps = RAZPTR<ID3D11PixelShader>(bps);
	return true;
}

bool DX11Raz::RazShader::InitPixel(const void* shader_byte_code, size_t byte_code_size)
{
	ID3D11PixelShader* bps;
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &bps);
	if (!SUCCEEDED(hr))
	{
		OutputDebugStringW(L"Failed to Create Pixel Shader \n");
		return false;
	}
	m_ps = RAZPTR<ID3D11PixelShader>(bps);
	return true;
}


UINT DX11Raz::RazShader::CreateVertexCB(std::string cbname, UINT slot, void* bufferdata, UINT buffersize)
{
	
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = buffersize + (16 - (buffersize % 16));
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buff_desc.MiscFlags = 0;
	buff_desc.StructureByteStride = 0;

	RAZPTR<RazConstantBuffer> cbuffer = CreateZRef<RazConstantBuffer>();
	ID3D11Buffer* buff;
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, 0, &buff);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Vertex Constant Buffer \n");
		return -1;
	}
	cbuffer->buffer = RAZPTR<ID3D11Buffer>(buff);
	cbuffer->varname = cbname;
	cbuffer->buffersize = buffersize;
	cbuffer->slot = slot;
	//printf("Created Buffer: %s at slot %u size: %u \n", cbuffer->varname.c_str(), cbuffer->slot, cbuffer->buffersize);
	//cbuffer->Copy(static_cast<char*>(bufferdata), cbuffer->buffersize);
	cbuffer->data = bufferdata;
	vc_buffer.push_back(RAZPTR<RazConstantBuffer>(cbuffer));
	return 1;
}

UINT DX11Raz::RazShader::CreatePixelCB(std::string cbname, UINT slot, void* bufferdata, UINT buffersize)
{



	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = buffersize + (16 - (buffersize % 16));
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//buff_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buff_desc.MiscFlags = 0;
	buff_desc.StructureByteStride = 0;
	//ID3D11Buffer* p; 
	RAZPTR<RazConstantBuffer> cbuffer = CreateZRef<RazConstantBuffer>();
	ID3D11Buffer* buff;
	HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBuffer(&buff_desc, 0, &buff);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Failed to Create Pixel Constant Buffer \n");
		return -1;
	}
	cbuffer->buffer = RAZPTR<ID3D11Buffer>(buff);
	cbuffer->varname = cbname;
	cbuffer->buffersize = buffersize;
	cbuffer->slot = slot;
	//printf("Created Buffer: %s at slot %u size: %u \n", cbuffer->varname.c_str(), cbuffer->slot, cbuffer->buffersize);
	//cbuffer->Copy(static_cast<char*>(bufferdata), cbuffer->buffersize);
	cbuffer->data = bufferdata;
	pc_buffer.push_back(RAZPTR<RazConstantBuffer>(cbuffer));
	return 1;
}

bool DX11Raz::RazShader::CreateTextureBuffer(std::string cbname, UINT slot, UINT buffersize, bool isarray)
{
	RazSamplerBuffer* sampler = new RazSamplerBuffer();
	sampler->varname = cbname;
	sampler->buffersize = buffersize;
	sampler->slot = slot;
	sampler->isArray = isarray;
	tx_buffer.push_back(RAZPTR<RazSamplerBuffer>(sampler));
	return true;
}

bool DX11Raz::RazShader::UpdateTextureBuffer(std::string tname, RAZPTR<ID3D11Resource> tex, RAZPTR<ID3D11ShaderResourceView> texturev)
{
	for (size_t i = 0; i < tx_buffer.size(); i++)
	{
		if (tname.compare(tx_buffer[i]->varname) == 0)
		{
			//delete vc_buffer[i]->data;
			tx_buffer[i]->texture = tex;
			tx_buffer[i]->textureview = texturev;
		}
	}

	return true;
}

bool DX11Raz::RazShader::UpdateTextureBuffer(std::string tname, RAZPTR<ID3D11Resource> tex)
{
	for (size_t i = 0; i < tx_buffer.size(); i++)
	{
		if (tname.compare(tx_buffer[i]->varname) == 0)
		{
			//delete vc_buffer[i]->data;
			tx_buffer[i]->texture = tex;
		}
	}

	return true;
}

bool DX11Raz::RazShader::UpdateTextureBuffer(std::string tname, RAZPTR<ID3D11ShaderResourceView> texturev)
{
	for (size_t i = 0; i < tx_buffer.size(); i++)
	{
		if (tname.compare(tx_buffer[i]->varname) == 0)
		{
			//delete vc_buffer[i]->data;
			tx_buffer[i]->textureview = texturev;
		}
	}

	return true;
}

bool DX11Raz::RazShader::UpdateTextureBuffer(std::string tname, RAZPTR<RazTexture> texture)
{
	for (size_t i = 0; i < tx_buffer.size(); i++)
	{
		if (tname.compare(tx_buffer[i]->varname) == 0)
		{
			//delete vc_buffer[i]->data;
			tx_buffer[i]->texture = texture->GetTexture();
			tx_buffer[i]->textureview = texture->GetTextureView();
		}
	}

	return true;
}

bool DX11Raz::RazShader::GetTextureBufferUploaded(UINT slot)
{
	for (size_t i = 0; i < tx_buffer.size(); i++)
	{
		if (slot == tx_buffer[i]->slot)
		{
			return tx_buffer[i]->isuploaded;
		}
	}

	return false;
}

void DX11Raz::RazShader::SetTextureBufferUploaded(UINT slot, bool uploaded)
{
	for (size_t i = 0; i < tx_buffer.size(); i++)
	{
		if (slot == tx_buffer[i]->slot)
		{
			tx_buffer[i]->isuploaded = uploaded;
		}
	}
}



bool DX11Raz::RazShader::UpdateVertexCB(void* bufferdata, std::string cbname)
{

	for (size_t i = 0; i < vc_buffer.size(); i++)
	{
		if (cbname.compare(vc_buffer[i]->varname) == 0)
		{
			//delete vc_buffer[i]->data;
			//vc_buffer[i]->Copy(static_cast<char*>(bufferdata), vc_buffer[i]->buffersize);
			vc_buffer[i]->data = bufferdata;
			//ApplyVertexCB(cbname);
			break;
		}
	}



	return true;
}

bool DX11Raz::RazShader::UpdatePixelCB(void* bufferdata, std::string cbname)
{

	for (size_t i = 0; i < pc_buffer.size(); i++)
	{
		if (cbname.compare(pc_buffer[i]->varname) == 0)
		{
			//delete vc_buffer[i]->data;
			//printf("Updating %s \n",pc_buffer[i]->varname.c_str());
			//pc_buffer[i]->Copy(static_cast<char*>(bufferdata), pc_buffer[i]->buffersize);
			pc_buffer[i]->data = bufferdata;
			//ApplyPixelCB(cbname);
			break;
		}
	}
	return true;
}

bool DX11Raz::RazShader::ApplyVertexCB(std::string cbname)
{
	RAZPTR<RazConstantBuffer> buffer = nullptr;

	for (size_t i = 0; i < vc_buffer.size(); i++)
	{
		if (cbname.compare(vc_buffer[i]->varname) == 0)
		{
			buffer = vc_buffer[i];
			break;
		}
	}

	if (buffer==0)
	{
		printf("Vertex ConstantBuffer: %s Pointer was Null",cbname);
		return false;
	}



	D3D11_MAPPED_SUBRESOURCE init_data = {};
	//ZeroMemory(&init_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT hr;
	DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->UpdateSubresource(buffer->buffer.get(), 0, 0, buffer->data, 0, 0);
	/*
	hr = DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->Map(buffer->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Could not Map Vertex Shader Data");
		return false;
	}

	CopyMemory(init_data.pData, buffer->data, buffer->buffersize);


	DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->Unmap(buffer->buffer, 0);
	
	*/
	ID3D11Buffer* buff = buffer->buffer.get();
	DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->VSSetConstantBuffers(buffer->slot, 1, &buff);
	
	return true;
}

bool DX11Raz::RazShader::ApplyPixelCB(std::string cbname)
{
	RAZPTR<RazConstantBuffer> buffer = 0;

	for (size_t i = 0; i < pc_buffer.size(); i++)
	{
		
		if (cbname.compare(pc_buffer[i]->varname) == 0)
		{
			buffer = pc_buffer[i];
			break;
		}
	}

	if (buffer == 0)
	{

		printf("Pixel ConstantBuffer: %s Pointer was Null", cbname);
		return false;
	}
	//printf("Applying %s \n", buffer->varname.c_str());
	D3D11_MAPPED_SUBRESOURCE init_data = {};
	//ZeroMemory(&init_data, sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT hr;
	DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->UpdateSubresource(buffer->buffer.get(), 0, 0, buffer->data, 0, 0);
	/*
	hr = DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->Map(buffer->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
	if (FAILED(hr))
	{
		OutputDebugStringW(L"Could not Map Pixel Shader Data");
		return false;
	}


	CopyMemory(init_data.pData, buffer->data, buffer->buffersize);


	DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->Unmap(buffer->buffer, 0);
	*/
	ID3D11Buffer* buff = buffer->buffer.get();
	DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->PSSetConstantBuffers(buffer->slot, 1, &buff);

	return true;
}

void* DX11Raz::RazShader::GetPixelCBData(UINT index)
{
	return pc_buffer[index].get();
}

void* DX11Raz::RazShader::GetVertexCBData(UINT index)
{
	return vc_buffer[index].get();
}

bool DX11Raz::RazShader::ApplyAllVertexCB()
{
	/*
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
		//DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->UpdateSubresource(vc_buffer[i]->buffer, 0, 0, vc_buffer[i]->data, 0, 0);
		
		hr = DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->Map(this->vc_buffer[i]->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
		if (FAILED(hr))
		{
			OutputDebugStringW(L"Could not Map Vertex Shader Data");
			noerror = false;
			continue;
		}


		CopyMemory(init_data.pData, this->vc_buffer[i]->data, this->vc_buffer[i]->buffersize);


		DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->Unmap(this->vc_buffer[i]->buffer, 0);

		
		DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->VSSetConstantBuffers(this->vc_buffer[i]->slot, 1, &this->vc_buffer[i]->buffer);
	}
	return noerror;
	*/
	return true;
}

bool DX11Raz::RazShader::ApplyAllPixelCB()
{
	/*
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
		//DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->UpdateSubresource(pc_buffer[i]->buffer, 0, 0, pc_buffer[i]->data, 0, 0);
		
		hr = DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->Map(this->pc_buffer[i]->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
		if (FAILED(hr))
		{
			OutputDebugStringW(L"Could not Map Pixel Shader Data");
			noerror = false;
			continue;
		}


		CopyMemory(init_data.pData, this->pc_buffer[i]->data, this->pc_buffer[i]->buffersize);


		DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->Unmap(this->pc_buffer[i]->buffer, 0);
		
		DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->GetContext()->PSSetConstantBuffers(this->pc_buffer[i]->slot, 1, &this->pc_buffer[i]->buffer);
	}
	return noerror;
	*/
	return true;
}

void DX11Raz::RazShader::ApplyTexture(std::string cbname)
{
	RAZPTR<RazSamplerBuffer> buffer = 0;

	for (size_t i = 0; i < tx_buffer.size(); i++)
	{
		if (cbname.compare(tx_buffer[i]->varname) == 0)
		{
			buffer = tx_buffer[i];
			break;
		}
	}

	if (buffer == 0)
	{
		OutputDebugStringW(L"Texture Buffer Pointer was Null");
		return;
	}
	if (!buffer->isuploaded)
	{
		buffer->isuploaded = true;
		DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->setshadertexture(buffer->slot, buffer->textureview);
	}
}

void DX11Raz::RazShader::ApplyTextureArray(std::string cbname)
{
	RAZPTR<RazSamplerBuffer> buffer = 0;

	for (size_t i = 0; i < tx_buffer.size(); i++)
	{
		if (cbname.compare(tx_buffer[i]->varname) == 0)
		{
			buffer = tx_buffer[i];
			break;
		}
	}

	if (buffer == 0)
	{
		OutputDebugStringW(L"Texture Buffer Pointer was Null");
		return;
	}
	DX11GraphicsEngine::Get()->GetCurrentDeviceContext()->setshadertexture(buffer->slot, buffer->textureview);

}



RAZPTR<ID3D10Blob> DX11Raz::RazShader::GetBuffer()
{
	return mv_buffer;
}

RAZPTR<ID3D10Blob> DX11Raz::RazShader::GetPBuffer()
{
	return mp_buffer;
}