#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GraphicsEngine.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "ErrorLogger.h"


DeviceContext::DeviceContext(ID3D11DeviceContext* device_context):m_device_context(device_context)
{
	
}

void DeviceContext::clearRenderTargetColor(SwapChain* swap_chain,float r, float g, float b, float a)
{
	FLOAT clear_color[] = { r,g,b,a };
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
	m_device_context->ClearDepthStencilView(m_depth_stencilview, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_device_context->OMSetRenderTargets(1, &swap_chain->m_rtv, m_depth_stencilview);
	m_device_context->OMSetDepthStencilState(m_depth_stencilstate, 0);
	m_device_context->PSSetSamplers(0, 1, &m_sampler_state);
	//create depth stencil state
	m_device_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void DeviceContext::setvertexbuffer(VertexBuffer * vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;
	m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	m_device_context->IASetInputLayout(vertex_buffer->m_layout);

}

void DeviceContext::setindexbuffer(IndexBuffer * index_buffer)
{
	m_device_context->IASetIndexBuffer(index_buffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}
template <class T>
void DeviceContext::setconstantbuffer(ConstantBuffer<T> * constant_buffer)
{
	D3D11_MAPPED_SUBRESOURCE init_data;
	
	m_device_context->Map(constant_buffer->m_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &init_data);
	//find a way to pass struct types
	CopyMemory(init_data.pData, constant_buffer->m_vsd, sizeof(T));
	m_device_context->Unmap(constant_buffer->m_buffer, 0);
	m_device_context->VSSetConstantBuffers(constant_buffer->bufferindex, 1, &constant_buffer->m_buffer);
}

void DeviceContext::drawtrianglelist(UINT vertex_count, UINT start_vertex_index)
{
	//m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawtrianglestrip(UINT vertex_count, UINT start_vertex_index)
{
	//m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::drawIndexed(UINT index_count, UINT start_vertex_index, UINT base_vertex_location)
{
	//m_device_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->DrawIndexed(index_count, start_vertex_index, base_vertex_location);
}

void DeviceContext::setviewportsize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0;
	vp.MaxDepth = 1.0;
	w = width;
	h = height;
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

bool DeviceContext::setstencilstate()
{
	D3D11_DEPTH_STENCIL_DESC depthstencildesc;
	ZeroMemory(&depthstencildesc, sizeof(depthstencildesc));
	depthstencildesc.DepthEnable = true;
	depthstencildesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateDepthStencilState(&depthstencildesc, &m_depth_stencilstate);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Depth Stencil State");
		return false;
	}


	return true;
}

bool DeviceContext::setsamplerstate()
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
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateSamplerState(&sampler_desc, &m_sampler_state);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Sampler State");
		return false;
	}

	return true;
}

bool DeviceContext::setstencilbuffer()
{
	D3D11_TEXTURE2D_DESC depthstencildesc;
	ZeroMemory(&depthstencildesc, sizeof(depthstencildesc));
	depthstencildesc.Width = w;
	depthstencildesc.Height = h;
	depthstencildesc.MipLevels = 1;
	depthstencildesc.ArraySize = 1;
	depthstencildesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthstencildesc.SampleDesc.Count = 1;
	depthstencildesc.SampleDesc.Quality = 0;
	depthstencildesc.Usage = D3D11_USAGE_DEFAULT;
	depthstencildesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthstencildesc.CPUAccessFlags = 0;
	depthstencildesc.MiscFlags = 0;
	HRESULT hr = GraphicsEngine::get()->m_d3d_device->CreateTexture2D(&depthstencildesc, NULL, &m_depth_stecil_buffer);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Texture");
		return false;
	}
	hr = GraphicsEngine::get()->m_d3d_device->CreateDepthStencilView(m_depth_stecil_buffer, NULL, &m_depth_stencilview);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Depth Stencil View");
		return false;
	}


	return true;
}

void DeviceContext::setblendstate()
{
	m_device_context->OMSetBlendState(m_bs,NULL,0xFFFFFFFF);
}

bool DeviceContext::createblendstate()
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
	HRESULT hr = GraphicsEngine::get()->getdevice()->CreateBlendState(&blendDesc, &m_bs);
	if (FAILED(hr))
	{
		ErrorLogger::log(hr, "Failed to Create Blend State");
		return false;
	}
	return true;
}

void DeviceContext::setvertexshader(VertexShader * vertex_shader)
{

	m_device_context->VSSetShader(vertex_shader->m_vs,nullptr,0);

}

void DeviceContext::setpixelshader(PixelShader * pixel_shader)
{
	m_device_context->PSSetShader(pixel_shader->m_ps, nullptr, 0);
}

void DeviceContext::setshadertexture(ID3D11ShaderResourceView* texture)
{
	m_device_context->PSSetShaderResources(0, 1, &texture);
}

ID3D11DeviceContext * DeviceContext::GetContext()
{
	return this->m_device_context;
}

ID3D11ShaderResourceView* DeviceContext::loadtexture(const wchar_t* filename)
{
	std::wstring ws(filename);
	std::string fn(ws.begin(), ws.end());

	if (StringConverter::FileExists(fn))
	{
		if (StringConverter::GetFileExtension(fn) == ".dds" || StringConverter::GetFileExtension(fn) == ".DDS")
		{
			HRESULT hr = DirectX::CreateDDSTextureFromFile(GraphicsEngine::get()->m_d3d_device, m_device_context, filename, nullptr, &m_texture);
			if (!SUCCEEDED(hr))
			{
				ErrorLogger::log(hr, "Failed to Load DDS Texture" + fn);
				return NULL;
			}
		}
		else
		{
			HRESULT hr = DirectX::CreateWICTextureFromFile(GraphicsEngine::get()->m_d3d_device, m_device_context, filename, nullptr, &m_texture);

			if (!SUCCEEDED(hr))
			{
				ErrorLogger::log(hr, "Failed to Load Texture " + fn);
				return NULL;
			}
		}
	}
	else {
		return NULL;
	}



	return m_texture;
}

ID3D11DeviceContext * DeviceContext::getcontext()
{
	return m_device_context;
}



bool DeviceContext::release()
{

	if (m_texture)m_texture->Release();
	if(m_bs)m_bs->Release();
	if(m_depth_stencilview)m_depth_stencilview->Release();
	if(m_depth_stecil_buffer)m_depth_stecil_buffer->Release();
	if(m_depth_stencilstate)m_depth_stencilstate->Release();
	if(m_sampler_state)m_sampler_state->Release();
	if(m_device_context)m_device_context->Release();
	delete this;
	return true;
}


DeviceContext::~DeviceContext()
{
}
