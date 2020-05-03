#include "Texture.h"
#include "ErrorLogger.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "WICTextureLoader.h"



Texture::Texture(const Color & color, aiTextureType type)
{
	this->Init1x1ColorTexture(color, type);
}

Texture::Texture(const Color * colorData, UINT width, UINT height, aiTextureType type)
{
	this->InitColorTexture(colorData, width, height, type);
}

Texture::Texture(const wchar_t * filename, aiTextureType type)
{
	this->type = type;
	textureView = GraphicsEngine::get()->loadtexture(filename);
	if (textureView)
	{
		textureView->GetResource(&this->texture);
	}
	else {

	}
	
}

Texture::Texture(ID3D11ShaderResourceView * textureView, aiTextureType type)
{
	this->type = type;
	this->textureView = textureView;
	this->textureView->GetResource(&this->texture);
}

Texture::Texture(const uint8_t * pData, size_t size, aiTextureType type)
{
	this->type = type;
	//not thread safe, remove context for threading
	HRESULT hr = DirectX::CreateWICTextureFromMemory(GraphicsEngine::get()->getdevice(), nullptr, pData, size, &texture, &textureView);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Texture from Memory");
	}
}

aiTextureType Texture::GetType()
{
	return this->type;
}

ID3D11ShaderResourceView * Texture::GetTexture()
{
	return this->textureView;
}

ID3D11ShaderResourceView ** Texture::GetTextureAddress()
{
	return &this->textureView;
}

void Texture::Release()
{
	//if (this->texture)this->texture->Release();
	//if (this->textureView)this->textureView->Release();
}

Texture::~Texture()
{
	//this->Release();
	//delete this;
}

void Texture::Init1x1ColorTexture(const Color & color, aiTextureType type)
{
	this->InitColorTexture(&color, 1, 1, type);
}

void Texture::InitColorTexture(const Color * colorData, UINT width, UINT height, aiTextureType type)
{
	this->type = type;
	CD3D11_TEXTURE2D_DESC textureDesc(DXGI_FORMAT_R8G8B8A8_UNORM, width, height);
	ID3D11Texture2D * p2DTexture = nullptr;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = colorData;
	initData.SysMemPitch = sizeof(Color);
	HRESULT hr = GraphicsEngine::get()->getdevice()->CreateTexture2D(&textureDesc, &initData, &p2DTexture);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Initialize Texture from color");
	}
	texture = static_cast<ID3D11Texture2D*>(p2DTexture);
	CD3D11_SHADER_RESOURCE_VIEW_DESC srcDesc(D3D11_SRV_DIMENSION_TEXTURE2D, textureDesc.Format);
	hr = GraphicsEngine::get()->getdevice()->CreateShaderResourceView(texture, &srcDesc, &textureView);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Shader Resource View from Texture");
	}
}
