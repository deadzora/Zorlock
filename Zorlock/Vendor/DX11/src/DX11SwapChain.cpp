#include "ZLpch.h"
#include "DX11SwapChain.h"
#include "DX11Graphics.h"

namespace ZorlockDX11
{
	DX11SwapChain::DX11SwapChain() : m_rtv(nullptr), m_swapchain(nullptr)
	{
	}

	bool DX11SwapChain::init(HWND hwnd, UINT width, UINT height)
	{
		ID3D11Device* device = DX11GraphicsEngine::get()->GetD3D11Device();

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
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Windowed = TRUE;

		HRESULT hr = DX11GraphicsEngine::get()->GetDXG11Factory()->CreateSwapChain(device, &desc, &m_swapchain);

		if (FAILED(hr))
		{			
			return false;
		}
		ID3D11Texture2D* buffer = NULL;
		hr = m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
		if (FAILED(hr))
		{
			return false;
		}

		hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
		buffer->Release();


		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}

	bool DX11SwapChain::flip(bool vsync)
	{
		m_swapchain->Present(vsync, NULL);
		return true;
	}

	bool DX11SwapChain::release()
	{
		m_swapchain->Release();
		delete this;
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
