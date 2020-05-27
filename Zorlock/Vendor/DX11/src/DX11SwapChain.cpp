#include "ZLpch.h"
#include "DX11SwapChain.h"

namespace DX11Raz
{
	DX11SwapChain::DX11SwapChain() : m_rtv(0), m_swapchain(0)
	{
		DX11GraphicsEngine::Get()->AddSwapChain(this);
	}

	bool DX11SwapChain::init(HWND hwnd, UINT width, UINT height)
	{
		ID3D11Device* device = DX11GraphicsEngine::Get()->GetDevice();
		UINT samples;
		HRESULT hr = device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT, &samples);


		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BufferCount = 1;
		desc.BufferDesc.Width = width;
		desc.BufferDesc.Height = height;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = hwnd;
		desc.SampleDesc.Count = 4;
		desc.SampleDesc.Quality = samples-1;
		desc.Windowed = TRUE;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		hr = DX11GraphicsEngine::Get()->GetFactory()->CreateSwapChain(device, &desc, &m_swapchain);

		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Swap Chain. Possible missing context\r\n");
			ZL_CORE_ASSERT(1,"Failed to Create Swap Chain. Possible missing context");
			return false;
		}
		ID3D11Texture2D* buffer = NULL;
		hr = m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Swap Chain Buffer\r\n");
			ZL_CORE_ASSERT(1, "Failed to Create Swap Chain Buffer");
			return false;
		}

		hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
		buffer->Release();


		if (FAILED(hr))
		{
			OutputDebugString(L"Swap Chain Buffer Invalid\r\n");
			ZL_CORE_ASSERT(1, "Swap Chain Buffer Invalid");
			return false;
		}

		return true;
	}

	bool DX11SwapChain::flip(bool vsync)
	{
		m_swapchain->Present(vsync, NULL);
		return true;
	}

	bool DX11SwapChain::Release()
	{
		if (&m_rtv != NULL)
		{
			//m_rtv->Release();
		}
		if (m_swapchain != NULL)
		{
			//m_swapchain->Release();
		}
		//m_swapchain->Release();
		//delete this;
		return true;
	}


	ID3D11RenderTargetView* DX11SwapChain::GetRenderTargetView()
	{
		return m_rtv;
	}

	DX11SwapChain::~DX11SwapChain()
	{
	}


}