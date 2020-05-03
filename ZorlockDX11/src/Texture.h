#pragma once
#include "Color.h"
#include <d3d11.h>
#include <material.h>


enum class TextureStorageType
{
	Invalid,
	None,
	EmbeddedIndexCompressed,
	EmbeddedIndexNonCompressed,
	EmbeddedCompressed,
	EmbeddedNonCompressed,
	Disk
};

class Texture
{
public:
	Texture(const Color & color, aiTextureType type);
	Texture(const Color * colorData, UINT width, UINT height, aiTextureType type);
	Texture(const wchar_t * filename, aiTextureType type);
	Texture(ID3D11ShaderResourceView * textureView, aiTextureType type);
	Texture(const uint8_t * pData, size_t size, aiTextureType type);
	aiTextureType GetType();
	ID3D11ShaderResourceView * GetTexture();
	ID3D11ShaderResourceView ** GetTextureAddress();
	void Release();
	~Texture();
private:
	void Init1x1ColorTexture(const Color & color, aiTextureType type);
	void InitColorTexture(const Color * colorData, UINT width, UINT height, aiTextureType type);
	ID3D11Resource * texture;
	ID3D11ShaderResourceView * textureView;
	aiTextureType type = aiTextureType::aiTextureType_UNKNOWN;
};

