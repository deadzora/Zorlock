#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <ZWindow.h>
#include <vector>
#include <filesystem>
#include <assimp/material.h>

namespace DX11Raz
{
#define RAZGETEXTENSION(f) f.substr(f.find_last_of(".") + 1)
#define RAZFILEEXISTS(f) std::filesystem::exists(f)

#ifndef D3D_COMPILE_STANDARD_FILE_INCLUDE
#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)
#endif

#ifdef ZL_DEBUG_DX11
	typedef bool (*DX11DebugCallback)(void* pInfoQueue);
#define PID3D11InfoQueue(p) static_cast<ID3D11InfoQueue*>(p);
#endif

	class DX11Color;
	class DX11DeviceContext;
	class DX11SwapChain;
	class RazVertexBuffer;
	class RazIndexBuffer;
	class RazShader;
	class RazTexture;
	//we need to be able to handle multiple contexts at once, so we need to push our device data to a new class


	bool RazDX11Initialize();
	bool RazDX11Release();
	void RazDX11CreateContext(ZWindow* zhandle);
	void RazSetCLSColor(DX11DeviceContext* dhandle, float r, float g, float b, float a);
	void RazCLS(DX11DeviceContext* dhandle);
	void RazSetViewport(UINT width, UINT height);
	RazVertexBuffer* RazCreateVertexBuffer();
	void RazDeleteVertexBuffer(RazVertexBuffer* v);
	RazIndexBuffer * RazCreateIndexBuffer();
	void RazDeleteIndexBuffer(RazIndexBuffer* i);
	RazShader* RazCreateShader();
	void RazDeleteShader(RazShader * shader);
	void RazSetCurrentShader(RazShader* shader);
	RazShader* RazGetCurrentShader();
	void RazSetCurrentContext(DX11DeviceContext* dhandle);
	DX11DeviceContext* RazGetCurrentContext();
	void RazSetCurrentVertexBuffer(RazVertexBuffer* vbuffer);
	RazVertexBuffer* RazGetCurrentVertexBuffer();
	void RazSetCurrentIndexBuffer(RazIndexBuffer* ibuffer);
	RazIndexBuffer* RazGetCurrentIndexBuffer();
	RazTexture* RazGetCurrentTexture();
	RazTexture* RazCreateTexture(const DX11Color& color, aiTextureType type);
	RazTexture* RazCreateTexture(const DX11Color* colorData, UINT width, UINT height, aiTextureType type);
	RazTexture* RazCreateTexture(const DX11Color* colorData, UINT width, UINT height, UINT size, aiTextureType type);
	RazTexture* RazCreateTexture(const wchar_t* filename, aiTextureType type);
	RazTexture* RazCreateTexture(std::string filename, aiTextureType type);
	RazTexture* RazCreateTexture(ID3D11ShaderResourceView* textureView, aiTextureType type);

	void RazSetCurrentTexture(RazTexture* texture);
	void RazSetDeleteTexture(RazTexture* texture);
	void RazSetLayout(RazVertexBuffer* vbuffer, ID3D10Blob* vertexshader);
	void RazSetLayout(ID3D10Blob* vertexshader);
	void RazSetLayout(RazVertexBuffer* vbuffer);
	void RazSetLayout();
	void RazBindIndexBuffer(RazIndexBuffer* ibuffer);
	void RazBindIndexBuffer();
	void RazBindIndices(RazIndexBuffer* ibuffer, UINT* indices, UINT count);
	void RazBindIndices(UINT* indices, UINT count);
	void RazBindIndices(std::vector<DWORD> indices);
	void RazBindVertices(RazVertexBuffer* vbuffer, float* verts, UINT size);
	void RazBindVertices(RazVertexBuffer* vbuffer, void* vertices, UINT size);
	void RazBindVertices(RazVertexBuffer* vbuffer, void* vertices, UINT bytewidth, UINT size);
	void RazBindVertices(float* verts, UINT size);
	void RazBindVertices(void* vertices, UINT size);
	void RazBindVertices(UINT size);
	void RazFlip(bool vsync);
	void RazApplyVertexShaderConstants(RazShader* shader);
	void RazApplyPixelShaderConstants(RazShader* shader);
	void RazApplyVertexShaderConstants();
	void RazApplyPixelShaderConstants();
	void RazApplyVertexShader(DX11DeviceContext* dhandle,RazShader* shader);
	void RazApplyPixelShader(DX11DeviceContext* dhandle,RazShader* shader);
	void RazApplyShader(DX11DeviceContext* dhandle,RazShader* shader);
	void RazApplyVertexShader(RazShader* shader);
	void RazApplyPixelShader(RazShader* shader);
	void RazApplyShader(RazShader* shader);
	void RazApplyVertexShader();
	void RazApplyPixelShader();
	void RazApplyShader();
	void RazSetBlendState(DX11DeviceContext* dhandle);
	void RazSetBlendState();
	void RazDrawIndexed(DX11DeviceContext* dhandle,UINT index_count, UINT start_vertex_index, UINT base_vertex_location);
	void RazDrawIndexed(UINT index_count, UINT start_vertex_index, UINT base_vertex_location);
	void RazApplyShaderTexture(RazShader* shader,std::string name, RazTexture* texture);
	void RazApplyShaderTexture(std::string name, RazTexture* texture);
	void RazApplyShaderTexture(RazTexture* texture);
	void RazApplyShaderTexture(RazTexture* texture, UINT slot);
	void RazApplyVertexBuffer(RazVertexBuffer* v);
	void RazApplyVertexBuffer();
	void RazApplyIndexBuffer(RazIndexBuffer* ibuffer);
	//void RazApplyShaderTextureIndex(RazShader* shader, UINT index, std::string name, RazTexture* texture);
	//void RazApplyShaderTextureIndex(UINT index, std::string name, RazTexture* texture);

