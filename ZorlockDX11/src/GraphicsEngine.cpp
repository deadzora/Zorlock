#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "ConstantBuffer2D.h"
#include "ConstantPixelBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "zMath.h"
#include "RenderableObject.h"
#include "Texture.h"
#include "Camera.h"
#include "OrthoCamera.h"
#include "Light.h"
#include "Sprite.h"
#include "StringConverter.h"
#include <d3dcompiler.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <Windows.h>
#include <material.h>
GraphicsEngine::GraphicsEngine()
{

}

bool GraphicsEngine::init(HWND hwnd)
{
	bool inited = this->init();
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(this->m_d3d_device, this->m_imm_context);
	ImGui::StyleColorsDark();

	return inited;
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] = 
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);


	D3D_FEATURE_LEVEL feature_levels[]=
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);
	HRESULT res = 0;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res=D3D11CreateDevice(NULL, driver_types[driver_type_index],NULL,NULL, feature_levels, num_feature_levels,D3D11_SDK_VERSION,&m_d3d_device, &feature_level,&m_imm_context);

		if (SUCCEEDED(res))
			break;

		driver_type_index++;
	}
	if (FAILED(res))
	{
		m_imm_context->Release();
		m_d3d_device->Release();
		return false;
	}

	m_imm_device_context = new DeviceContext(m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
	//m_dxgi_factory->CreateSwapChain




	return true;
}

bool GraphicsEngine::release()
{

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();
	m_imm_device_context->release();
	m_imm_context->Release();
	m_d3d_device->Release();
	/*
	for (size_t i = 0; i < this->textures.size(); i++)
	{
		this->textures[i]->Release();
	}
	*/
	return true;
}




