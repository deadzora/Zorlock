#include "ZLpch.h"
#include "DX11SwapChain.h"

namespace DX11Raz
{
	DX11SwapChain::DX11SwapChain() : m_rtv(0), m_swapchain(0)
	{
		DX11GraphicsEngine::Get()->AddSwapChain(RAZPTR<DX11SwapChain>(this));
	}

	bool DX11SwapChain::init(HWND hwnd, UINT width, UINT height)
	{
		ID3D11Device* device = DX11GraphicsEngine::Get()->GetDevice().get();
		UINT samples;
		HRESULT hr = device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT, &samples);


		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BufferCount = 2;
		desc.BufferDesc.Width = width;
		desc.BufferDesc.Height = height;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.RefreshRate.Numerator = 144;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = hwnd;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Windowed = TRUE;
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		//desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		IDXGISwapChain* sc;
		hr = DX11GraphicsEngine::Get()->GetFactory()->CreateSwapChain(device, &desc, &sc);

		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Swap Chain. Possible missing context\r\n");
			ZL_CORE_ASSERT(1,"Failed to Create Swap Chain. Possible missing context");
			return false;
		}
		m_swapchain = RAZPTR<IDXGISwapChain>(sc);
		ID3D11Texture2D* buffer = NULL;
		hr = m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Swap Chain Buffer\r\n");
			ZL_CORE_ASSERT(1, "Failed to Create Swap Chain Buffer");
			return false;
		}
		ID3D11RenderTargetView* rtv;
		hr = device->CreateRenderTargetView(buffer, NULL, &rtv);
		buffer->Release();


		if (FAILED(hr))
		{
			OutputDebugString(L"Swap Chain Buffer Invalid\r\n");
			ZL_CORE_ASSERT(1, "Swap Chain Buffer Invalid");
			return false;
		}
		m_rtv = RAZPTR<ID3D11RenderTargetView>(rtv);
		return true;
	}

	bool DX11SwapChain::flip(bool vsync)
	{
		m_swapchain->Present(false, NULL);
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

	bool DX11SwapChain::SetViewport(HWND hwnd, UINT width, UINT height)
	{
		DXGI_MODE_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = width;
		desc.Height = height;
		desc.RefreshRate.Denominator = 1;
		desc.RefreshRate.Numerator = 144;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		HRESULT hr = m_swapchain->ResizeTarget(&desc);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Resize Swap Chain. Possible missing context\r\n");
			ZL_CORE_ASSERT(1, "Failed to Resize Swap Chain. Possible missing context");
			return false;
		}
		return true;
	}


	RAZPTR<ID3D11RenderTargetView> DX11SwapChain::GetRenderTargetView()
	{
		return m_rtv;
	}

	DX11SwapChain::~DX11SwapChain()
	{
	}


}