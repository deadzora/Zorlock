#include "ZLpch.h"
#include "DX11DeviceContext.h"
#include "DX11SwapChain.h"
#include "DX11VBuffer.h"
#include "DX11IBuffer.h"
#include "DX11Shaders.h"

namespace DX11Raz
{

	DX11DeviceContext::DX11DeviceContext(RAZPTR<ID3D11DeviceContext> device_context) :m_device_context(device_context)
	{

		m_bs = nullptr;
		m_depth_stencilview = nullptr;
		m_depth_stecil_buffer = nullptr;
		m_depth_stencilstate = nullptr;
		m_sampler_state = nullptr;
		m_pRasterState = nullptr;
	}

	void DX11DeviceContext::Init(RAZPTR<ZWindow> zhandle)
	{
		m_contextContainer = zhandle;
		m_contextswapchain = CreateZRef<DX11SwapChain>();
		m_contextswapchain->init(zhandle->GetHWND(), zhandle->GetWidth(), zhandle->GetHeight());
		setviewportsize(zhandle->GetWidth(), zhandle->GetHeight());
		createblendstate();
		initialized = true;
	}

	void DX11DeviceContext::Flip(bool vsync)
	{		
		m_contextswapchain->flip(vsync);
	}

	void DX11DeviceContext::clearRenderTarget()
	{
		clearRenderTargetColor(dcolor.r, dcolor.g, dcolor.b, dcolor.a);
	}

	void DX11DeviceContext::clearRenderTargetColor(float r, float g, float b, float a)
	{
		dcolor.r = r;
		dcolor.g = g;
		dcolor.b = b;
		dcolor.a = a;
		FLOAT clear_color[] = { r,g,b,a };
		m_device_context->ClearRenderTargetView(m_contextswapchain->m_rtv.get(), clear_color);
		m_device_context->ClearDepthStencilView(m_depth_stencilview.get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		ID3D11RenderTargetView* rtv = m_contextswapchain->m_rtv.get();
		m_device_context->OMSetRenderTargets(1, &rtv, m_depth_stencilview.get());
		m_device_context->OMSetDepthStencilState(m_depth_stencilstate.get(), 0);
		m_device_context->RSSetState(m_pRasterState.get());
		ID3D11SamplerState* samplerst = m_sampler_state.get();
		m_device_context->PSSetSamplers(0, 1, &samplerst);
		//create depth stencil state
		m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void DX11DeviceContext::setviewportsize(UINT width, UINT height)
	{

		
		D3D11_VIEWPORT vp = {};
		vp.Width = width;
		vp.Height = height;
		vp.MinDepth = 0.0;
		vp.MaxDepth = 1.0;
		this->width = width;
		this->height = height;
		m_device_context->RSSetViewports(1, &vp);

		if (!setrasterizer())
		{
			//log the error
		}

		if (!setstencilbuffer())
		{
			//log the error
		}

		if (!setstencilstate())
		{
			//log the error
		}
		if (!setsamplerstate())
		{
			//log the error
		}

		
	}

	bool DX11DeviceContext::createblendstate()
	{
		//create blend state - move to class to handle this
		D3D11_BLEND_DESC blendDesc = {};
		D3D11_RENDER_TARGET_BLEND_DESC rtbd = {};
		//ZeroMemory(&rtbd, sizeof(rtbd));
		rtbd.BlendEnable = true;
		rtbd.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		rtbd.DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		rtbd.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		rtbd.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		rtbd.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		rtbd.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

		blendDesc.RenderTarget[0] = rtbd;
		ID3D11BlendState* bs;
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBlendState(&blendDesc, &bs);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Blend State\r\n");
			return false;
		}
		m_bs = RAZPTR<ID3D11BlendState>(bs);
		setblendstate();
		return true;
	}

	void DX11DeviceContext::setblendstate()
	{

			m_device_context->OMSetBlendState(m_bs.get(), NULL, 0xFFFFFFFF);
		

	}

	bool DX11DeviceContext::setstencilstate()
	{
		D3D11_DEPTH_STENCIL_DESC depthstencildesc;
		ZeroMemory(&depthstencildesc, sizeof(depthstencildesc));
		depthstencildesc.DepthEnable = true;
		depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		ID3D11DepthStencilState* depthsten;
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateDepthStencilState(&depthstencildesc, &depthsten);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Depth Stencil State\r\n");
			ZL_CORE_INFO("Failed to Create Depth Stencil State");
			return false;
		}
		m_depth_stencilstate = RAZPTR<ID3D11DepthStencilState>(depthsten);

		return true;
	}

