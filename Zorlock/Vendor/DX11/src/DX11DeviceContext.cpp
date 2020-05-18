#include "ZLpch.h"
#include "DX11DeviceContext.h"
#include "DX11SwapChain.h"
#include "DX11VBuffer.h"
#include "DX11IBuffer.h"
#include "DX11Shaders.h"

namespace DX11Raz
{

	DX11DeviceContext::DX11DeviceContext(ID3D11DeviceContext* device_context) :m_device_context(device_context)
	{
	}

	void DX11DeviceContext::Init(ZWindow * zhandle)
	{
		m_contextContainer = zhandle;
		m_contextswapchain = new DX11SwapChain();
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
		m_device_context->ClearRenderTargetView(m_contextswapchain->m_rtv, clear_color);
		m_device_context->ClearDepthStencilView(m_depth_stencilview, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		m_device_context->OMSetRenderTargets(1, &m_contextswapchain->m_rtv, m_depth_stencilview);
		m_device_context->OMSetDepthStencilState(m_depth_stencilstate, 0);
		m_device_context->PSSetSamplers(0, 1, &m_sampler_state);
		//create depth stencil state
		m_device_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void DX11DeviceContext::setviewportsize(UINT width, UINT height)
	{

		
		D3D11_VIEWPORT vp = {};
		vp.Width = 1280;
		vp.Height = 720;
		vp.MinDepth = 0.0;
		vp.MaxDepth = 1.0;
		this->width = 1280;
		this->height = 720;
		m_device_context->RSSetViewports(1, &vp);


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

		rtbd.BlendEnable = true;
		rtbd.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		rtbd.DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		rtbd.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		rtbd.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		rtbd.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		rtbd.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

		blendDesc.RenderTarget[0] = rtbd;
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateBlendState(&blendDesc, &m_bs);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Blend State\r\n");
			return false;
		}
		setblendstate();
		return true;
	}

	void DX11DeviceContext::setblendstate()
	{

			m_device_context->OMSetBlendState(m_bs, NULL, 0xFFFFFFFF);
		

	}

	bool DX11DeviceContext::setstencilstate()
	{
		D3D11_DEPTH_STENCIL_DESC depthstencildesc;
		ZeroMemory(&depthstencildesc, sizeof(depthstencildesc));
		depthstencildesc.DepthEnable = true;
		depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateDepthStencilState(&depthstencildesc, &m_depth_stencilstate);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Depth Stencil State\r\n");
			ZL_CORE_INFO("Failed to Create Depth Stencil State");
			return false;
		}


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
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateSamplerState(&sampler_desc, &m_sampler_state);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Sampler State\r\n");
			ZL_CORE_INFO("Failed to Create Sampler State");
			return false;
		}

		return true;
	}

	bool DX11DeviceContext::setstencilbuffer()
	{
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
		HRESULT hr = DX11GraphicsEngine::Get()->GetDevice()->CreateTexture2D(&depthstencildesc, NULL, &m_depth_stecil_buffer);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Depth Surface\r\n");
			ZL_CORE_INFO("Failed to Create Depth Surface");
			return false;
		}
		hr = DX11GraphicsEngine::Get()->GetDevice()->CreateDepthStencilView(m_depth_stecil_buffer, NULL, &m_depth_stencilview);
		if (FAILED(hr))
		{
			OutputDebugString(L"Failed to Create Depth Stencil View\r\n");
			ZL_CORE_INFO("Failed to Depth Stencil View");
			return false;
		}


		return true;
	}

	void DX11DeviceContext::setvertexshader(RazShader* vertex_shader)
	{
		m_device_context->VSSetShader(vertex_shader->m_vs, nullptr, 0);
	}

	void DX11DeviceContext::setpixelshader(RazShader* pixel_shader)
	{
		m_device_context->PSSetShader(pixel_shader->m_ps, nullptr, 0);
	}

	void DX11DeviceContext::setvertexbuffer(RazVertexBuffer* vertex_buffer)
	{
		UINT stride = vertex_buffer->m_size_vertex;
		UINT offset = 0;
		m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
		m_device_context->IASetInputLayout(vertex_buffer->m_layout);
	}

	void DX11DeviceContext::setindexbuffer(RazIndexBuffer* index_buffer)
	{
		m_device_context->IASetIndexBuffer(index_buffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
	}

	void DX11DeviceContext::drawIndexed(UINT index_count, UINT start_vertex_index, UINT base_vertex_location)
	{
		m_device_context->DrawIndexed(index_count, start_vertex_index, base_vertex_location);
	}




	bool DX11DeviceContext::Release()
	{
		
		m_bs->Release();
		m_depth_stencilview->Release();
		m_depth_stecil_buffer->Release();
		m_depth_stencilstate->Release();
		m_sampler_state->Release();
		m_contextswapchain->release();
		delete this;
		return true;
	}

	bool DX11DeviceContext::MainRelease()
	{

		m_device_context->Release();

		delete this;
		return true;
	}

	ID3D11DeviceContext* DX11DeviceContext::GetContext()
	{
		return m_device_context;
	}

	DX11DeviceContext::~DX11DeviceContext()
	{
	}



}