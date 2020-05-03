#pragma once
#include <d3d11.h>


class DeviceContext;


class SwapChain
{
public:
	SwapChain();
	bool init(HWND hwnd, UINT width, UINT height);
	bool flip(bool vsync);
	bool release();
	~SwapChain();
private:
	IDXGISwapChain* m_swapchain;
	ID3D11RenderTargetView* m_rtv;
	friend class DeviceContext;
};

