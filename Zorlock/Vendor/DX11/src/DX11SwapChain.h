#pragma once
#include <d3d11.h>


namespace ZorlockDX11
{

	class DX11DeviceContext;


	class DX11SwapChain
	{
	public:
		DX11SwapChain();
		bool init(HWND hwnd, UINT width, UINT height);
		bool flip(bool vsync);
		bool release();
		ID3D11RenderTargetView* GetRenderTargetView();
		~DX11SwapChain();
	private:
		IDXGISwapChain* m_swapchain;
		ID3D11RenderTargetView* m_rtv;
		friend class DX11DeviceContext;
	};
}