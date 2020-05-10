#pragma once
#include <d3d11.h>


namespace DX11Raz
{


	class RazShader
	{
	public:
		RazShader();
		~RazShader();
		void Release();
		bool InitVertex(const wchar_t* filename);
		bool InitVertex(const std::string shadertext);
		bool InitVertex(const void* shader_byte_code, size_t byte_code_size);
		bool InitPixel(const wchar_t* filename);
		bool InitPixel(const std::string shadertext);
		bool InitPixel(const void* shader_byte_code, size_t byte_code_size);
		//constant buffers
		UINT CreateVertexCB(void * bufferdata, UINT buffersize);
		UINT CreatePixelCB(void* bufferdata, UINT buffersize);
		bool UpdateVertexCB(void* bufferdata, UINT buffersize, UINT index);
		bool UpdatePixelCB(void* bufferdata, UINT buffersize, UINT index);
		bool ApplyVertexCB(void* bufferdata, UINT buffersize, UINT index);
		bool ApplyPixelCB(void* bufferdata, UINT buffersize, UINT index);
		void* GetPixelCBData(UINT index);
		void* GetVertexCBData(UINT index);
		bool ApplyAllVertexCB();
		bool ApplyAllPixelCB();
		ID3D10Blob* GetBuffer();
	protected:
		std::vector<void*> vdata;
		std::vector<void*> pdata;
		std::vector <UINT> vbsize;
		std::vector <UINT> pbsize;
		std::vector < ID3D11Buffer*> vc_buffer;
		std::vector < ID3D11Buffer*> pc_buffer;
		ID3D10Blob* m_buffer;
		ID3D11VertexShader* m_vs;
		ID3D11PixelShader* m_ps;

	};






}