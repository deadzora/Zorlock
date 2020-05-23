#include "ZLpch.h"
#include "DX11Raz.h"
#include "DX11DeviceContext.h"
#include "DX11SwapChain.h"
#include "DX11VBuffer.h"
#include "DX11IBuffer.h"
#include "DX11Shaders.h"
#include "DX11Textures.h"
#include <D3d11sdklayers.h>

namespace DX11Raz
{

	
	DX11GraphicsEngine engine;
	

	DX11GraphicsEngine::~DX11GraphicsEngine()
	{
		//release stuff
	}

	bool DX11GraphicsEngine::Initialize()
	{
		D3D_DRIVER_TYPE driver_types[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE
		};
		UINT num_driver_types = ARRAYSIZE(driver_types);


		D3D_FEATURE_LEVEL feature_levels[] =
		{
			D3D_FEATURE_LEVEL_11_1
		};
		UINT num_feature_levels = ARRAYSIZE(feature_levels);
		HRESULT res = 0;

		OutputDebugString(L"Initializing DX11 3D Device\r\n");

		for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
		{
			//NO IMMEDIATE CONTEXT!
#ifdef ZL_DEBUG_DX11
			
			res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, D3D11_DEBUG_FEATURE_FINISH_PER_RENDER_OP, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &feature_level, &m_imm_context);
#else
			res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &feature_level, &m_imm_context);
#endif
			if (SUCCEEDED(res))
				break;
			driver_type_index++;
		}
		if (FAILED(res))
		{
			
			OutputDebugString(L"Failed to Create DX11 3D Device\r\n");
			ZL_CORE_ASSERT(1,"Failed to Create DX11 3D Device");
			//m_imm_context->Release();
			m_d3d_device->Release();
			return false;
		}
		else {
			OutputDebugString(L"Created DX11 3D Device\r\n");
		}
		//create main shared context
		m_imm_device_context = new DX11DeviceContext(m_imm_context);

		m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
		m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
		m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
		//m_dxgi_factory->CreateSwapChain
		intialized = true;
		return true;
	}


	void DX11GraphicsEngine::Release()
	{
		printf("Graphics Shutdown \n");
		for (size_t i = 0; i < shaders.size(); i++)
		{
			shaders[i]->Release();
		}
		for (size_t i = 0; i < vbuffers.size(); i++)
		{
			vbuffers[i]->Release();

		}
		for (size_t i = 0; i < ibuffers.size(); i++)
		{
			ibuffers[i]->Release();

		}
		for (size_t i = 0; i < textures.size(); i++)
		{
			textures[i]->Release();

		}
		for (size_t i = 0; i < contexts.size(); i++)
		{
			contexts[i]->Release();

		}
		for (size_t i = 0; i < swapchains.size(); i++)
		{
			swapchains[i]->Release();
		}


		m_d3d_device->Release();
		m_dxgi_device->Release();
		m_dxgi_adapter->Release();
		m_imm_device_context->MainRelease();
		//m_imm_context->Release();

	}


	DX11GraphicsEngine* DX11GraphicsEngine::Get()
	{
		
		engine.enabled = true;
		return &engine;
	}

	void DX11GraphicsEngine::Cls()
	{
		if (current_device_context != 0)
		{

			current_device_context->clearRenderTarget();
		}
	}

	void DX11GraphicsEngine::Cls(float r, float g, float b, float a)
	{
		//we need to know which context we are performing CLS on
		if (current_device_context != 0)
		{

			current_device_context->clearRenderTargetColor(r, g, b, a);
		}
		//this->m_imm_device_context->clearRenderTargetColor(this->m_swapchain, r, g, b, a);
	}

	void DX11GraphicsEngine::Flip(bool vsync)
	{
		if (current_device_context != 0)
		{
			current_device_context->Flip(vsync);
		}
		//this->m_swapchain->flip(vsync);
	}

	void DX11GraphicsEngine::SetViewport(UINT x, UINT y, UINT width, UINT height)
	{



		//m_imm_device_context->setviewportsize(width, height);

	}

	ID3D11Device* DX11GraphicsEngine::GetDevice()
	{
		return m_d3d_device;
	}

	IDXGIFactory* DX11GraphicsEngine::GetFactory()
	{
		return m_dxgi_factory;
	}

	RazShader* DX11GraphicsEngine::GetCurrentShader()
	{
		return currentShader;
	}

	void DX11GraphicsEngine::SetCurrentShader(RazShader* shader)
	{
		currentShader = shader;
	}

	void DX11GraphicsEngine::AddShader(RazShader* shader)
	{
		shaders.push_back(shader);
	}

	void DX11GraphicsEngine::RemoveShader(RazShader* shader)
	{
		for (auto it = shaders.begin(); it != shaders.end(); ) {
			if (*it == shader) {
				it = shaders.erase(it);
				shader->Release();
				break;
			}
			else {
				++it;
			}
		}
		shaders.shrink_to_fit();
	}

	DX11DeviceContext* DX11GraphicsEngine::GetCurrentDeviceContext()
	{
		return current_device_context;
	}

	void DX11GraphicsEngine::SetCurrentDeviceContext(DX11DeviceContext* curcontext)
	{
		current_device_context = curcontext;
	}

	void DX11GraphicsEngine::AddDeviceContext(DX11DeviceContext* curcontext)
	{
		contexts.push_back(curcontext);
	}

	void DX11GraphicsEngine::RemoveDeviceContext(DX11DeviceContext* context)
	{
		for (auto it = contexts.begin(); it != contexts.end(); ) {
			if (*it == context) {
				it = contexts.erase(it);
				context->Release();
				break;
			}
			else {
				++it;
			}
		}
		contexts.shrink_to_fit();
	}

	RazVertexBuffer* DX11GraphicsEngine::GetCurrentVertexBuffer()
	{
		return currentVertexBuffer;
	}

	void DX11GraphicsEngine::SetCurrentVertexBuffer(RazVertexBuffer* vbuffer)
	{
		currentVertexBuffer = vbuffer;
	}

	void DX11GraphicsEngine::AddVertexBuffer(RazVertexBuffer* vbuffer)
	{
		vbuffers.push_back(vbuffer);
	}

	void DX11GraphicsEngine::RemoveVertexBuffer(RazVertexBuffer* vbuffer)
	{
		for (auto it = vbuffers.begin(); it != vbuffers.end(); ) {
			if (*it == vbuffer) {
				it = vbuffers.erase(it);
				vbuffer->Release();
				break;
			}
			else {
				++it;
			}
		}
		vbuffers.shrink_to_fit();
	}

	RazIndexBuffer* DX11GraphicsEngine::GetCurrentIndexBuffer()
	{
		return currentIndexBuffer;
	}

	void DX11GraphicsEngine::SetCurrentIndexBuffer(RazIndexBuffer* ibuffer)
	{
		currentIndexBuffer = ibuffer;
	}

	void DX11GraphicsEngine::AddIndexBuffer(RazIndexBuffer* ibuffer)
	{
		ibuffers.push_back(ibuffer);
	}

	void DX11GraphicsEngine::RemoveIndexBuffer(RazIndexBuffer* ibuffer)
	{
		for (auto it = ibuffers.begin(); it != ibuffers.end(); ) {
			if (*it == ibuffer) {
				it = ibuffers.erase(it);
				ibuffer->Release();
				break;
			}
			else {
				++it;
			}
		}
		ibuffers.shrink_to_fit();
	}

	RazTexture* DX11GraphicsEngine::GetCurrentTexture()
	{
		return currentTexture;
	}

	void DX11GraphicsEngine::SetCurrentTexture(RazTexture* texture)
	{
		currentTexture = texture;
	}

	void DX11GraphicsEngine::AddTexture(RazTexture* texture)
	{
		textures.push_back(texture);
	}

	void DX11GraphicsEngine::RemoveTexture(RazTexture* texture)
	{
		for (auto it = textures.begin(); it != textures.end(); ) {
			if (*it == texture) {
				it = textures.erase(it);
				texture->Release();
				break;
			}
			else {
				++it;
			}
		}
		textures.shrink_to_fit();
	}

	DX11DeviceContext* DX11GraphicsEngine::GetImmediateDeviceContext()
	{
		return m_imm_device_context;
	}



	DX11SwapChain* DX11GraphicsEngine::CreateSwapChain()
	{
		return new DX11SwapChain();
	}
	void DX11GraphicsEngine::AddSwapChain(DX11SwapChain* swapchain)
	{
		swapchains.push_back(swapchain);
	}
	void DX11GraphicsEngine::RemoveSwapChain(DX11SwapChain* swapchain)
	{
		for (auto it = swapchains.begin(); it != swapchains.end(); ) {
			if (*it == swapchain) {
				it = swapchains.erase(it);
				swapchain->Release();
				break;
			}
			else {
				++it;
			}
		}
		swapchains.shrink_to_fit();
	}
