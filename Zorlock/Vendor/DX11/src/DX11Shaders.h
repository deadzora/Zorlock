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

		ID3D10Blob* GetBuffer();
	protected:
		
		ID3D10Blob* m_buffer;
		ID3D11VertexShader* m_vs;
		ID3D11PixelShader* m_ps;

	};






}