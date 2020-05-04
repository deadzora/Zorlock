#pragma once
#include <d3d11.h>

namespace ZorlockDX11
{

	class DX11DeviceContext
	{
	public:
		DX11DeviceContext(ID3D11DeviceContext* device_context);
		void clearRenderTargetColor(DX11SwapChain* swap_chain, float r, float g, float b, float a);
		void setviewportsize(int width, int height);
		bool createblendstate();
		void setblendstate();
		bool setstencilstate();
		bool setsamplerstate();
		bool setstencilbuffer();
		bool release();
		ID3D11DeviceContext* GetContext();
		~DX11DeviceContext();
		int width = 0;
		int height = 0;
	private:
		ID3D11BlendState* m_bs = nullptr;
		ID3D11DeviceContext* m_device_context = nullptr;
		ID3D11DepthStencilView* m_depth_stencilview = nullptr;
		ID3D11Texture2D* m_depth_stecil_buffer = nullptr;
		ID3D11DepthStencilState* m_depth_stencilstate = nullptr;
		ID3D11SamplerState* m_sampler_state = nullptr;
		ID3D11ShaderResourceView* m_texture = nullptr;

	};




}