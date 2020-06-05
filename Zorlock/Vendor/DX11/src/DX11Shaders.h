#pragma once
#include <d3d11.h>
#include "DX11Defs.h"

namespace DX11Raz
{

	struct RazConstantBuffer
	{
	public:
		RazConstantBuffer() = default;
		~RazConstantBuffer() = default;
		std::string varname;
		UINT slot;
		RAZPTR<ID3D11Buffer> buffer;
		UINT buffersize;
		void* data;
		void Release()
		{
			buffer->Release();
			//delete data;
		}
	};

	struct RazSamplerBuffer
	{
	public:
		RazSamplerBuffer() : isuploaded(false), slot(0), buffersize(0), texture(nullptr), textureview(nullptr), varname(""), isArray(false)
		{};
		~RazSamplerBuffer() = default;
		RAZPTR<ID3D11ShaderResourceView> textureview;
		RAZPTR<ID3D11Resource> texture;
		std::string varname;
		UINT slot;
		UINT buffersize;
		bool isArray;
		bool isuploaded;
		std::vector<RAZPTR<ID3D11Resource>> texturearray;
		void Release()
		{
			//handled on the texture side
			//delete data;
		}
	};

	class DX11DeviceContext;
	class RazTexture;

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
		bool CreateTextureBuffer(std::string tname, UINT slot, UINT buffersize, bool isarray = false);
		bool UpdateTextureBuffer(std::string tname, RAZPTR<ID3D11Resource> tex, RAZPTR<ID3D11ShaderResourceView> texturev);
		bool UpdateTextureBuffer(std::string tname, RAZPTR<ID3D11Resource> tex);
		bool UpdateTextureBuffer(std::string tname, RAZPTR<ID3D11ShaderResourceView> texturev);
		bool UpdateTextureBuffer(std::string tname, RAZPTR<RazTexture> texture);
		bool GetTextureBufferUploaded(UINT slot);
		void SetTextureBufferUploaded(UINT slot, bool uploaded);
		bool UpdateVertexCB(void* bufferdata, std::string cbname);
		bool UpdatePixelCB(void* bufferdata, std::string cbname);
		bool ApplyVertexCB(std::string cbname);
		bool ApplyPixelCB(std::string cbname);
		void* GetPixelCBData(UINT index);
		void* GetVertexCBData(UINT index);
		bool ApplyAllVertexCB();
		bool ApplyAllPixelCB();
		void ApplyTexture(std::string cbname);
		void ApplyTextureArray(std::string cbname);
		RAZPTR<ID3D10Blob> GetBuffer();
		RAZPTR<ID3D10Blob> GetPBuffer();

	protected:
		friend class DX11DeviceContext;
		std::vector <RAZPTR<RazConstantBuffer>> vc_buffer;
		std::vector <RAZPTR<RazConstantBuffer>> pc_buffer;
		std::vector <RAZPTR<RazSamplerBuffer>> tx_buffer;
		RAZPTR<ID3D10Blob> mv_buffer;
		RAZPTR<ID3D10Blob> mp_buffer;
		RAZPTR<ID3D11VertexShader> m_vs;
		RAZPTR<ID3D11PixelShader> m_ps;

	};






}