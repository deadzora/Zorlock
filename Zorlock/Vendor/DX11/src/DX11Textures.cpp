#include "ZLpch.h"
#include "DX11Textures.h"
#include "DX11Raz.h"
#include "DX11DeviceContext.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

namespace DX11Raz
{
	DX11Color::DX11Color(BYTE r, BYTE g, BYTE b) : DX11Color(r, g, b, 255)
	{

	}

	DX11Color::DX11Color(BYTE r, BYTE g, BYTE b, BYTE a)
	{
		rgba[0] = r;
		rgba[1] = g;
		rgba[2] = b;
		rgba[3] = a;
	}




	RazTexture::RazTexture(const DX11Color& color, aiTextureType type)
	{
		this->Init1x1ColorTexture(color, type);
		DX11GraphicsEngine::Get()->AddTexture(this);
	}

	RazTexture::RazTexture(const DX11Color* colorData, UINT width, UINT height, aiTextureType type)
	{
		this->InitColorTexture(colorData, width, height, type);
		DX11GraphicsEngine::Get()->AddTexture(this);
	}

	RazTexture::RazTexture(const DX11Color* colorData, UINT width, UINT height, UINT size, aiTextureType type)
	{
		this->InitColorTextureArray(colorData, width, height, size, type);
		DX11GraphicsEngine::Get()->AddTexture(this);
	}

	RazTexture::RazTexture(const wchar_t* filename, aiTextureType type)
	{
		if (RAZFILEEXISTS(filename))
		{
			if (RAZTEXTUREFILE(filename) == ".dds" || RAZTEXTUREFILE(filename) == ".DDS")
			{
				HRESULT hr = DirectX::CreateDDSTextureFromFile(DX11GraphicsEngine::Get()->GetDevice(), DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext(), filename, nullptr, &textureView);
				if (!SUCCEEDED(hr))
				{
					OutputDebugString(L"Failed to Load DDS Texture \r\n");
					this->textureView->GetResource(&this->texture);
					
				}
			}
			else
			{
				HRESULT hr = DirectX::CreateWICTextureFromFile(DX11GraphicsEngine::Get()->GetDevice(), DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext(), filename, nullptr, &textureView);

				if (!SUCCEEDED(hr))
				{
					OutputDebugString(L"Failed to Load Texture \r\n");
					this->textureView->GetResource(&this->texture);
				}
			}
			
			
		}
		else {
			textureView = 0;
			texture = 0;
			
		}

		DX11GraphicsEngine::Get()->AddTexture(this);


	}

	RazTexture::RazTexture(std::string filename, aiTextureType type)
	{
		if (RAZFILEEXISTS(filename))
		{
			if (RAZGETEXTENSION(filename) == ".dds" || RAZGETEXTENSION(filename) == ".DDS")
			{
				HRESULT hr = DirectX::CreateDDSTextureFromFile(DX11GraphicsEngine::Get()->GetDevice(), DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext(), RAZTEXTUREFILEW(filename), nullptr, &textureView);
				if (!SUCCEEDED(hr))
				{
					OutputDebugString(L"Failed to Load DDS Texture \r\n");
					
					this->textureView->GetResource(&this->texture);
				}
			}
			else
			{
				HRESULT hr = DirectX::CreateWICTextureFromFile(DX11GraphicsEngine::Get()->GetDevice(), DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext(), RAZTEXTUREFILEW(filename), nullptr, &textureView);

				if (!SUCCEEDED(hr))
				{
					OutputDebugString(L"Failed to Load Texture \r\n");
					this->textureView->GetResource(&this->texture);
				}
			}
			
		}
		else {
			textureView = 0;
			texture = 0;
		}

		DX11GraphicsEngine::Get()->AddTexture(this);


	}

	RazTexture::RazTexture(ID3D11ShaderResourceView* textureView, aiTextureType type)
	{
		this->type = type;
		this->textureView = textureView;
		this->textureView->GetResource(&this->texture);
		DX11GraphicsEngine::Get()->AddTexture(this);
	}

	RazTexture::RazTexture(const uint8_t* pData, size_t size, aiTextureType type)
	{
		this->type = type;
		//not thread safe, remove context for threading
		HRESULT hr = DirectX::CreateWICTextureFromMemory(DX11GraphicsEngine::Get()->GetDevice(), nullptr, pData, size, &texture, &textureView);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Texture \r\n");
			textureView = 0;
			texture = 0;
		}

		DX11GraphicsEngine::Get()->AddTexture(this);
	}

	aiTextureType RazTexture::GetType()
	{
		return this->type;
	}

	ID3D11ShaderResourceView* RazTexture::GetTexture()
	{
		return this->textureView;
	}

	ID3D11ShaderResourceView** RazTexture::GetTextureAddress()
	{
		return &this->textureView;
	}

	void RazTexture::Release()
	{
		if(textureView != 0) textureView->Release();
		if (texture != 0) texture->Release();
	}

	RazTexture::~RazTexture()
	{
	}

	void RazTexture::Init1x1ColorTexture(const DX11Color& color, aiTextureType type)
	{
		this->InitColorTexture(&color, 1, 1, type);
	}

	void RazTexture::InitColorTexture(const DX11Color* colorData, UINT width, UINT height, aiTextureType type)
	{
		this->type = type;
		CD3D11_TEXTURE2D_DESC textureDesc(DXGI_FORMAT_R8G8B8A8_UNORM, width, height);
		ID3D11Texture2D* p2DTexture = nullptr;
		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = colorData;
		initData.SysMemPitch = sizeof(DX11Color);
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateTexture2D(&textureDesc, &initData, &p2DTexture);
		if (FAILED(hr))
		{
			textureView = 0;
			texture = 0;
			OutputDebugString(L"Failed to Create Texture from Color \r\n");
		}
		texture = static_cast<ID3D11Texture2D*>(p2DTexture);
		CD3D11_SHADER_RESOURCE_VIEW_DESC srcDesc(D3D11_SRV_DIMENSION_TEXTURE2D, textureDesc.Format);
		hr = DX11GraphicsEngine::Get()->GetDevice()->CreateShaderResourceView(texture, &srcDesc, &textureView);
		if (FAILED(hr))
		{
			textureView = 0;
			texture = 0;
			OutputDebugString(L"Failed to Create Shader Resource from Color \r\n");
		}
	}

	void RazTexture::InitColorTextureArray(const DX11Color* colorData, UINT width, UINT height, UINT size, aiTextureType type)
	{
		this->type = type;
		CD3D11_TEXTURE2D_DESC textureDesc(DXGI_FORMAT_R8G8B8A8_UNORM, width, height,size);

		ID3D11Texture2D* p2DTexture = nullptr;
		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = colorData;
		//initData.SysMemPitch = sizeof(DX11Color);
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateTexture2D(&textureDesc, &initData, &p2DTexture);
		if (FAILED(hr))
		{
			textureView = 0;
			texture = 0;
			OutputDebugString(L"Failed to Create Texture2d array  from Color \r\n");
		}
		texture = static_cast<ID3D11Texture2D*>(p2DTexture);
		CD3D11_SHADER_RESOURCE_VIEW_DESC srcDesc(D3D11_SRV_DIMENSION_TEXTURE2DARRAY, textureDesc.Format,0,0,0,size);
		hr = DX11GraphicsEngine::Get()->GetDevice()->CreateShaderResourceView(texture, &srcDesc, &textureView);
		if (FAILED(hr))
		{
			textureView = 0;
			texture = 0;
			OutputDebugString(L"Failed to Create Texture 2d Array Shader Resource from Color \r\n");
		}
	}

}