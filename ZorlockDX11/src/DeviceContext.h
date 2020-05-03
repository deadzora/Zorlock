#pragma once
#include <d3d11.h>
#include <math.h>
//change this later to use templates
#include "ConstantBufferTypes.h"

class SwapChain;
class VertexBuffer;
class IndexBuffer;
template <class T>
class ConstantBuffer;
class VertexShader;
class PixelShader;


class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	void clearRenderTargetColor(SwapChain* swap_chain,float r,float g,float b,float a);
	void setvertexbuffer(VertexBuffer* vertex_buffer);
	void setindexbuffer(IndexBuffer* index_buffer);
	template <class T>
	void setconstantbuffer(ConstantBuffer<T> * constant_buffer);
	void drawtrianglelist(UINT vertex_count, UINT start_vertex_index);
	void drawtrianglestrip(UINT vertex_count, UINT start_vertex_index);
	void drawIndexed(UINT index_count, UINT start_vertex_index, UINT base_vertex_location);
	void setviewportsize(UINT width, UINT height);
	bool setstencilstate();
	bool setsamplerstate();
	bool setstencilbuffer();
	void setblendstate();
	bool createblendstate();
	void setvertexshader(VertexShader* vertex_shader);
	void setpixelshader(PixelShader* pixel_shader);
	void setshadertexture(ID3D11ShaderResourceView* texture);
	ID3D11DeviceContext* GetContext();
	ID3D11ShaderResourceView* loadtexture(const wchar_t* filename);
	ID3D11DeviceContext* getcontext();
	bool release();
	UINT w;
	UINT h;
	~DeviceContext();
private:
	ID3D11BlendState* m_bs;
	ID3D11DeviceContext* m_device_context;
	ID3D11DepthStencilView* m_depth_stencilview;
	ID3D11Texture2D* m_depth_stecil_buffer;
	ID3D11DepthStencilState* m_depth_stencilstate;
	ID3D11SamplerState* m_sampler_state;
	ID3D11ShaderResourceView* m_texture;

};

