#include "ZLpch.h"
#include "DX11Graphics.h"
#include "DX11DeviceContext.h"
#include "DX11SwapChain.h"
#include "DX11Math.h"
#include "DirectX11VertexArray.h"
namespace ZorlockDX11
{
	bool DX11GraphicsEngine::SetWorldMatrix()
	{
		WorldMatrix = DirectX::XMMatrixIdentity();
		DirectX::XMVECTOR EyePos = DirectX::XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);
		DirectX::XMVECTOR LookAtPos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		DirectX::XMVECTOR UpVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		View = DirectX::XMMatrixLookAtLH(EyePos, LookAtPos, UpVector);
		return true;
	}
	bool DX11GraphicsEngine::SetProjectionMatrix()
	{
		float FOV = 90.0f;
		float AspectRatio = static_cast<float>(this->GetDX11DeviceContext()->width) / static_cast<float>(this->GetDX11DeviceContext()->height);
		float nearZ = 0.01f;
		float farZ = 1000.0f;
		ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(DX11Math::RadiansFromDegrees(FOV), AspectRatio, nearZ, farZ);
		return true;
	}

	ID3D11Device* DX11GraphicsEngine::GetD3D11Device()
	{
		return m_d3d_device;
	}
	IDXGIFactory* DX11GraphicsEngine::GetDXG11Factory()
	{
		return m_dxgi_factory;
	}
	DX11DeviceContext* DX11GraphicsEngine::GetDX11DeviceContext()
	{
		return m_imm_device_context;
	}
	bool DX11GraphicsEngine::CreateContext()
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
			res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &feature_level, &m_imm_context);

			if (SUCCEEDED(res))
				break;

			driver_type_index++;
		}
		if (FAILED(res))
		{
			ZL_CORE_INFO("Failed to find DX11 Driver");
			m_imm_context->Release();
			m_d3d_device->Release();
			return false;
		}

		m_imm_device_context = new DX11DeviceContext(m_imm_context);

		m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
		m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
		m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
		//m_dxgi_factory->CreateSwapChain




		return true;
	}

	unsigned int DX11GraphicsEngine::DX11CreateVertexArray(DirectX11VertexArray& va)
	{
		DirectX11VertexArray* v = new DirectX11VertexArray();
		va = *v;
		vertexArrays.push_back(va);
		return vertexArrays.size;
	}



	DX11SwapChain* DX11GraphicsEngine::CreateDX11SwapChain()
	{
		return new DX11SwapChain();
	}

	bool DX11GraphicsEngine::SetWorldMatrix(float translate[], float scale[], float rotation[])
	{
		WorldMatrix = DirectX::XMMatrixScaling(scale[0], scale[1], scale[2]) * DirectX::XMMatrixTranslation(translate[0], translate[1], translate[2]) * DirectX::XMMatrixRotationRollPitchYaw(rotation[0], rotation[1], rotation[3]);
		DirectX::XMVECTOR EyePos = DirectX::XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);
		DirectX::XMVECTOR LookAtPos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		DirectX::XMVECTOR UpVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		View = DirectX::XMMatrixLookAtLH(EyePos, LookAtPos, UpVector);
		return true;
	}

	void DX11GraphicsEngine::Init(HWND hwnd, RECT rect)
	{
		//this->init(hwnd);
		this->CreateContext();
		this->m_swapchain = this->CreateDX11SwapChain();
		this->m_swapchain->init(hwnd, rect.right - rect.left, rect.bottom - rect.top);
		this->GetDX11DeviceContext()->setviewportsize(rect.right - rect.left, rect.bottom - rect.top);
		this->GetDX11DeviceContext()->createblendstate();
	}

	DX11GraphicsEngine::~DX11GraphicsEngine()
	{
	}

	DX11GraphicsEngine* ZorlockDX11::DX11GraphicsEngine::get()
	{
		static DX11GraphicsEngine engine;
		return &engine;
	}

	void DX11GraphicsEngine::Cls()
	{
		this->GetDX11DeviceContext()->clearRenderTargetColor(this->m_swapchain, 0, 0, 0, 1);
	}

	void DX11GraphicsEngine::Cls(float r, float g, float b, float a)
	{
		this->GetDX11DeviceContext()->clearRenderTargetColor(this->m_swapchain, r, g, b, a);
	}

	void DX11GraphicsEngine::Flip(bool vsync)
	{
		this->m_swapchain->flip(vsync);
	}

	void DX11GraphicsEngine::UpdateWorld()
	{
		this->SetProjectionMatrix();
	}

	void DX11GraphicsEngine::RenderWorld()
	{
		//Not ready to be implemented yet
	}

	bool DX11GraphicsEngine::Release()
	{
		m_dxgi_device->Release();
		m_dxgi_adapter->Release();
		m_dxgi_factory->Release();
		m_imm_device_context->release();
		m_imm_context->Release();
		m_d3d_device->Release();
		return true;
	}

}
