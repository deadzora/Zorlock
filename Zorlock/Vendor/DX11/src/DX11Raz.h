#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <ZWindow.h>
#include <vector>

namespace DX11Raz
{



#ifdef ZL_DEBUG
	typedef bool (*DX11DebugCallback)(D3D11_MESSAGE_CATEGORY,D3D11_MESSAGE_SEVERITY,D3D11_MESSAGE_ID,const char*,SIZE_T);
#endif

	class DX11DeviceContext;
	class DX11SwapChain;

	class DX11GraphicsEngine
	{
	public:
		DX11GraphicsEngine() {};
		~DX11GraphicsEngine();
		bool Initialize();
		bool SetContext(HWND hwnd);
		bool SetContext(HWND hwnd, RECT rect);
		static DX11GraphicsEngine* Get();
		void Cls();
		void Cls(float r, float g, float b, float a);
		void Flip(bool vsync = false);
		void SetViewport(UINT x, UINT y, UINT width, UINT height);
		ID3D11Device* GetDevice();
		IDXGIFactory* GetFactory();
		ID3D11DeviceContext* GetContext();
		DX11SwapChain* CreateSwapChain();
#if defined(ZL_DEBUG)
		ID3D11Debug* DXEnableDebug(DX11DebugCallback func);
#endif
	private:
		bool intialized;
		RECT viewportsize;
		ID3D11Device* m_d3d_device;
		IDXGIDevice* m_dxgi_device;
		IDXGIAdapter* m_dxgi_adapter;
		IDXGIFactory* m_dxgi_factory;
		DX11SwapChain* m_swapchain;
		ID3D11Debug* m_d3dDebug;
		ID3D11DeviceContext* m_imm_context;
		ID3D11InfoQueue * d3dInfoQueue;
		D3D_FEATURE_LEVEL feature_level;
		DX11DebugCallback DebugCall;
		DX11DeviceContext* m_imm_device_context;
	};





}