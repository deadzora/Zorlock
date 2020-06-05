#include "ZLpch.h"
#include "DX11Raz.h"
#include "DX11DeviceContext.h"
#include "DX11SwapChain.h"
#include "DX11VBuffer.h"
#include "DX11IBuffer.h"
#include "DX11Shaders.h"
#include "DX11Textures.h"
#include <D3d11sdklayers.h>
//#define ZL_DEBUG_DX11
namespace DX11Raz
{

	DX11GraphicsEngine engine;
	RAZPTR<DX11GraphicsEngine> m_engine;
	

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
		ID3D11Device* d3ddevice;
		ID3D11DeviceContext* d3ddevicecontext;
		for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
		{
			//NO IMMEDIATE CONTEXT!
#ifdef ZL_DEBUG_DX11
			
			res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, D3D11_DEBUG_FEATURE_FINISH_PER_RENDER_OP, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &d3ddevice, &feature_level, &d3ddevicecontext);
#else
			res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &d3ddevice, &feature_level, &d3ddevicecontext);
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
			d3ddevice->Release();
			return false;
		}
		else {
			OutputDebugString(L"Created DX11 3D Device\r\n");
		}
		//create main shared context
		m_d3d_device = RAZPTR<ID3D11Device>(d3ddevice);
		m_imm_context = RAZPTR<ID3D11DeviceContext>(d3ddevicecontext);
		m_imm_device_context = RAZPTR<DX11DeviceContext>(new DX11DeviceContext(m_imm_context));
		IDXGIDevice* idxgidev;
		m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&idxgidev);
		m_dxgi_device = RAZPTR<IDXGIDevice>(idxgidev);
		IDXGIAdapter* idxgiadapter;
		m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&idxgiadapter);
		m_dxgi_adapter = RAZPTR<IDXGIAdapter>(idxgiadapter);
		IDXGIFactory* idxfactory;
		m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&idxfactory);
		m_dxgi_factory = RAZPTR<IDXGIFactory>(idxfactory);
		//m_dxgi_factory->CreateSwapChain
		intialized = true;
		
		return true;
	}


	void DX11GraphicsEngine::Release()
	{
		printf("Graphics Shutdown \n");
		for (size_t i = 0; i < shaders.size(); i++)
		{
			if(shaders[i]!=nullptr)
				shaders[i]->Release();
		}
		for (size_t i = 0; i < vbuffers.size(); i++)
		{
			if (vbuffers[i] != nullptr)
				vbuffers[i]->Release();

		}
		for (size_t i = 0; i < ibuffers.size(); i++)
		{
			if (ibuffers[i] != nullptr)
				ibuffers[i]->Release();

		}
		for (size_t i = 0; i < textures.size(); i++)
		{
			if (textures[i] != nullptr)
				textures[i]->Release();

		}
		for (size_t i = 0; i < contexts.size(); i++)
		{
			if (contexts[i] != nullptr)
				contexts[i]->Release();

		}
		for (size_t i = 0; i < swapchains.size(); i++)
		{
			if (swapchains[i] != nullptr)
				swapchains[i]->Release();
		}

		if (m_d3d_device != nullptr)
			m_d3d_device->Release();
		if (m_dxgi_device != nullptr)
			m_dxgi_device->Release();
		if (m_dxgi_device != nullptr)
			m_dxgi_device->Release();
		if (m_imm_device_context != nullptr)
			m_imm_device_context->MainRelease();
		//m_imm_context->Release();

	}


	RAZPTR<DX11GraphicsEngine> DX11GraphicsEngine::Get()
	{
		if (m_engine == nullptr)
		{
			m_engine = CreateZRef<DX11GraphicsEngine>();
		}
		m_engine->enabled = true;
		return m_engine;
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

	RAZPTR<ID3D11Device> DX11GraphicsEngine::GetDevice()
	{
		return this->m_d3d_device;
	}

	RAZPTR<IDXGIFactory> DX11GraphicsEngine::GetFactory()
	{
		return this->m_dxgi_factory;
	}

	RAZPTR<RazShader> DX11GraphicsEngine::GetCurrentShader()
	{
		return this->currentShader;
	}

	void DX11GraphicsEngine::SetCurrentShader(RAZPTR<RazShader> shader)
	{
		currentShader = shader;
	}

	void DX11GraphicsEngine::AddShader(RAZPTR<RazShader> shader)
	{
		shaders.push_back(shader);
	}

	void DX11GraphicsEngine::RemoveShader(RAZPTR<RazShader> shader)
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

	RAZPTR<DX11DeviceContext> DX11GraphicsEngine::GetCurrentDeviceContext()
	{
		return current_device_context;
	}

	void DX11GraphicsEngine::SetCurrentDeviceContext(RAZPTR<DX11DeviceContext> curcontext)
	{
		current_device_context = curcontext;
	}

	void DX11GraphicsEngine::AddDeviceContext(RAZPTR<DX11DeviceContext> curcontext)
	{
		contexts.push_back(curcontext);
	}

	void DX11GraphicsEngine::RemoveDeviceContext(RAZPTR<DX11DeviceContext> context)
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

	RAZPTR<RazVertexBuffer> DX11GraphicsEngine::GetCurrentVertexBuffer()
	{
		return currentVertexBuffer;
	}

	void DX11GraphicsEngine::SetCurrentVertexBuffer(RAZPTR<RazVertexBuffer> vbuffer)
	{
		currentVertexBuffer = vbuffer;
	}

	void DX11GraphicsEngine::AddVertexBuffer(RAZPTR<RazVertexBuffer> vbuffer)
	{
		vbuffers.push_back(vbuffer);
	}

	void DX11GraphicsEngine::RemoveVertexBuffer(RAZPTR<RazVertexBuffer> vbuffer)
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

	RAZPTR<RazIndexBuffer> DX11GraphicsEngine::GetCurrentIndexBuffer()
	{
		return currentIndexBuffer;
	}

	void DX11GraphicsEngine::SetCurrentIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer)
	{
		currentIndexBuffer = ibuffer;
	}

	void DX11GraphicsEngine::AddIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer)
	{
		ibuffers.push_back(ibuffer);
	}

	void DX11GraphicsEngine::RemoveIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer)
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

	RAZPTR<RazTexture> DX11GraphicsEngine::GetCurrentTexture()
	{
		return currentTexture;
	}

	void DX11GraphicsEngine::SetCurrentTexture(RAZPTR<RazTexture> texture)
	{
		currentTexture = texture;
	}

	void DX11GraphicsEngine::AddTexture(RAZPTR<RazTexture> texture)
	{
		textures.push_back(texture);
	}

	void DX11GraphicsEngine::RemoveTexture(RAZPTR<RazTexture> texture)
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

	RAZPTR<DX11DeviceContext> DX11GraphicsEngine::GetImmediateDeviceContext()
	{
		return this->m_imm_device_context;
	}



	RAZPTR<DX11SwapChain> DX11GraphicsEngine::CreateSwapChain()
	{
		return RAZPTR<DX11SwapChain>(new DX11SwapChain());
	}
	void DX11GraphicsEngine::AddSwapChain(RAZPTR<DX11SwapChain> swapchain)
	{
		swapchains.push_back(swapchain);
	}
	void DX11GraphicsEngine::RemoveSwapChain(RAZPTR<DX11SwapChain> swapchain)
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

	void RazDX11CreateContext(RAZPTR<ZWindow> zhandle)
	{
		//ID3D11DeviceContext * newcontext;
		//HRESULT res = 0;
		//DX11GraphicsEngine::Get()->GetDevice()->GetImmediateContext(&newcontext); //->CreateDeferredContext(0, &newcontext);
		//if (SUCCEEDED(res))
		//{
		RAZPTR<ID3D11DeviceContext> devcontext = DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext();
		DX11DeviceContext* context = new DX11DeviceContext(devcontext);
		RAZPTR<DX11DeviceContext> DXContext = RAZPTR<DX11DeviceContext>(context);

			zhandle->SetDeviceContext(DXContext);			
			DXContext->Init(zhandle);
			RazSetCurrentContext(DXContext);
		//}

	}

	void RazSetCLSColor(RAZPTR<DX11DeviceContext> dhandle, float r, float g, float b, float a)
	{
		dhandle->clearRenderTargetColor(r, g, b, a);
	}

	void RazCLS(RAZPTR<DX11DeviceContext> dhandle)
	{
		dhandle->clearRenderTarget();
	}

	void RazSetViewport(UINT width, UINT height)
	{
		DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->setviewportsize(width, height);
	}

	RAZPTR<RazVertexBuffer> RazCreateVertexBuffer()
	{
		return RAZPTR<RazVertexBuffer>(new RazVertexBuffer());
	}

	void RazDeleteVertexBuffer(RAZPTR<RazVertexBuffer> v)
	{
		DX11GraphicsEngine::Get()->RemoveVertexBuffer(v);
	}

	RAZPTR<RazIndexBuffer> RazCreateIndexBuffer()
	{
		return RAZPTR<RazIndexBuffer>(new RazIndexBuffer());
	}

	void RazDeleteIndexBuffer(RAZPTR<RazIndexBuffer> i)
	{
		DX11GraphicsEngine::Get()->RemoveIndexBuffer(i);
	}

	RAZPTR<RazShader> RazCreateShader()
	{
		return RAZPTR<RazShader>(new RazShader());
	}

	void RazDeleteShader(RAZPTR<RazShader> shader)
	{
		DX11GraphicsEngine::Get()->RemoveShader(shader);
	}

	void RazSetCurrentShader(RAZPTR<RazShader> shader)
	{
		return DX11GraphicsEngine::Get()->SetCurrentShader(shader);
	}

	RAZPTR<RazShader> RazGetCurrentShader()
	{
		return DX11GraphicsEngine::Get()->GetCurrentShader();
	}

	void RazSetCurrentContext(RAZPTR<DX11DeviceContext> dhandle)
	{
		DX11GraphicsEngine::Get()->SetCurrentDeviceContext(dhandle);
	}

	RAZPTR<DX11DeviceContext> RazGetCurrentContext()
	{
		return DX11GraphicsEngine::Get()->GetCurrentDeviceContext();
	}

	void RazSetCurrentVertexBuffer(RAZPTR<RazVertexBuffer> vbuffer)
	{
		DX11GraphicsEngine::Get()->SetCurrentVertexBuffer(vbuffer);
	}

	RAZPTR<RazVertexBuffer> RazGetCurrentVertexBuffer()
	{
		return DX11GraphicsEngine::Get()->GetCurrentVertexBuffer();
	}

	void RazSetCurrentIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer)
	{
		DX11GraphicsEngine::Get()->SetCurrentIndexBuffer(ibuffer);
	}

	RAZPTR<RazIndexBuffer> RazGetCurrentIndexBuffer()
	{
		return DX11GraphicsEngine::Get()->GetCurrentIndexBuffer();
	}

	RAZPTR<RazTexture> RazGetCurrentTexture()
	{
		return DX11GraphicsEngine::Get()->GetCurrentTexture();
	}



	RAZPTR<RazTexture> RazCreateTexture(const RAZPTR<DX11Color> colorData, UINT width, UINT height, aiTextureType type)
	{
		return RAZPTR<RazTexture>(new RazTexture(colorData, width, height, type));
	}

	RAZPTR<RazTexture> RazCreateTexture(const RAZPTR<DX11Color> colorData, UINT width, UINT height, UINT size, aiTextureType type)
	{
		return RAZPTR<RazTexture>(new RazTexture(colorData, width, height,size, type));
	}

	RAZPTR<RazTexture> RazCreateTexture(const wchar_t* filename, aiTextureType type)
	{
		return RAZPTR<RazTexture>(new RazTexture(filename, type));
	}

	RAZPTR<RazTexture> RazCreateTexture(std::string filename, aiTextureType type)
	{
		return RAZPTR<RazTexture>(new RazTexture(filename, type));
	}

	RAZPTR<RazTexture> RazCreateTexture(RAZPTR<ID3D11ShaderResourceView> textureView, aiTextureType type)
	{
		return RAZPTR<RazTexture>(new RazTexture(textureView, type));
	}

	void RazSetCurrentTexture(RAZPTR<RazTexture> texture)
	{
		DX11GraphicsEngine::Get()->SetCurrentTexture(texture);
	}

	void RazSetDeleteTexture(RAZPTR<RazTexture> texture)
	{
		DX11GraphicsEngine::Get()->RemoveTexture(texture);
	}

	void RazSetLayout(RAZPTR<RazVertexBuffer> vbuffer, RAZPTR<ID3D10Blob> vertexshader)
	{
		vbuffer->SetLayout(vertexshader);
	}

	void RazSetLayout(RAZPTR<ID3D10Blob> vertexshader)
	{
		RazGetCurrentVertexBuffer()->SetLayout(vertexshader);
	}

	void RazSetLayout(RAZPTR<RazVertexBuffer> vbuffer)
	{
		vbuffer->SetLayout(RazGetCurrentShader()->GetBuffer());
	}

	void RazSetLayout()
	{
		RazGetCurrentVertexBuffer()->SetLayout(RazGetCurrentShader()->GetBuffer());
	}

	void RazBindIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer)
	{
		RazGetCurrentContext()->setindexbuffer(ibuffer);
	}

	void RazBindIndexBuffer()
	{
		RazGetCurrentContext()->setindexbuffer(RazGetCurrentIndexBuffer());
	}

	void RazBindIndices(RAZPTR<RazIndexBuffer> ibuffer, UINT* indices, UINT count)
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

	void RazBindVertices(RAZPTR<RazVertexBuffer> vbuffer, float* verts, UINT size)
	{
		vbuffer->SetVertices(verts, size);
	}

	void RazBindVertices(RAZPTR<RazVertexBuffer> vbuffer, void* vertices, UINT size)
	{
		vbuffer->SetVertices(vertices, size);
	}

	void RazBindVertices(RAZPTR<RazVertexBuffer> vbuffer, void* vertices, UINT bytewidth, UINT size)
	{
		vbuffer->SetVertices(vertices, bytewidth, size);
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

	void RazApplyVertexShaderConstants(RAZPTR<RazShader> shader)
	{
		shader->ApplyAllVertexCB();
	}

	void RazApplyPixelShaderConstants(RAZPTR<RazShader> shader)
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

	void RazApplyVertexShader(RAZPTR<DX11DeviceContext> dhandle, RAZPTR<RazShader> shader)
	{
		dhandle->setvertexshader(shader);
	}

	void RazApplyPixelShader(RAZPTR<DX11DeviceContext> dhandle, RAZPTR<RazShader> shader)
	{
		dhandle->setpixelshader(shader);
	}

	void RazApplyShader(RAZPTR<DX11DeviceContext> dhandle, RAZPTR<RazShader> shader)
	{
		dhandle->setvertexshader(shader);
		dhandle->setpixelshader(shader);
	}

	void RazApplyVertexShader(RAZPTR<RazShader> shader)
	{
		RazGetCurrentContext()->setvertexshader(shader);
	}

	void RazApplyPixelShader(RAZPTR<RazShader> shader)
	{
		RazGetCurrentContext()->setpixelshader(shader);
	}

	void RazApplyShader(RAZPTR<RazShader> shader)
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

	void RazSetBlendState(RAZPTR<DX11DeviceContext> dhandle)
	{
		dhandle->setblendstate();
	}

	void RazSetBlendState()
	{
		RazGetCurrentContext()->setblendstate();
	}

	void RazDrawIndexed(RAZPTR<DX11DeviceContext> dhandle, UINT index_count, UINT start_vertex_index, UINT base_vertex_location)
	{
		dhandle->drawIndexed(index_count, start_vertex_index, base_vertex_location);
	}

	void RazDrawIndexed(UINT index_count, UINT start_vertex_index, UINT base_vertex_location)
	{
		RazGetCurrentContext()->drawIndexed(index_count, start_vertex_index, base_vertex_location);
	}

	void RazApplyShaderTexture(RAZPTR<RazShader> shader, std::string name, RAZPTR<RazTexture> texture)
	{
		shader->UpdateTextureBuffer(name, texture->GetTexture());
		RazGetCurrentContext()->setshadertexture(texture->GetTextureView());
	}

	void RazApplyShaderTexture(std::string name, RAZPTR<RazTexture> texture)
	{
		RazGetCurrentShader()->UpdateTextureBuffer(name, texture->GetTexture());
		RazGetCurrentContext()->setshadertexture(texture->GetTextureView());
	}

	void RazApplyShaderTexture(RAZPTR<RazTexture> texture)
	{
		RazGetCurrentContext()->setshadertexture(texture->GetTextureView());
	}

	void RazApplyShaderTexture(RAZPTR<RazTexture> texture, UINT slot)
	{
		RazGetCurrentContext()->setshadertexture( slot,texture->GetTextureView());
	}

	void RazApplyVertexBuffer(RAZPTR<RazVertexBuffer> v)
	{
		RazGetCurrentContext()->setvertexbuffer(v);
	}

	void RazApplyVertexBuffer()
	{
		RazGetCurrentContext()->setvertexbuffer(RazGetCurrentVertexBuffer());
	}

	void RazApplyIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer)
	{
		RazGetCurrentContext()->setindexbuffer(ibuffer);
	}





}
