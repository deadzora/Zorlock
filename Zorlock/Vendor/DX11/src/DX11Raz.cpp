#include "ZLpch.h"
#include "DX11Raz.h"
#include "DX11DeviceContext.h"
#include "DX11SwapChain.h"
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
			D3D_FEATURE_LEVEL_11_0
		};
		UINT num_feature_levels = ARRAYSIZE(feature_levels);
		HRESULT res = 0;

		OutputDebugString(L"Initializing DX11 3D Device\r\n");

		for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
		{
			//NO IMMEDIATE CONTEXT!
#ifdef ZL_DEBUG
			res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, D3D11_DEBUG_FEATURE_FINISH_PER_RENDER_OP, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &feature_level, &m_imm_context);
#else
			res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &feature_level, NULL);//&m_imm_context);
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
		//this->Cls(0, 0, 0, 1);
	}

	void DX11GraphicsEngine::Cls(float r, float g, float b, float a)
	{
		//we need to know which context we are performing CLS on

		//this->m_imm_device_context->clearRenderTargetColor(this->m_swapchain, r, g, b, a);
	}

	void DX11GraphicsEngine::Flip(bool vsync)
	{
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

	DX11DeviceContext* DX11GraphicsEngine::GetImmediateDeviceContext()
	{
		return m_imm_device_context;
	}



	DX11SwapChain* DX11GraphicsEngine::CreateSwapChain()
	{
		return new DX11SwapChain();;
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
			DX11DeviceContext * DXContext = new DX11DeviceContext(DX11GraphicsEngine::Get()->GetImmediateDeviceContext()->GetContext());

			zhandle->SetDeviceContext(DXContext);
			DXContext->Init(zhandle);

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

}
