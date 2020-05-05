#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>

namespace ZorlockDX11
{
	

	class DX11DeviceContext;
	class DX11SwapChain;
	class DirectX11VertexArray;

	class DX11GraphicsEngine
	{
	public:
		DX11GraphicsEngine() {};
		void Init(HWND hwnd, RECT rect);
		~DX11GraphicsEngine();
		//Static Path to Graphics Engine
		static DX11GraphicsEngine* get();
		//Main Graphics Engine Functions
		void Cls();
		void Cls(float r, float g, float b, float a);
		void Flip(bool vsync = false);	
		void UpdateWorld();
		void RenderWorld();
		bool Release();
		//DX11API Functions
		DX11SwapChain* CreateDX11SwapChain();
		bool SetWorldMatrix(float translate[], float scale[], float rotation[]);
		bool SetWorldMatrix();
		bool SetProjectionMatrix();
		//DX API Returns
		ID3D11Device* GetD3D11Device();
		IDXGIFactory* GetDXG11Factory();
		DX11DeviceContext* GetDX11DeviceContext();
		bool DX11GraphicsEngine::CreateContext();
		//DX API Create
		DirectX11VertexArray* DX11CreateVertexArray();
		void DX11DeleteVertexArray(DirectX11VertexArray* v);
		//DX API Set
		void DX11AddVertexArray(unsigned int i) {};
	private:
		//DX11API classes
		DX11SwapChain* m_swapchain;
		//DX11 classes
		IDXGIDevice* m_dxgi_device;
		IDXGIAdapter* m_dxgi_adapter;
		IDXGIFactory* m_dxgi_factory;
		ID3D11DeviceContext* m_imm_context;
		DX11DeviceContext* m_imm_device_context;
		ID3D11Device* m_d3d_device;
		D3D_FEATURE_LEVEL feature_level;
		DirectX::XMMATRIX WorldMatrix;
		DirectX::XMMATRIX ProjectionMatrix;
		//move this when we create camera class
		DirectX::XMMATRIX View;

		//Renderable Stuff
		std::vector<DirectX11VertexArray*> vertexArrays;


	};


	enum LIGHTTYPE
	{
		POINT,
		SPOT,
		DIRECTIONAL
	};
}