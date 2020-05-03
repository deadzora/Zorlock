#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <vector>
#include <material.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>


class SwapChain;
class DeviceContext;
class VertexBuffer;
class CalVertexBuffer;
class IndexBuffer;
class VertexShader;
class PixelShader;
class ComputeShader;
class Texture;
class Sprite;
class Light;
class RenderableObject;
class Camera;
class OrthoCamera;

template <class T>
class ConstantBuffer;



class GraphicsEngine
{
public:

	enum LIGHTTYPE
	{
		POINT,
		SPOT,
		DIRECTIONAL
	};

	GraphicsEngine();
	bool init(HWND hwnd);
	bool init();
	bool release();
	~GraphicsEngine();
public:
	static GraphicsEngine* get();
public:
	//Main Graphics Engine Functions
	void Cls();
	void Flip(bool vsync = false);
	void Init(HWND hwnd,RECT rect);
	void UpdateWorld();
	void RenderWorld();
	//Model
	RenderableObject* LoadModel(const wchar_t* filename);

	//Texture
	Texture* LoadTexture(const wchar_t* filename, aiTextureType textype = aiTextureType::aiTextureType_DIFFUSE);

	//Sprites
	Sprite* LoadSprite(float width, float height, const wchar_t* filename);

	//Objects
	Camera* CreateCamera(float aspectRatio, float fovDegrees = 90.0f, float nearZ = 0.1f, float farZ = 10000.0f);
	OrthoCamera* CreateCamera2D(float width, float height, float nearZ = 0.0f, float farZ = 10000.0f);
	Light* CreateLight(LIGHTTYPE lt = LIGHTTYPE::POINT);
	ID3D11Device* Get3dDevice();
	
	VertexBuffer* create_vertexbuffer();
	IndexBuffer* create_indexbuffer();
	template <class T>
	ConstantBuffer<T>* create_constantbuffer()
	{
		return new ConstantBuffer<T>(getImmediateDeviceContext()->getcontext(), m_d3d_device);
	}

	//ConstantBuffer2D* create_constantbuffer2d();
	//ConstantPixelBuffer * create_pixelconstantbuffer();



	DeviceContext* getImmediateDeviceContext();
	ID3D11ShaderResourceView* loadtexture(const wchar_t * filename);
	void setmodellights(int index);
	void getShaderBufferAndSize(void **bytecode, UINT*size);
	bool compilevertexshader(const wchar_t* filename, const char* entrypoint_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilepixelshader(const wchar_t* filename, const char* entrypoint_name, void** shader_byte_code, size_t* byte_code_size);
	void released_compiled_shader();
	SwapChain* create_swapchain();
	ID3D11Device* getdevice()
	{
		return m_d3d_device;
	};
private:
	VertexShader* create_vertexshader(const void * shader_byte_code, size_t byte_code_size);
	PixelShader* create_pixelshader(const void * shader_byte_code, size_t byte_code_size);
	bool setworldmatrix(float translate[], float scale[], float rotation[]);
	bool setworldmatrix();
	bool setprojectionmatrix();
	DirectX::XMMATRIX WorldMatrix;
	DirectX::XMMATRIX ProjectionMatrix;
	//move this when we create camera class
	DirectX::XMMATRIX View;
	//Begin High Level functions	
private:
	SwapChain* m_swapchain;
	ID3D11DeviceContext* m_imm_context;
	DeviceContext* m_imm_device_context;
private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL feature_level;

private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
private:
	ID3DBlob* m_blob;
	ID3DBlob* m_vsblob;
	ID3DBlob* m_psblob;
	ID3D11VertexShader* m_vs;
	ID3D11PixelShader* m_ps;
	
private:
	Camera * ActiveCamera;
	OrthoCamera * Active2DCamera;
	std::vector<Texture*> Textures;
	std::vector<RenderableObject*> RenderableGameObjects;
	std::vector<Light*> Lights;
	std::vector<Camera*> Cameras;
	std::vector<OrthoCamera*> Cameras2D;
	std::vector<Sprite*> Sprites;
private:
	friend class DeviceContext;
	friend class SwapChain;
	friend class VertexBuffer;
	friend class CalVertexBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class ComputeShader;
	friend class IndexBuffer;
	friend class ConstantBuffer<class T>;


};