bool GraphicsEngine::compilevertexshader(const wchar_t* filename, const char* entrypoint_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(::D3DCompileFromFile(filename, nullptr, nullptr, entrypoint_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if(error_blob)error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();


	return true;
}

bool GraphicsEngine::compilepixelshader(const wchar_t * filename, const char * entrypoint_name, void ** shader_byte_code, size_t * byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(::D3DCompileFromFile(filename, nullptr, nullptr, entrypoint_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob)error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();


	return true;
}

void GraphicsEngine::released_compiled_shader()
{
	if (this->m_blob) this->m_blob->Release();
}

void GraphicsEngine::setmodellights(int index)
{
	std::vector<Light*> furthest;
	std::vector<Light*> closest;

	for (UINT i = 0; i < this->Lights.size(); i++)
	{

	}
}

void GraphicsEngine::getShaderBufferAndSize(void ** bytecode, UINT * size)
{
	*bytecode = this->m_vsblob->GetBufferPointer();
	*size = this->m_vsblob->GetBufferSize();
}

GraphicsEngine::~GraphicsEngine()
{
}

GraphicsEngine * GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}

void GraphicsEngine::Cls()
{
	this->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swapchain, 0, 0, 0, 1);
}

void GraphicsEngine::Flip(bool vsync)
{
	this->m_swapchain->flip(vsync);
}

void GraphicsEngine::Init(HWND hwnd, RECT rect)
{
	this->init(hwnd);
	this->m_swapchain = this->create_swapchain();
	this->m_swapchain->init(hwnd, rect.right - rect.left, rect.bottom - rect.top);
	this->getImmediateDeviceContext()->setviewportsize(rect.right - rect.left, rect.bottom - rect.top);
	this->getImmediateDeviceContext()->createblendstate();
}

void GraphicsEngine::UpdateWorld()
{
	this->setprojectionmatrix();



	for (UINT i = 0; i < Lights.size(); i++)
	{
		Lights[i]->UpdateLight();
		Lights[i]->UpdateMatrix();
	}
}

void GraphicsEngine::RenderWorld()
{
	for (UINT i = 0; i < this->RenderableGameObjects.size(); i++)
	{
		this->RenderableGameObjects[i]->Draw(this->ActiveCamera->GetViewMatrix() * this->ActiveCamera->GetProjectionMatrix());
	}

	//do 2d last
	for (UINT i = 0; i < this->Sprites.size(); i++)
	{
		this->Sprites[i]->Draw(this->Active2DCamera->GetWorldMatrix() * this->Active2DCamera->GetOrthoMatrix());
	}
}

RenderableObject * GraphicsEngine::LoadModel(const wchar_t * filename)
{
	RenderableObject * gameobject = new RenderableObject(StringConverter::WidetoString(filename), L"shader.fx", L"shader.fx");
	RenderableGameObjects.push_back(gameobject);
	return gameobject;
}

Texture * GraphicsEngine::LoadTexture(const wchar_t * filename, aiTextureType textype)
{
	Texture * newtex = new Texture(filename, textype);
	Textures.push_back(newtex);
	return newtex;
}

Sprite * GraphicsEngine::LoadSprite(float width, float height, const wchar_t * filename)
{
	Sprite* sprite = new Sprite();
	sprite->Init(width, height, filename);
	Sprites.push_back(sprite);
	return sprite;
}

Camera * GraphicsEngine::CreateCamera(float aspectRatio, float fovDegrees, float nearZ, float farZ)
{
	Camera * camera = new Camera();
	camera->SetProjectionValues(fovDegrees, aspectRatio, nearZ, farZ);
	Cameras.push_back(camera);
	ActiveCamera = camera;
	return camera;
}

OrthoCamera * GraphicsEngine::CreateCamera2D(float width, float height, float nearZ, float farZ)
{
	OrthoCamera* camera = new OrthoCamera();
	camera->SetProjectionValues(width, height, nearZ, farZ);
	Cameras2D.push_back(camera);
	Active2DCamera = camera;
	return camera;
}

Light * GraphicsEngine::CreateLight(LIGHTTYPE lt)
{
	//make select case for light types

	Light * light = new Light(L"shader2d.fx", L"shader2d.fx");
	Lights.push_back(light);
	return light;
}

ID3D11Device * GraphicsEngine::Get3dDevice()
{
	return m_d3d_device;
}

SwapChain * GraphicsEngine::create_swapchain()
{
	return new SwapChain();
}

DeviceContext * GraphicsEngine::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer * GraphicsEngine::create_vertexbuffer()
{
	return new VertexBuffer();
}

IndexBuffer * GraphicsEngine::create_indexbuffer()
{
	
	return new IndexBuffer();
}


/*
ConstantBuffer2D * GraphicsEngine::create_constantbuffer2d()
{
	return new ConstantBuffer2D(getImmediateDeviceContext()->getcontext(), m_d3d_device);
}

ConstantPixelBuffer * GraphicsEngine::create_pixelconstantbuffer()
{
	return new ConstantPixelBuffer(getImmediateDeviceContext()->getcontext(), m_d3d_device);
}
*/

VertexShader * GraphicsEngine::create_vertexshader(const void * shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = new VertexShader();
	if (!vs->init(shader_byte_code, byte_code_size))
	{
		vs->release();
		return nullptr;
	}

	return vs;
}

PixelShader * GraphicsEngine::create_pixelshader(const void * shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader();
	if (!ps->init(shader_byte_code, byte_code_size))
	{
		ps->release();
		return nullptr;
	}

	return ps;
}

bool GraphicsEngine::setworldmatrix(float translate[], float scale[], float rotation[])
{

	WorldMatrix = DirectX::XMMatrixScaling(scale[0],scale[1],scale[2]) * DirectX::XMMatrixTranslation(translate[0], translate[1], translate[2]) * DirectX::XMMatrixRotationRollPitchYaw(rotation[0],rotation[1],rotation[3]);
	DirectX::XMVECTOR EyePos = DirectX::XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);
	DirectX::XMVECTOR LookAtPos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR UpVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	View = DirectX::XMMatrixLookAtLH(EyePos, LookAtPos, UpVector);
	return true;
}

bool GraphicsEngine::setworldmatrix()
{
	WorldMatrix = DirectX::XMMatrixIdentity();
	DirectX::XMVECTOR EyePos = DirectX::XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);
	DirectX::XMVECTOR LookAtPos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR UpVector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	View = DirectX::XMMatrixLookAtLH(EyePos, LookAtPos, UpVector);
	return true;
}

bool GraphicsEngine::setprojectionmatrix()
{
	float FOV = 90.0f;
	float AspectRatio = static_cast<float>(getImmediateDeviceContext()->w) / static_cast<float>(getImmediateDeviceContext()->h);
	float nearZ = 0.01f;
	float farZ = 1000.0f;
	ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(Math::RadiansFromDegrees(FOV), AspectRatio, nearZ, farZ);
	return true;
}

ID3D11ShaderResourceView * GraphicsEngine::loadtexture(const wchar_t * filename)
{
	ID3D11ShaderResourceView *tex;
	tex = this->getImmediateDeviceContext()->loadtexture(filename);
	//this->textures.push_back(tex);
	return tex;
}