#ifdef ZL_DEBUG
	/*
	ID3D11Debug* DX11GraphicsEngine::DXEnableDebug(DX11DebugCallback f)
	{


		if (this->m_d3dDebug != nullptr)
		{
			HRESULT res = 0;
			res = m_d3d_device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&this->m_d3dDebug));
			if (SUCCEEDED(res))
			{
				m_d3dDebug->SetFeatureMask(D3D11_DEBUG_FEATURE_FINISH_PER_RENDER_OP);
				HRESULT resb = 0;
				resb = m_d3dDebug->QueryInterface(__uuidof(ID3D11InfoQueue), reinterpret_cast<void**>(&this->d3dInfoQueue));
				if (SUCCEEDED(resb))
				{
						DebugCall = f;
				}
			}
			//res = ID3D11Debug::SetFeatureMask(D3D11_DEBUG_FEATURE_FINISH_PER_RENDER_OP);
		}

		return nullptr;
	}
	*/
#endif


	bool RazDX11Initialize()
	{
		return DX11GraphicsEngine::Get()->Initialize();
		
	}

	bool RazDX11Release()
	{
		DX11GraphicsEngine::Get()->Release();
		return true;
	}

	void RazDX11CreateContext(ZWindow* zhandle)
	{
		//ID3D11DeviceContext * newcontext;
		//HRESULT res = 0;
		//DX11GraphicsEngine::Get()->GetDevice()->GetImmediateContext(&newcontext); //->CreateDeferredContext(0, &newcontext);
		//if (SUCCEEDED(res))
		//{
		DX11DeviceContext* DXContext = new DX11DeviceContext(DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext());

			zhandle->SetDeviceContext(DXContext);			
			DXContext->Init(zhandle);
			RazSetCurrentContext(DXContext);
		//}

	}

	void RazSetCLSColor(DX11DeviceContext* dhandle, float r, float g, float b, float a)
	{
		dhandle->clearRenderTargetColor(r, g, b, a);
	}

	void RazCLS(DX11DeviceContext* dhandle)
	{
		dhandle->clearRenderTarget();
	}

	void RazSetViewport(UINT width, UINT height)
	{
		DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->setviewportsize(width, height);
	}

	RazVertexBuffer* RazCreateVertexBuffer()
	{
		return new RazVertexBuffer();
	}

	void RazDeleteVertexBuffer(RazVertexBuffer* v)
	{
		DX11GraphicsEngine::Get()->RemoveVertexBuffer(v);
	}

	RazIndexBuffer* RazCreateIndexBuffer()
	{
		return new RazIndexBuffer();
	}

	void RazDeleteIndexBuffer(RazIndexBuffer* i)
	{
		DX11GraphicsEngine::Get()->RemoveIndexBuffer(i);
	}

	RazShader* RazCreateShader()
	{
		return new RazShader();
	}

	void RazDeleteShader(RazShader * shader)
	{
		DX11GraphicsEngine::Get()->RemoveShader(shader);
	}

	void RazSetCurrentShader(RazShader* shader)
	{
		return DX11GraphicsEngine::Get()->SetCurrentShader(shader);
	}

	RazShader* RazGetCurrentShader()
	{
		return DX11GraphicsEngine::Get()->GetCurrentShader();
	}

	void RazSetCurrentContext(DX11DeviceContext* dhandle)
	{
		DX11GraphicsEngine::Get()->SetCurrentDeviceContext(dhandle);
	}

	DX11DeviceContext* RazGetCurrentContext()
	{
		return DX11GraphicsEngine::Get()->GetCurrentDeviceContext();
	}

	void RazSetCurrentVertexBuffer(RazVertexBuffer* vbuffer)
	{
		DX11GraphicsEngine::Get()->SetCurrentVertexBuffer(vbuffer);
	}

	RazVertexBuffer* RazGetCurrentVertexBuffer()
	{
		return DX11GraphicsEngine::Get()->GetCurrentVertexBuffer();
	}

	void RazSetCurrentIndexBuffer(RazIndexBuffer* ibuffer)
	{
		DX11GraphicsEngine::Get()->SetCurrentIndexBuffer(ibuffer);
	}

	RazIndexBuffer* RazGetCurrentIndexBuffer()
	{
		return DX11GraphicsEngine::Get()->GetCurrentIndexBuffer();
	}

	RazTexture* RazGetCurrentTexture()
	{
		return DX11GraphicsEngine::Get()->GetCurrentTexture();
	}

	RazTexture* RazCreateTexture(const DX11Color& color, aiTextureType type)
	{
		return new RazTexture(color,type);
	}

	RazTexture* RazCreateTexture(const DX11Color* colorData, UINT width, UINT height, aiTextureType type)
	{
		return new RazTexture(colorData, width, height, type);
	}

	RazTexture* RazCreateTexture(const DX11Color* colorData, UINT width, UINT height, UINT size, aiTextureType type)
	{
		return new RazTexture(colorData, width, height,size, type);
	}

	RazTexture* RazCreateTexture(const wchar_t* filename, aiTextureType type)
	{
		return new RazTexture(filename, type);
	}

	RazTexture* RazCreateTexture(std::string filename, aiTextureType type)
	{
		return new RazTexture(filename, type);
	}

	RazTexture* RazCreateTexture(ID3D11ShaderResourceView* textureView, aiTextureType type)
	{
		return new RazTexture(textureView, type);
	}

	void RazSetCurrentTexture(RazTexture* texture)
	{
		DX11GraphicsEngine::Get()->SetCurrentTexture(texture);
	}

	void RazSetDeleteTexture(RazTexture* texture)
	{
		DX11GraphicsEngine::Get()->RemoveTexture(texture);
	}

	void RazSetLayout(RazVertexBuffer* vbuffer, ID3D10Blob* vertexshader)
	{
		vbuffer->SetLayout(vertexshader);
	}

	void RazSetLayout(ID3D10Blob* vertexshader)
	{
		RazGetCurrentVertexBuffer()->SetLayout(vertexshader);
	}

	void RazSetLayout(RazVertexBuffer* vbuffer)
	{
		vbuffer->SetLayout(RazGetCurrentShader()->GetBuffer());
	}

	void RazSetLayout()
	{
		RazGetCurrentVertexBuffer()->SetLayout(RazGetCurrentShader()->GetBuffer());
	}

	void RazBindIndexBuffer(RazIndexBuffer* ibuffer)
	{
		RazGetCurrentContext()->setindexbuffer(ibuffer);
	}

	void RazBindIndexBuffer()
	{
		RazGetCurrentContext()->setindexbuffer(RazGetCurrentIndexBuffer());
	}

	void RazBindIndices(RazIndexBuffer* ibuffer, UINT* indices, UINT count)
	{
		ibuffer->SetIndexes(indices, count);
	}

	void RazBindIndices(UINT* indices, UINT count)
	{
		RazGetCurrentIndexBuffer()->SetIndexes(indices, count);
	}

	void RazBindIndices(std::vector<DWORD> indices)
	{
		RazGetCurrentIndexBuffer()->SetIndexes(indices);
	}

	void RazBindVertices(RazVertexBuffer* vbuffer, float* verts, UINT size)
	{
		vbuffer->SetVertices(verts, size);
	}

	void RazBindVertices(RazVertexBuffer* vbuffer, void* vertices, UINT size)
	{
		vbuffer->SetVertices(vertices, size);
	}

	void RazBindVertices(float* verts, UINT size)
	{
		RazGetCurrentVertexBuffer()->SetVertices(verts, size);
	}

	void RazBindVertices(void* vertices, UINT size)
	{
		RazGetCurrentVertexBuffer()->SetVertices(vertices, size);
	}

	void RazBindVertices(UINT size)
	{
		RazGetCurrentVertexBuffer()->SetVertices(size);
	}

	void RazFlip(bool vsync)
	{
		RazGetCurrentContext()->Flip(vsync);
	}

	void RazApplyVertexShaderConstants(RazShader* shader)
	{
		shader->ApplyAllVertexCB();
	}

	void RazApplyPixelShaderConstants(RazShader* shader)
	{
		shader->ApplyAllPixelCB();
	}

	void RazApplyVertexShaderConstants()
	{
		RazGetCurrentShader()->ApplyAllVertexCB();
	}

	void RazApplyPixelShaderConstants()
	{
		RazGetCurrentShader()->ApplyAllPixelCB();
	}

	void RazApplyVertexShader(DX11DeviceContext* dhandle, RazShader* shader)
	{
		dhandle->setvertexshader(shader);
	}

	void RazApplyPixelShader(DX11DeviceContext* dhandle, RazShader* shader)
	{
		dhandle->setpixelshader(shader);
	}

	void RazApplyShader(DX11DeviceContext* dhandle, RazShader* shader)
	{
		dhandle->setvertexshader(shader);
		dhandle->setpixelshader(shader);
	}

	void RazApplyVertexShader(RazShader* shader)
	{
		RazGetCurrentContext()->setvertexshader(shader);
	}

	void RazApplyPixelShader(RazShader* shader)
	{
		RazGetCurrentContext()->setpixelshader(shader);
	}

	void RazApplyShader(RazShader* shader)
	{
		RazApplyVertexShader(shader);
		RazApplyPixelShader(shader);
	}

	void RazApplyVertexShader()
	{
		RazGetCurrentContext()->setvertexshader(RazGetCurrentShader());
	}

	void RazApplyPixelShader()
	{
		RazGetCurrentContext()->setpixelshader(RazGetCurrentShader());
	}

	void RazApplyShader()
	{
		RazApplyVertexShader();
		RazApplyPixelShader();
	}

	void RazSetBlendState(DX11DeviceContext* dhandle)
	{
		dhandle->setblendstate();
	}

	void RazSetBlendState()
	{
		RazGetCurrentContext()->setblendstate();
	}

	void RazDrawIndexed(DX11DeviceContext* dhandle, UINT index_count, UINT start_vertex_index, UINT base_vertex_location)
	{
		dhandle->drawIndexed(index_count, start_vertex_index, base_vertex_location);
	}

	void RazDrawIndexed(UINT index_count, UINT start_vertex_index, UINT base_vertex_location)
	{
		RazGetCurrentContext()->drawIndexed(index_count, start_vertex_index, base_vertex_location);
	}

	void RazApplyShaderTexture(RazShader* shader, std::string name, RazTexture* texture)
	{
		shader->UpdateTextureBuffer(name, texture->GetTexture());
		RazGetCurrentContext()->setshadertexture(texture->GetTextureView());
	}

	void RazApplyShaderTexture(std::string name, RazTexture* texture)
	{
		RazGetCurrentShader()->UpdateTextureBuffer(name, texture->GetTexture());
		RazGetCurrentContext()->setshadertexture(texture->GetTextureView());
	}

	void RazApplyShaderTexture(RazTexture* texture)
	{
		RazGetCurrentContext()->setshadertexture(texture->GetTextureView());
	}

	void RazApplyShaderTexture(RazTexture* texture, UINT slot)
	{
		RazGetCurrentContext()->setshadertexture( slot,texture->GetTextureView());
	}

	void RazApplyVertexBuffer(RazVertexBuffer* v)
	{
		RazGetCurrentContext()->setvertexbuffer(v);
	}

	void RazApplyVertexBuffer()
	{
		RazGetCurrentContext()->setvertexbuffer(RazGetCurrentVertexBuffer());
	}

	void RazApplyIndexBuffer(RazIndexBuffer* ibuffer)
	{
		RazGetCurrentContext()->setindexbuffer(ibuffer);
	}





}
