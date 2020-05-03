#pragma once
#include <d3d11.h>
#include "Math.h"

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();
	bool load(void * list_vertices, UINT size_vertex, UINT size_list);
	virtual bool setlayout(void* shader_byte_code, UINT size_byte_shader);
	virtual bool load(void * list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	bool setlayout(const D3D11_INPUT_ELEMENT_DESC * layout, UINT size_layout, void * shader_byte_code, UINT size_byte_shader);
	bool load(D3D11_INPUT_ELEMENT_DESC * layout, UINT size_layout, void * list_vertices, UINT size_vertex, UINT size_list, void * shader_byte_code, UINT size_byte_shader);
	UINT GetVertexListSize();
	bool release();
	~VertexBuffer();
protected:
	UINT m_size_vertex;
	UINT m_size_list;
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
protected:
	friend class DeviceContext;
};
