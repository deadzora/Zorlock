#pragma once
#include "DX11Raz.h"

namespace DX11Raz
{
	class DX11SwapChain;

	class DX11DeviceContext
	{
	public:
		DX11DeviceContext(ID3D11DeviceContext* device_context);
		void clearRenderTargetColor(DX11SwapChain* swap_chain, float r, float g, float b, float a);
		void setviewportsize(UINT width, UINT height);
		bool createblendstate();
		void setblendstate();
		bool setstencilstate();
		bool setsamplerstate();
		bool setstencilbuffer();
		bool release();
		ID3D11DeviceContext* GetContext();
		~DX11DeviceContext();
		UINT width;
		UINT height;
	private:
		bool initialized;
		ID3D11BlendState* m_bs;
		ID3D11DeviceContext* m_device_context;
		ID3D11DepthStencilView* m_depth_stencilview;
		ID3D11Texture2D* m_depth_stecil_buffer;
		ID3D11DepthStencilState* m_depth_stencilstate;
		ID3D11SamplerState* m_sampler_state;
		ID3D11ShaderResourceView* m_texture;

	};




}