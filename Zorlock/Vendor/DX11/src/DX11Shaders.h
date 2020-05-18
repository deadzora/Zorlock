#pragma once
#include <d3d11.h>


namespace DX11Raz
{

	struct RazConstantBuffer
	{
	public:
		RazConstantBuffer() = default;
		~RazConstantBuffer() = default;
		std::string varname;
		UINT slot;
		ID3D11Buffer* buffer;
		UINT buffersize;
		void* data;
		void Release()
		{
			buffer->Release();
			//delete data;
		}
	};

	class DX11DeviceContext;

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
		UINT CreateVertexCB(std::string cbname, UINT slot, void * bufferdata, UINT buffersize);
		UINT CreatePixelCB(std::string cbname, UINT slot, void* bufferdata, UINT buffersize);
		bool UpdateVertexCB(void* bufferdata, std::string cbname);
		bool UpdatePixelCB(void* bufferdata, std::string cbname);
		bool ApplyVertexCB(std::string cbname);
		bool ApplyPixelCB(std::string cbname);
		void* GetPixelCBData(UINT index);
		void* GetVertexCBData(UINT index);
		bool ApplyAllVertexCB();
		bool ApplyAllPixelCB();
		ID3D10Blob* GetBuffer();
		ID3D10Blob* GetPBuffer();

	protected:
		friend class DX11DeviceContext;
		std::vector <RazConstantBuffer*> vc_buffer;
		std::vector <RazConstantBuffer*> pc_buffer;
		ID3D10Blob* mv_buffer;
		ID3D10Blob* mp_buffer;
		ID3D11VertexShader* m_vs;
		ID3D11PixelShader* m_ps;

	};






}