#pragma once
#include "DX11Defs.h"
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
	void RazDX11CreateContext(RAZPTR<ZWindow> zhandle);
	void RazSetCLSColor(RAZPTR<DX11DeviceContext> dhandle, float r, float g, float b, float a);
	void RazCLS(RAZPTR<DX11DeviceContext> dhandle);
	void RazSetViewport(UINT width, UINT height);
	RAZPTR<RazVertexBuffer> RazCreateVertexBuffer();
	void RazDeleteVertexBuffer(RAZPTR<RazVertexBuffer> v);
	RAZPTR<RazIndexBuffer> RazCreateIndexBuffer();
	void RazDeleteIndexBuffer(RAZPTR<RazIndexBuffer> i);
	RAZPTR<RazShader> RazCreateShader();
	void RazDeleteShader(RAZPTR<RazShader> shader);
	void RazSetCurrentShader(RAZPTR<RazShader> shader);
	RAZPTR<RazShader> RazGetCurrentShader();
	void RazSetCurrentContext(RAZPTR<DX11DeviceContext> dhandle);
	RAZPTR<DX11DeviceContext> RazGetCurrentContext();
	void RazSetCurrentVertexBuffer(RAZPTR<RazVertexBuffer> vbuffer);
	RAZPTR<RazVertexBuffer> RazGetCurrentVertexBuffer();
	void RazSetCurrentIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer);
	RAZPTR<RazIndexBuffer> RazGetCurrentIndexBuffer();
	RAZPTR<RazTexture> RazGetCurrentTexture();

	RAZPTR<RazTexture> RazCreateTexture(const RAZPTR<DX11Color> colorData, UINT width, UINT height, aiTextureType type);
	RAZPTR<RazTexture> RazCreateTexture(const RAZPTR<DX11Color> colorData, UINT width, UINT height, UINT size, aiTextureType type);
	RAZPTR<RazTexture> RazCreateTexture(const wchar_t* filename, aiTextureType type);
	RAZPTR<RazTexture> RazCreateTexture(std::string filename, aiTextureType type);
	RAZPTR<RazTexture> RazCreateTexture(RAZPTR<ID3D11ShaderResourceView> textureView, aiTextureType type);

	void RazSetCurrentTexture(RAZPTR<RazTexture> texture);
	void RazSetDeleteTexture(RAZPTR<RazTexture> texture);
	void RazSetLayout(RAZPTR<RazVertexBuffer> vbuffer, RAZPTR<ID3D10Blob> vertexshader);
	void RazSetLayout(RAZPTR<ID3D10Blob> vertexshader);
	void RazSetLayout(RAZPTR<RazVertexBuffer> vbuffer);
	void RazSetLayout();
	void RazBindIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer);
	void RazBindIndexBuffer();
	void RazBindIndices(RAZPTR<RazIndexBuffer> ibuffer, UINT* indices, UINT count);
	void RazBindIndices(UINT* indices, UINT count);
	void RazBindIndices(std::vector<DWORD> indices);
	void RazBindVertices(RAZPTR<RazVertexBuffer> vbuffer, float* verts, UINT size);
	void RazBindVertices(RAZPTR<RazVertexBuffer> vbuffer, void* vertices, UINT size);
	void RazBindVertices(RAZPTR<RazVertexBuffer> vbuffer, void* vertices, UINT bytewidth, UINT size);
	void RazBindVertices(float* verts, UINT size);
	void RazBindVertices(void* vertices, UINT size);
	void RazBindVertices(UINT size);
	void RazFlip(bool vsync);
	void RazApplyVertexShaderConstants(RAZPTR<RazShader> shader);
	void RazApplyPixelShaderConstants(RAZPTR<RazShader> shader);
	void RazApplyVertexShaderConstants();
	void RazApplyPixelShaderConstants();
	void RazApplyVertexShader(RAZPTR<DX11DeviceContext> dhandle, RAZPTR<RazShader> shader);
	void RazApplyPixelShader(RAZPTR<DX11DeviceContext> dhandle, RAZPTR<RazShader> shader);
	void RazApplyShader(RAZPTR<DX11DeviceContext> dhandle, RAZPTR<RazShader> shader);
	void RazApplyVertexShader(RAZPTR<RazShader> shader);
	void RazApplyPixelShader(RAZPTR<RazShader> shader);
	void RazApplyShader(RAZPTR<RazShader> shader);
	void RazApplyVertexShader();
	void RazApplyPixelShader();
	void RazApplyShader();
	void RazSetBlendState(RAZPTR<DX11DeviceContext> dhandle);
	void RazSetBlendState();
	void RazDrawIndexed(RAZPTR<DX11DeviceContext> dhandle,UINT index_count, UINT start_vertex_index, UINT base_vertex_location);
	void RazDrawIndexed(UINT index_count, UINT start_vertex_index, UINT base_vertex_location);
	void RazApplyShaderTexture(RAZPTR<RazShader> shader,std::string name, RAZPTR<RazTexture> texture);
	void RazApplyShaderTexture(std::string name, RAZPTR<RazTexture> texture);
	void RazApplyShaderTexture(RAZPTR<RazTexture> texture);
	void RazApplyShaderTexture(RAZPTR<RazTexture> texture, UINT slot);
	void RazApplyVertexBuffer(RAZPTR<RazVertexBuffer> v);
	void RazApplyVertexBuffer();
	void RazApplyIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer);
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

		RAZPTR<ID3D11Device> GetDevice();
		RAZPTR<IDXGIFactory> GetFactory();
		//get set current shader
		RAZPTR<RazShader> GetCurrentShader();
		void SetCurrentShader(RAZPTR<RazShader> shader);
		void AddShader(RAZPTR<RazShader> shader);
		void RemoveShader(RAZPTR<RazShader> shader);

		//get set current context
		RAZPTR<DX11DeviceContext> GetCurrentDeviceContext();
		void SetCurrentDeviceContext(RAZPTR<DX11DeviceContext> curcontext);
		void AddDeviceContext(RAZPTR<DX11DeviceContext> curcontext);
		void RemoveDeviceContext(RAZPTR<DX11DeviceContext> context);
		//get set current indexbuffer
		RAZPTR<RazVertexBuffer> GetCurrentVertexBuffer();
		void SetCurrentVertexBuffer(RAZPTR<RazVertexBuffer> vbuffer);
		void AddVertexBuffer(RAZPTR<RazVertexBuffer> vbuffer);
		void RemoveVertexBuffer(RAZPTR<RazVertexBuffer> vbuffer);
		
		RAZPTR<RazIndexBuffer> GetCurrentIndexBuffer();
		void SetCurrentIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer);
		void AddIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer);
		void RemoveIndexBuffer(RAZPTR<RazIndexBuffer> ibuffer);
		//get set current texture
		RAZPTR<RazTexture> GetCurrentTexture();
		void SetCurrentTexture(RAZPTR<RazTexture> texture);
		void AddTexture(RAZPTR<RazTexture> texture);
		void RemoveTexture(RAZPTR<RazTexture> texture);
		RAZPTR<DX11DeviceContext> GetImmediateDeviceContext();
		//ID3D11DeviceContext* GetContext();
		RAZPTR<DX11SwapChain> CreateSwapChain();
		void AddSwapChain(RAZPTR<DX11SwapChain> swapchain);
		void RemoveSwapChain(RAZPTR<DX11SwapChain> swapchain);

