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
		DX11GraphicsEngine::Get()->AddTexture(RAZPTR<RazTexture>(this));
	}

	RazTexture::RazTexture(const RAZPTR<DX11Color> colorData, UINT width, UINT height, aiTextureType type)
	{
		this->InitColorTexture(colorData, width, height, type);
		DX11GraphicsEngine::Get()->AddTexture(RAZPTR<RazTexture>(this));
	}

	RazTexture::RazTexture(const RAZPTR<DX11Color> colorData, UINT width, UINT height, UINT size, aiTextureType type)
	{
		this->InitColorTextureArray(colorData, width, height, size, type);
		DX11GraphicsEngine::Get()->AddTexture(RAZPTR<RazTexture>(this));
	}

	

	RazTexture::RazTexture(const wchar_t* filename, aiTextureType type)
	{
		if (RAZFILEEXISTS(filename))
		{
			if (RAZTEXTUREFILE(filename) == ".dds" || RAZTEXTUREFILE(filename) == ".DDS")
			{
				ID3D11ShaderResourceView* textview;
				HRESULT hr = DirectX::CreateDDSTextureFromFile(DX11GraphicsEngine::Get()->GetDevice().get(), DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext().get(), filename, nullptr, &textview);
				if (!SUCCEEDED(hr))
				{
					OutputDebugString(L"Failed to Load DDS Texture \r\n");
					//this->textureView->GetResource(&this->texture);
					
				}
				textureView = RAZPTR<ID3D11ShaderResourceView>(textview);
			}
			else
			{
				ID3D11ShaderResourceView* textview;
				HRESULT hr = DirectX::CreateWICTextureFromFile(DX11GraphicsEngine::Get()->GetDevice().get(), DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext().get(), filename, nullptr, &textview);

				if (!SUCCEEDED(hr))
				{
					OutputDebugString(L"Failed to Load Texture \r\n");
					//this->textureView->GetResource(&(texture.get()));
				}
				textureView = RAZPTR<ID3D11ShaderResourceView>(textview);
			}
			
			
		}
		else {
			textureView = 0;
			texture = 0;
			
		}

		DX11GraphicsEngine::Get()->AddTexture(RAZPTR<RazTexture>(this));


	}

	RazTexture::RazTexture(std::string filename, aiTextureType type)
	{
		if (RAZFILEEXISTS(filename))
		{
			if (RAZGETEXTENSION(filename) == ".dds" || RAZGETEXTENSION(filename) == ".DDS")
			{
				ID3D11ShaderResourceView* textview;
				HRESULT hr = DirectX::CreateDDSTextureFromFile(DX11GraphicsEngine::Get()->GetDevice().get(), DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext().get(), RAZTEXTUREFILEW(filename), nullptr, &textview);
				if (!SUCCEEDED(hr))
				{
					OutputDebugString(L"Failed to Load DDS Texture \r\n");
					
					//this->textureView->GetResource(&this->texture);
				}
				textureView = RAZPTR<ID3D11ShaderResourceView>(textview);
			}
			else
			{
				ID3D11ShaderResourceView* textview;
				HRESULT hr = DirectX::CreateWICTextureFromFile(DX11GraphicsEngine::Get()->GetDevice().get(), DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext().get(), RAZTEXTUREFILEW(filename), nullptr, &textview);

				if (!SUCCEEDED(hr))
				{
					OutputDebugString(L"Failed to Load Texture \r\n");
					//this->textureView->GetResource(&this->texture);
				}
				textureView = RAZPTR<ID3D11ShaderResourceView>(textview);
			}
			
		}
		else {
			textureView = 0;
			texture = nullptr;
		}

		DX11GraphicsEngine::Get()->AddTexture(RAZPTR<RazTexture>(this));


	}

	RazTexture::RazTexture(RAZPTR<ID3D11ShaderResourceView> textureView, aiTextureType type)
	{
		this->type = type;
		this->textureView = textureView;
		ID3D11Resource* text = texture.get();
		this->textureView->GetResource(&text);
		DX11GraphicsEngine::Get()->AddTexture(RAZPTR<RazTexture>(this));
	}

	RazTexture::RazTexture(const uint8_t* pData, size_t size, aiTextureType type)
	{
		this->type = type;
		//not thread safe, remove context for threading
		ID3D11ShaderResourceView* textview;
		ID3D11Resource* text;
		HRESULT hr = DirectX::CreateWICTextureFromMemory(DX11GraphicsEngine::Get()->GetDevice().get(), nullptr, pData, size, &text, &textview);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Texture \r\n");
			textureView = nullptr;
			texture = nullptr;
		}
		textureView = RAZPTR<ID3D11ShaderResourceView>(textview);
		texture = RAZPTR<ID3D11Resource>(text);
		DX11GraphicsEngine::Get()->AddTexture(RAZPTR<RazTexture>(this));
	}

	aiTextureType RazTexture::GetType()
	{
		return this->type;
	}

	RAZPTR<ID3D11Resource> RazTexture::GetTexture()
	{
		return this->texture;
	}

	RAZPTR<ID3D11ShaderResourceView> RazTexture::GetTextureView()
	{
		return this->textureView;
	}

	ID3D11ShaderResourceView** RazTexture::GetTextureAddress()
	{
		ID3D11ShaderResourceView* text = textureView.get();
		return &text;
	}

	void RazTexture::InsertTexture(RAZPTR<RazTexture> rtexture, UINT index)
	{
		D3D11_MAPPED_SUBRESOURCE init_data = {};
		HRESULT hr;
		hr = DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Map(rtexture->texture.get(), 0, D3D11_MAP_READ, 0, &init_data);
		if (FAILED(hr))
		{
			OutputDebugStringW(L"Could not read Texture Data");
			return;
		}
		DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Unmap(rtexture->texture.get(), 0);
		hr = DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Map(texture.get(), index, D3D11_MAP_WRITE, 0, &init_data);
		if (FAILED(hr))
		{
			OutputDebugStringW(L"Could not write Texture Data");
			return;
		}
		DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext()->Unmap(texture.get(), index);		
	}

	void RazTexture::Release()
	{
		if(textureView != nullptr) 
			textureView->Release();
		if (texture != nullptr) 
			texture->Release();
	}



	UINT RazTexture::GetByteSize(DXGI_FORMAT format)
	{
		switch (format)
		{
		case DXGI_FORMAT::DXGI_FORMAT_B4G4R4A4_UNORM:
		{
			return 2;
		}
		case DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_TYPELESS:
		case DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM:
		case DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_SINT:
		case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_SNORM:
		case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_TYPELESS:
		case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UINT:
		case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM:
		case DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		{
			return 4;
		}
		case DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_FLOAT:
		case DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_SINT:
		case DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_SNORM:
		case DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_TYPELESS:
		case DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_UINT:
		case DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_UNORM:
		{
			return 8;
		}
		case DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT:
		case DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_TYPELESS:
		case DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_UINT:
		{
			return 16;
		}
		case DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT:
		case DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT:
		case DXGI_FORMAT::DXGI_FORMAT_R32G32B32_TYPELESS:
		case DXGI_FORMAT::DXGI_FORMAT_R32G32B32_UINT:
		{
			return 12;
		}
		}

		return 0;
	}

	void RazTexture::Init1x1ColorTexture(const DX11Color& color, aiTextureType type)
	{
		this->InitColorTexture(RAZPTR<DX11Color>(new DX11Color(color)), 1, 1, type);
	}

	void RazTexture::InitColorTexture(const RAZPTR<DX11Color> colorData, UINT width, UINT height, aiTextureType type)
	{
		this->type = type;
		CD3D11_TEXTURE2D_DESC textureDesc(DXGI_FORMAT_R8G8B8A8_UNORM, width, height);
		ID3D11Texture2D* p2DTexture = nullptr;
		D3D11_SUBRESOURCE_DATA initData = {};

		initData.pSysMem = colorData.get();
		initData.SysMemPitch = width * 4;
		initData.SysMemSlicePitch = width * height * 4;
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateTexture2D(&textureDesc, &initData, &p2DTexture);
		if (FAILED(hr))
		{
			textureView = 0;
			texture = nullptr;
			OutputDebugString(L"Failed to Create Texture from Color \r\n");
		}
		texture = RAZPTR<ID3D11Resource>(static_cast<ID3D11Texture2D*>(p2DTexture));
		CD3D11_SHADER_RESOURCE_VIEW_DESC srcDesc(D3D11_SRV_DIMENSION_TEXTURE2D, textureDesc.Format);
		ID3D11ShaderResourceView* textview;
		hr = DX11GraphicsEngine::Get()->GetDevice()->CreateShaderResourceView(texture.get(), &srcDesc, &textview);
		if (FAILED(hr))
		{
			textureView = 0;
			texture = nullptr;
			OutputDebugString(L"Failed to Create Shader Resource from Color \r\n");
		}
		textureView = RAZPTR<ID3D11ShaderResourceView>(textview);
		Width = width;
		Height = height;
		Size = 4;
		Count = 1;


	}

	void RazTexture::InitColorTextureArray(const RAZPTR<DX11Color> colorData, UINT width, UINT height, UINT size, aiTextureType type)
	{

		this->type = type;
		CD3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.ArraySize = size;
		textureDesc.Usage = D3D11_USAGE_DYNAMIC;

		ID3D11Texture2D* p2DTexture = nullptr;
		D3D11_SUBRESOURCE_DATA* initData = new D3D11_SUBRESOURCE_DATA[size];
		DX11Color* col = colorData.get();
		for (size_t i = 0; i < size; i++)
		{
			//32 bits = 4 bytes
			initData->pSysMem = col;
			initData->SysMemPitch = width * 4;
			initData->SysMemSlicePitch = width * height * 4;
			col++;
			initData++;
		}
		
		//initData.SysMemPitch = sizeof(DX11Color);
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateTexture2D(&textureDesc, initData, &p2DTexture);
		if (FAILED(hr))
		{
			textureView = 0;
			texture = nullptr;
			OutputDebugString(L"Failed to Create Texture2d array  from Color \r\n");
		}
		texture = RAZPTR<ID3D11Resource>(static_cast<ID3D11Texture2D*>(p2DTexture));
		CD3D11_SHADER_RESOURCE_VIEW_DESC srcDesc(D3D11_SRV_DIMENSION_TEXTURE2DARRAY, textureDesc.Format,0,0,0,size);
		ID3D11ShaderResourceView* textview;
		hr = DX11GraphicsEngine::Get()->GetDevice()->CreateShaderResourceView(texture.get(), &srcDesc, &textview);
		if (FAILED(hr))
		{
			textureView = nullptr;
			texture = nullptr;
			OutputDebugString(L"Failed to Create Texture 2d Array Shader Resource from Color \r\n");
		}
		textureView = RAZPTR<ID3D11ShaderResourceView>(textview);
		Width = width;
		Height = height;
		Size = 4;
		Count = size;

	}

}