#pragma once
#include "DX11Raz.h"

namespace DX11Raz
{

	class DX11DeviceContext;


	class DX11SwapChain
	{
	public:
		DX11SwapChain();
		bool init(HWND hwnd, UINT width, UINT height);
		bool flip(bool vsync);
		bool Release();
		bool SetViewport(HWND hwnd, UINT width, UINT height);

		RAZPTR<ID3D11RenderTargetView> GetRenderTargetView();
		~DX11SwapChain();
	private:
		RAZPTR<IDXGISwapChain> m_swapchain;
		RAZPTR<ID3D11RenderTargetView> m_rtv;
		friend class DX11DeviceContext;
	};

}