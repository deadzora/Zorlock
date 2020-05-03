#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "shader.h"


class PixelShader : public Shader
{
public:
	PixelShader();
	void release();
	~PixelShader();
	bool init(const wchar_t* filename);
private:
	bool init(const void* shader_byte_code, size_t byte_code_size);
	ID3D11PixelShader* m_ps;
	friend class GraphicsEngine;
	friend class DeviceContext;
};

