#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <ZWindow.h>
#include <vector>
#include <filesystem>

namespace DX11Raz
{
#define RAZGETEXTENSION(f) f.substr(f.find_last_of(".") + 1)
#define RAZFILEEXISTS(f) std::filesystem::exists(f)

#ifndef D3D_COMPILE_STANDARD_FILE_INCLUDE
#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)
#endif

#ifdef ZL_DEBUG
	typedef bool (*DX11DebugCallback)(void* pInfoQueue);
#define PID3D11InfoQueue(p) static_cast<ID3D11InfoQueue*>(p);
#endif

	class DX11DeviceContext;
	class DX11SwapChain;
	class RazVertexBuffer;
	class RazIndexBuffer;
	class RazShader;
	//we need to be able to handle multiple contexts at once, so we need to push our device data to a new class

	bool RazDX11Initialize();
	bool RazDX11Release();
	void RazDX11CreateContext(ZWindow* zhandle);
	void RazSetCLSColor(DX11DeviceContext* dhandle, float r, float g, float b, float a);
	void RazCLS(DX11DeviceContext* dhandle);
	void RazSetViewport(UINT width, UINT height);
	RazVertexBuffer* RazCreateVertexBuffer();
	void RazDeleteVertexBuffer(RazVertexBuffer* v);
	RazIndexBuffer * RazCreateIndexBuffer();
	void RazDeleteIndexBuffer(RazIndexBuffer* i);
	RazShader* RazCreateShader();
	void RazDeleteShader(RazShader * shader);


	class DX11GraphicsEngine
	{
	public:
		DX11GraphicsEngine() {};
		~DX11GraphicsEngine();
		bool Initialize();
		bool enabled;
		void Release();
		//bool SetContext(HWND hwnd, RECT rect);
	public:
		static DX11GraphicsEngine* Get();
	public:
		void Cls();
		void Cls(float r, float g, float b, float a);
		void Flip(bool vsync = false);
		void SetViewport(UINT x, UINT y, UINT width, UINT height);
		ID3D11Device* GetDevice();
		IDXGIFactory* GetFactory();
		DX11DeviceContext* GetImmediateDeviceContext();
		//ID3D11DeviceContext* GetContext();
		DX11SwapChain* CreateSwapChain();
#if defined(ZL_DEBUG)
		//ID3D11Debug* DXEnableDebug(DX11DebugCallback func);
#endif
	private:
		bool intialized;

		ID3D11Device* m_d3d_device;
		IDXGIDevice* m_dxgi_device;
		IDXGIAdapter* m_dxgi_adapter;
		IDXGIFactory* m_dxgi_factory;
		ID3D11InfoQueue* d3dInfoQueue;
		D3D_FEATURE_LEVEL feature_level;

		ID3D11DeviceContext* m_imm_context;
		//DX11SwapChain* m_swapchain;
		ID3D11Debug* m_d3dDebug;
		

		DX11DebugCallback DebugCall;
		//main context
		DX11DeviceContext* m_imm_device_context;
	};

	




}