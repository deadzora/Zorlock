#pragma once
typedef unsigned char BYTE;
#include "DX11Defs.h"
#include <d3d11.h>
#include <assimp/material.h>

namespace DX11Raz
{
#define RAZTEXTUREFILEW(filename) std::wstring(filename.begin(), filename.end()).c_str()
#define RAZTEXTUREFILE(filename) std::string(std::wstring(filename).begin(), std::wstring(filename).end())

	enum class RazTextureStorageType
	{
		Invalid,
		None,
		EmbeddedIndexCompressed,
		EmbeddedIndexNonCompressed,
		EmbeddedCompressed,
		EmbeddedNonCompressed,
		Disk
	};

	class DX11Color
	{
	public:
		DX11Color() : color(0)
		{
		};
		DX11Color(unsigned int val) :color(val)
		{

		}
		DX11Color(BYTE r, BYTE g, BYTE b);
		DX11Color(BYTE r, BYTE g, BYTE b, BYTE a);
		DX11Color(const DX11Color& src) : color(src.color)
		{

		}
		DX11Color& operator=(const DX11Color& src)
		{
			this->color = src.color;
			return *this;
		}
		bool operator==(const DX11Color& rhs) const
		{
			return (this->color == rhs.color);
		}
		bool operator!=(const DX11Color& rhs) const
		{
			return !(*this == rhs);
		}

		constexpr BYTE GetR() const
		{
			return this->rgba[0];
		}

		void SetR(BYTE r)
		{
			this->rgba[0] = r;
		}

		constexpr BYTE GetG() const
		{
			return this->rgba[1];
		}
		void SetG(BYTE g)
		{
			this->rgba[1] = g;
		}


		constexpr BYTE GetB() const
		{
			return this->rgba[2];
		}

		void SetB(BYTE b)
		{
			this->rgba[2] = b;
		}

		constexpr BYTE GetA() const
		{
			return this->rgba[3];
		}

		void SetA(BYTE a)
		{
			this->rgba[3] = a;
		}

		~DX11Color() = default;

	private:
		union
		{
			BYTE rgba[4];
			unsigned int color;
		};
	};


	const DX11Color UnloadedTextureColor(100, 100, 100);
	const DX11Color UnhandledTextureColor(255, 0, 255);
	const DX11Color Black(0, 0, 0);
	const DX11Color White(255, 255, 255);
	const DX11Color Red(255, 0, 0);
	const DX11Color Green(0, 255, 0);
	const DX11Color Blue(0, 0, 255);
	const DX11Color Yellow(255, 255, 0);
	const DX11Color Teal(0, 255, 255);


	class RazTexture
	{
	public:
		RazTexture(const DX11Color& color, aiTextureType type);
		RazTexture(const RAZPTR<DX11Color> colorData, UINT width, UINT height, aiTextureType type);
		RazTexture(const RAZPTR<DX11Color> colorData, UINT width, UINT height, UINT size, aiTextureType type);
		RazTexture(const wchar_t* filename, aiTextureType type);
		RazTexture(std::string filename, aiTextureType type);
		RazTexture(RAZPTR<ID3D11ShaderResourceView> textureView, aiTextureType type);
		RazTexture(const uint8_t* pData, size_t size, aiTextureType type);
		aiTextureType GetType();
		RAZPTR<ID3D11Resource> GetTexture();
		RAZPTR<ID3D11ShaderResourceView> GetTextureView();
		ID3D11ShaderResourceView** GetTextureAddress();
		void InsertTexture(RAZPTR<RazTexture> rtexture, UINT index);
		void Release();
		
	private:
		UINT GetByteSize(DXGI_FORMAT format);
		void Init1x1ColorTexture(const DX11Color& color, aiTextureType type);
		void InitColorTexture(const RAZPTR<DX11Color> colorData, UINT width, UINT height, aiTextureType type);
		void InitColorTextureArray(const RAZPTR<DX11Color> colorData, UINT width, UINT height, UINT size, aiTextureType type);
		UINT Width, Height, Size, Count;
		RAZPTR<ID3D11Resource> texture;
		RAZPTR<ID3D11ShaderResourceView> textureView;
		aiTextureType type = aiTextureType::aiTextureType_UNKNOWN;
	};


}