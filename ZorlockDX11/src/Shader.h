#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

class GraphicsEngine;


class Shader
{
public:
	Shader();
	~Shader();
	virtual void release() {};
	virtual bool init(const wchar_t* filename) { return true;  };
	ID3D10Blob * GetBuffer();
protected:
	virtual bool init(const void* shader_byte_code, size_t byte_code_size) { return true; };
	ID3D10Blob * m_buffer;
	friend class GraphicsEngine;
	friend class DeviceContext;
};