	bool DX11DeviceContext::setsamplerstate()
	{
		D3D11_SAMPLER_DESC sampler_desc;
		ZeroMemory(&sampler_desc, sizeof(sampler_desc));
		sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampler_desc.MinLOD = 0;
		sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
		ID3D11SamplerState* samplestate;
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateSamplerState(&sampler_desc, &samplestate);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Sampler State\r\n");
			ZL_CORE_INFO("Failed to Create Sampler State");
			return false;
		}
		m_sampler_state = RAZPTR<ID3D11SamplerState>(samplestate);
		return true;
	}

	bool DX11DeviceContext::setstencilbuffer()
	{
		UINT samples;
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT, &samples);

		D3D11_TEXTURE2D_DESC depthstencildesc;
		ZeroMemory(&depthstencildesc, sizeof(depthstencildesc));
		depthstencildesc.Width = width;
		depthstencildesc.Height = height;
		depthstencildesc.MipLevels = 1;
		depthstencildesc.ArraySize = 1;
		depthstencildesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthstencildesc.SampleDesc.Count = 1;
		depthstencildesc.SampleDesc.Quality = 0;
		depthstencildesc.Usage = D3D11_USAGE_DEFAULT;
		depthstencildesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthstencildesc.CPUAccessFlags = 0;
		depthstencildesc.MiscFlags = 0;
		ID3D11Texture2D* tex;
		hr = DX11GraphicsEngine::Get()->GetDevice()->CreateTexture2D(&depthstencildesc, NULL, &tex);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Depth Surface\r\n");
			ZL_CORE_INFO("Failed to Create Depth Surface");
			return false;
		}
		m_depth_stecil_buffer = RAZPTR<ID3D11Texture2D>(tex);
		D3D11_DEPTH_STENCIL_VIEW_DESC depthdetencilviewdesc;
		ZeroMemory(&depthdetencilviewdesc, sizeof(depthdetencilviewdesc));
		depthdetencilviewdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		depthdetencilviewdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		ID3D11DepthStencilView* stenview;
		hr = DX11GraphicsEngine::Get()->GetDevice()->CreateDepthStencilView(m_depth_stecil_buffer.get(), &depthdetencilviewdesc, &stenview);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Depth Stencil View\r\n");
			ZL_CORE_INFO("Failed to Depth Stencil View");
			return false;
		}
		m_depth_stencilview = RAZPTR<ID3D11DepthStencilView>(stenview);

		return true;
	}

	bool DX11DeviceContext::setrasterizer()
	{
		CD3D11_RASTERIZER_DESC rasterDesc(D3D11_FILL_SOLID, D3D11_CULL_BACK,
			TRUE /* FrontCounterClockwise */,
			D3D11_DEFAULT_DEPTH_BIAS,
			D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
			D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
			TRUE /* DepthClipEnable */,
			FALSE /* ScissorEnable */,
			TRUE /* MultisampleEnable */,
			TRUE /* AntialiasedLineEnable */);
		ID3D11RasterizerState* rasterstate;
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateRasterizerState(&rasterDesc, &rasterstate);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Rasterizer \r\n");
			ZL_CORE_INFO("Failed to Create Rasterizer");
			return false;
		}
		m_pRasterState = RAZPTR<ID3D11RasterizerState>(rasterstate);
	}

	void DX11DeviceContext::setvertexshader(RAZPTR<RazShader> vertex_shader)
	{
		m_device_context->VSSetShader(vertex_shader->m_vs.get(), nullptr, 0);
	}

	void DX11DeviceContext::setpixelshader(RAZPTR<RazShader> pixel_shader)
	{
		m_device_context->PSSetShader(pixel_shader->m_ps.get(), nullptr, 0);
	}

	void DX11DeviceContext::setvertexbuffer(RAZPTR<RazVertexBuffer> vertex_buffer)
	{		
		UINT offset = 0;
		ID3D11Buffer* buff = vertex_buffer->m_buffer.get();
		m_device_context->IASetVertexBuffers(0, 1, &buff, &vertex_buffer->stride, &offset);
		m_device_context->IASetInputLayout(vertex_buffer->m_layout.get());
	}

	void DX11DeviceContext::setindexbuffer(RAZPTR<RazIndexBuffer> index_buffer)
	{
		m_device_context->IASetIndexBuffer(index_buffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
		m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void DX11DeviceContext::drawIndexed(UINT index_count, UINT start_vertex_index, UINT base_vertex_location)
	{
		
		m_device_context->DrawIndexed(index_count, start_vertex_index, base_vertex_location);
	}

	void DX11DeviceContext::setshadertexture(UINT slot, RAZPTR<ID3D11ShaderResourceView> texture)
	{
		ID3D11ShaderResourceView* rview = texture.get();
		m_device_context->PSSetShaderResources(slot, 1, &rview);
	}

	void DX11DeviceContext::setshadertexture(RAZPTR<ID3D11ShaderResourceView> texture)
	{
		ID3D11ShaderResourceView* rview = texture.get();
		m_device_context->PSSetShaderResources(0, 1, &rview);
	}

	void DX11DeviceContext::setshadertextures(RAZPTR<ID3D11ShaderResourceView> texture, UINT arraysize)
	{
		ID3D11ShaderResourceView* rview = texture.get();
		m_device_context->PSSetShaderResources(0, arraysize, &rview);
	}

	void DX11DeviceContext::setshadertextures(UINT slot, RAZPTR<ID3D11ShaderResourceView> texture, UINT arraysize)
	{
		ID3D11ShaderResourceView* rview = texture.get();
		m_device_context->PSSetShaderResources(slot, arraysize, &rview);
	}




	bool DX11DeviceContext::Release()
	{
		
		m_bs->Release();
		m_depth_stencilview->Release();
		m_depth_stecil_buffer->Release();
		m_depth_stencilstate->Release();
		m_sampler_state->Release();
		m_contextswapchain->Release();
		delete this;
		return true;
	}

	bool DX11DeviceContext::MainRelease()
	{

		
		if (m_bs!=nullptr)m_bs->Release();
		if (m_depth_stencilview != nullptr)m_depth_stencilview->Release();
		if (m_depth_stecil_buffer != nullptr)m_depth_stecil_buffer->Release();
		if (m_depth_stencilstate != nullptr)m_depth_stencilstate->Release();
		if (m_sampler_state != nullptr)m_sampler_state->Release();
		m_device_context->Release();
		delete this;
		return true;
	}

	RAZPTR<DX11SwapChain> DX11DeviceContext::GetSwapChain()
	{
		return m_contextswapchain;
	}

	RAZPTR<ID3D11DeviceContext> DX11DeviceContext::GetContext()
	{
		return m_device_context;
	}

	DX11DeviceContext::~DX11DeviceContext()
	{
	}



}