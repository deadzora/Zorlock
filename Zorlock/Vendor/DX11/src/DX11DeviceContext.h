#pragma once
#include "DX11Raz.h"

namespace DX11Raz
{
	class DX11SwapChain;

	class DX11DeviceContext
	{
	public:
		DX11DeviceContext(RAZPTR<ID3D11DeviceContext> device_context);
		void Init(RAZPTR<ZWindow> zhandle);
		void Flip(bool vsync);
		void clearRenderTarget();
		void clearRenderTargetColor(float r, float g, float b, float a);
		void setviewportsize(UINT width, UINT height);
		bool createblendstate();
		void setblendstate();
		bool setstencilstate();
		bool setsamplerstate();
		bool setstencilbuffer();
		bool setrasterizer();
		void setvertexshader(RAZPTR<RazShader> vertex_shader);
		void setpixelshader(RAZPTR<RazShader> pixel_shader);
		void setvertexbuffer(RAZPTR<RazVertexBuffer> vertex_buffer);
		void setindexbuffer(RAZPTR<RazIndexBuffer> index_buffer);
		void drawIndexed(UINT index_count, UINT start_vertex_index, UINT base_vertex_location);
		void setshadertexture(UINT slot, RAZPTR<ID3D11ShaderResourceView> texture);
		void setshadertexture(RAZPTR<ID3D11ShaderResourceView> texture);
		void setshadertextures(RAZPTR<ID3D11ShaderResourceView> texture, UINT arraysize);
		void setshadertextures(UINT slot, RAZPTR<ID3D11ShaderResourceView> texture, UINT arraysize);
		bool Release();
		bool MainRelease();
		RAZPTR<DX11SwapChain> GetSwapChain();
		RAZPTR<ID3D11DeviceContext> GetContext();
		~DX11DeviceContext();
		UINT width;
		UINT height;
	private:
		bool initialized;
		RAZPTR<ID3D11BlendState> m_bs;
		RAZPTR<ID3D11DeviceContext> m_device_context;
		RAZPTR<ID3D11DepthStencilView> m_depth_stencilview;
		RAZPTR<ID3D11Texture2D> m_depth_stecil_buffer;
		RAZPTR<ID3D11DepthStencilState> m_depth_stencilstate;
		RAZPTR<ID3D11SamplerState> m_sampler_state;
		RAZPTR<ID3D11RasterizerState> m_pRasterState;
		//ID3D11ShaderResourceView* m_texture;
		RAZPTR<DX11SwapChain> m_contextswapchain;
		RAZPTR<ZWindow> m_contextContainer;

		//temporary color struct
		struct ZColor
		{
			float r, g, b, a;
		};
		ZColor dcolor;

	};




}