	class DX11GraphicsEngine
	{
	public:
		DX11GraphicsEngine() 
		{};
		~DX11GraphicsEngine();
		bool Initialize();
		bool enabled;
		void Release();
		//bool SetContext(HWND hwnd, RECT rect);
	public:
		static DX11GraphicsEngine* Get();
	public:
		void Cls();
		void Cls(float r, float g, float b, float a);
		void Flip(bool vsync = false);
		void SetViewport(UINT x, UINT y, UINT width, UINT height);

		ID3D11Device* GetDevice();
		IDXGIFactory* GetFactory();
		//get set current shader
		RazShader* GetCurrentShader();
		void SetCurrentShader(RazShader * shader);
		void AddShader(RazShader* shader);
		void RemoveShader(RazShader* shader);

		//get set current context
		DX11DeviceContext* GetCurrentDeviceContext();
		void SetCurrentDeviceContext(DX11DeviceContext* curcontext);
		void AddDeviceContext(DX11DeviceContext* curcontext);
		void RemoveDeviceContext(DX11DeviceContext* context);
		//get set current indexbuffer
		RazVertexBuffer* GetCurrentVertexBuffer();
		void SetCurrentVertexBuffer(RazVertexBuffer* vbuffer);
		void AddVertexBuffer(RazVertexBuffer* vbuffer);
		void RemoveVertexBuffer(RazVertexBuffer* vbuffer);
		
		RazIndexBuffer* GetCurrentIndexBuffer();
		void SetCurrentIndexBuffer(RazIndexBuffer* ibuffer);
		void AddIndexBuffer(RazIndexBuffer* ibuffer);
		void RemoveIndexBuffer(RazIndexBuffer* ibuffer);
		//get set current texture
		RazTexture* GetCurrentTexture();
		void SetCurrentTexture(RazTexture* texture);
		void AddTexture(RazTexture* texture);
		void RemoveTexture(RazTexture* texture);
		DX11DeviceContext* GetImmediateDeviceContext();
		//ID3D11DeviceContext* GetContext();
		DX11SwapChain* CreateSwapChain();
		void AddSwapChain(DX11SwapChain* swapchain);
		void RemoveSwapChain(DX11SwapChain* swapchain);

#if defined(ZL_DEBUG)
		//ID3D11Debug* DXEnableDebug(DX11DebugCallback func);
#endif
	private:
		bool intialized;
		RazShader* currentShader;

		RazVertexBuffer* currentVertexBuffer;

		RazIndexBuffer* currentIndexBuffer;

		RazTexture* currentTexture;

		DX11DeviceContext* current_device_context;

		ID3D11Device* m_d3d_device;
		IDXGIDevice* m_dxgi_device;
		IDXGIAdapter* m_dxgi_adapter;
		IDXGIFactory* m_dxgi_factory;
		ID3D11InfoQueue* d3dInfoQueue;
		D3D_FEATURE_LEVEL feature_level;

		ID3D11DeviceContext* m_imm_context;
		//DX11SwapChain* m_swapchain;
		ID3D11Debug* m_d3dDebug;
		
#ifdef ZL_DEBUG_DX11
		DX11DebugCallback DebugCall;

#endif
		//main context
		DX11DeviceContext* m_imm_device_context;

		//Keep a list of everything created so it can be released
		std::vector< RazShader*> shaders;
		std::vector< RazVertexBuffer*> vbuffers;
		std::vector< RazIndexBuffer*> ibuffers;
		std::vector< RazTexture*> textures;
		std::vector< DX11DeviceContext*> contexts;
		std::vector< DX11SwapChain*> swapchains;

	};

	




}