#if defined(ZL_DEBUG)
		//ID3D11Debug* DXEnableDebug(DX11DebugCallback func);
#endif
	private:
		bool intialized;
		RAZPTR<RazShader> currentShader;
		RAZPTR<RazVertexBuffer> currentVertexBuffer;
		RAZPTR<RazIndexBuffer> currentIndexBuffer;
		RAZPTR<RazTexture> currentTexture;
		RAZPTR<DX11DeviceContext> current_device_context;
		RAZPTR<ID3D11Device> m_d3d_device;
		RAZPTR<IDXGIDevice> m_dxgi_device;
		RAZPTR<IDXGIAdapter> m_dxgi_adapter;
		RAZPTR<IDXGIFactory> m_dxgi_factory;
		RAZPTR<ID3D11InfoQueue> d3dInfoQueue;
		D3D_FEATURE_LEVEL feature_level;

		RAZPTR<ID3D11DeviceContext> m_imm_context;
		//DX11SwapChain* m_swapchain;
		RAZPTR<ID3D11Debug> m_d3dDebug;
		
#ifdef ZL_DEBUG_DX11
		DX11DebugCallback DebugCall;

#endif
		//main context
		RAZPTR<DX11DeviceContext> m_imm_device_context;

		//Keep a list of everything created so it can be released
		std::vector<RAZPTR<RazShader>> shaders;
		std::vector< RAZPTR<RazVertexBuffer>> vbuffers;
		std::vector< RAZPTR<RazIndexBuffer>> ibuffers;
		std::vector< RAZPTR<RazTexture>> textures;
		std::vector< RAZPTR<DX11DeviceContext>> contexts;
		std::vector< RAZPTR<DX11SwapChain>> swapchains;

	};

	




}