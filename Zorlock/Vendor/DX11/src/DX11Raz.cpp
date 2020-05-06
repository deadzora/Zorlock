#include "ZLpch.h"
#include "DX11Raz.h"
#include "DX11DeviceContext.h"
#include "DX11SwapChain.h"
#include <D3d11sdklayers.h>

namespace DX11Raz
{
	
	static bool enabled = false;

	

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

		for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
		{
#ifdef ZL_DEBUG
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
			m_imm_context->Release();
			m_d3d_device->Release();
			return false;
		}
		m_imm_device_context = new DX11DeviceContext(m_imm_context);

		m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
		m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
		m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
		//m_dxgi_factory->CreateSwapChain
		intialized = true;

		viewportsize.left = 0;
		viewportsize.top = 0;
		viewportsize.right = 1280;
		viewportsize.bottom = 720;

		return true;
	}

	bool DX11GraphicsEngine::SetContext(HWND hwnd)
	{
		return this->SetContext(hwnd, viewportsize);
	}

	bool DX11GraphicsEngine::SetContext(HWND hwnd, RECT rect)
	{
		if (intialized == false)
		{
			Initialize();
		}
		viewportsize = rect;
		this->m_swapchain = this->CreateSwapChain();
		this->m_swapchain->init(hwnd, 1280, 720);//rect.right - rect.left, rect.bottom - rect.top);
		this->m_imm_device_context->setviewportsize(1280, 720); //rect.right - rect.left, rect.bottom - rect.top);
		this->m_imm_device_context->createblendstate();
		return true;
	}

	DX11GraphicsEngine* DX11GraphicsEngine::Get()
	{
		static DX11GraphicsEngine engine;
		enabled = true;
		return &engine;
	}

	void DX11GraphicsEngine::Cls()
	{
		this->Cls(0, 0, 0, 1);
	}

	void DX11GraphicsEngine::Cls(float r, float g, float b, float a)
	{
		this->m_imm_device_context->clearRenderTargetColor(this->m_swapchain, r, g, b, a);
	}

	void DX11GraphicsEngine::Flip(bool vsync)
	{
		this->m_swapchain->flip(vsync);
	}

	void DX11GraphicsEngine::SetViewport(UINT x, UINT y, UINT width, UINT height)
	{

		viewportsize.left = x;
		viewportsize.top = y;
		viewportsize.right = x + width;
		viewportsize.bottom = y + height;

		m_imm_device_context->setviewportsize(width, height);

	}

	ID3D11Device* DX11GraphicsEngine::GetDevice()
	{
		return m_d3d_device;
	}

	IDXGIFactory* DX11GraphicsEngine::GetFactory()
	{
		return m_dxgi_factory;
	}

	ID3D11DeviceContext* DX11GraphicsEngine::GetContext()
	{
		return m_imm_context;
	}

	DX11SwapChain* DX11GraphicsEngine::CreateSwapChain()
	{
		return new DX11SwapChain();;
	}
#ifdef ZL_DEBUG
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
#endif


}
